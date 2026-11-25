#!/usr/bin/env python3

'''
ZeeTweak 5.0 - Transfer and process data for Zeeweii oscilloscopes.

https://github.com/taligentx/ZeeTweak

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
'''

import serial
import serial.tools.list_ports
import time
import struct
import argparse
import numpy as np
from PIL import Image
from datetime import datetime
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.patheffects as pe
from matplotlib.colors import to_rgb
from matplotlib.offsetbox import TextArea, HPacker, AnnotationBbox
import csv
import contextlib
import io
try:
    import termios
except ImportError:
    termios = None
import os
import re
import sys
import select
import zlib
import base64
import hashlib
import json

VDIV_BASE_X1 = {13:10000000, 12:5000000, 11:2000000, 10:1000000, 9:500000, 8:200000, 7:100000, 6:50000, 5:20000, 4:10000, 3:5000, 2:2000, 1:1000}
TIMEBASE_LABELS = {
    0:"1ns", 1:"2ns", 2:"5ns", 3:"10ns", 4:"20ns", 5:"50ns", 6:"100ns",
    7:"200ns", 8:"500ns", 9:"1us", 10:"2us", 11:"5us", 12:"10us", 13:"20us",
    14:"50us", 15:"100us", 16:"200us", 17:"500us", 18:"1ms", 19:"2ms", 20:"5ms",
    21:"10ms", 22:"20ms", 23:"50ms", 24:"100ms", 25:"200ms", 26:"500ms",
    27:"1s", 28:"2s", 29:"5s", 30:"10s"
}
PROBE_LABELS = {0:"x1", 1:"x10", 2:"x100"}
RUN_STATES  = {0:"Stop", 1:"Run", 2:"Wait"}
MEASUREMENT_FLAGS = {
    0: ("Freq", 11, "F"),
    1: ("PkPk", 0, "V"),
    2: ("Avg", 6, "V"),
    3: ("RMS", 7, "V"),
    4: ("Amp", 1, "V"),
    5: ("+Duty", 12, "D"),
    6: ("+T", 8, "T"),
    7: ("-T", 9, "T"),
    8: ("T", 10, "T"),
    9: ("Max", 4, "V"),
    10: ("Min", 5, "V"),
    11: ("Top", 2, "V"),
    12: ("Base", 3, "V"),
    13: ("-Duty", 13, "D")
}
SELECTED_MEASUREMENTS = {label[0].lower(): idx for idx, label in MEASUREMENT_FLAGS.items()}
SIGGEN_PATTERNS = {0:"Sine", 1:"Square", 2:"Triangle", 3:"Sawtooth", 4:"Halfwave", 5:"Fullwave", 6:"Sinc", 7:"Noise"}

# Data offset, label, bytes, signed
DATA_DSO3D12 = {
    1200: ("Run State", 1, False),                  # 0=Stop, 1=Run, 2=Wait
    1201: ("System State", 1, False),
    1202: ("CH2 Enabled", 1, False),
    1204: ("Buffer Depth", 8, True),                # Total samples (60000)
    1212: ("HW Buffer Wrap Val?", 4, False),        # Sets to 0x10000, 0x8000, 0x4000, 0
    1216: ("Timebase Index", 1, False),             # 2=5ns...30=10s
    1220: ("Timebase Value (ns/div)", 8, False),
    1228: ("Horiz Trigger Delay (ps)", 8, True),    # Trigger position in the record; pre = rec/2 + delay*fs
    1236: ("View Scroll Offset (ps)", 8, True),     # Stopped-view pan only; negative moves waveform right
    1244: ("Fetch Start Offset (samples)", 4, True), # clamp(winaddr/1000, -post, pre); cursor - this = read start
    1248: ("Window Address Offset (1/1000 smp)", 8, True), # (6*tb_ps + delay - scroll) * fs / 1e9
    1256: ("Trigger Source", 1, False),             # 0=Ch1, 1=Ch2
    1257: ("Trigger Mode", 1, False),               # 0=Auto, 1=Normal
    1258: ("Trigger Edge", 1, False),               # 0=Rise, 1=Fall
    1259: ("Trigger Level Mode", 1, False),         # 0=Auto, 1=Manual
    1260: ("Buffer Write Cursor", 4, False),        # Fetch window reference; dynamic per waveform
    1264: ("Trigger Level ADC", 2, False),          # 0-255
    1266: ("CH1 V/Div Index", 1, False),
    1268: ("CH1 Volt Scale (uV)", 4, False),
    1272: ("CH1 Zero Volt (pixels)", 4, True),
    1276: ("CH1 Zero Volt (uV)", 8, True),
    1284: ("CH1 Trigger Level Offset (uV)", 8, True),
    1292: ("CH1 Trigger Level (uV)", 8, True),
    1300: ("CH1 Trigger Level (pixels)", 4, True),
    1304: ("CH1 Coupling", 1, False),               # 0=DC, 1=AC
    1305: ("CH1 Probe Mode", 1, False),
    1308: ("CH1 Enabled Measurements", 4, False),   # Bitfield
    1312: ("CH1 Gain Cal", 2, False),
    1316: ("CH1 Vert Offset Buffer (uV)", 8, True),
    1324: ("CH1 Vert Scroll Offset", 4, False),
    1328: ("CH2 V/Div Index", 1, False),
    1332: ("CH2 Volt Scale (uV)", 4, False),
    1336: ("CH2 Zero Volt (pixels)", 4, True),
    1340: ("CH2 Zero Volt (uV)", 8, True),
    1348: ("CH2 Trigger Level Offset (uV)", 8, True),
    1356: ("CH2 Trigger Level (uV)", 8, True),
    1364: ("CH2 Trigger Level (pixels)", 4, True),
    1368: ("CH2 Coupling", 1, False),
    1369: ("CH2 Probe Mode", 1, False),
    1372: ("CH2 Enabled Measurements", 4, False),   # Bitfield
    1376: ("CH2 Gain Cal", 2, False),
    1380: ("CH2 Vert Offset Buffer (uV)", 8, True),
    1388: ("CH2 Vert Scroll Offset", 4, False),
    1392: ("Sample Rate (Meas)", 8, False),         # Measurements/display sample rate
    1400: ("Pre-Trigger Samples", 4, False),        # rec/2 + delay*fs, clamped to [0, rec]
    1404: ("Post-Trigger Samples", 4, False),       # record length - pre-trigger
    1408: ("Display Start Column", 2, False),
    1410: ("Display End Column", 2, False),
    1412: ("0x2001ddb4", 4, False),
    1416: ("Buffer Ready Flag?", 1, False),
    1417: ("Trigger Armed Flag?", 1, False),
    1418: ("Roll Mode Flag?", 1, False),            # Active >= 100ms
    1420: ("Scan Mode", 1, False),                  # 0=Idle/Start?, 1=Pre-Trigger/Arming?, 2=Block?, 3=Roll
    1421: ("Roll Mode Enable", 1, False),
    1422: ("Block Mode Enable?", 1, False),
    1423: ("Fast Render Enable", 1, False),         # Skips buffer and uses screen data for calculations, active < 100ns
    1424: ("Render Scale Factor", 4, False),        # Decimation factor?
    1428: ("Mid-Speed Config?", 1, False),
    1429: ("ADC Interleave Enable?", 1, False),     # 0=Normal, 1=Interleaved?
    1430: ("Persistence Mode", 1, False),
    1431: ("Roll Menu Enable", 1, False),
    1432: ("Language", 1, False),
    1433: ("0x2001ddc9", 1, False),
    1434: ("SigGen Enable", 1, False),
    1436: ("SigGen Duty Cycle", 4, False),          # 0.1%
    1440: ("SigGen Frequency", 4, False),           # 0.1Hz
    1444: ("SigGen Amplitude (mV)", 4, False),
    1448: ("SigGen Waveform", 1, False),
    1449: ("Key Beep Enable", 1, False),
    1450: ("Screen Brightness", 1, False),          # 0-80
    1451: ("Auto-off Enable", 1, False),
    1452: ("FFT Mode", 1, False),                   # 0=Off, 1=Log, 2=Lin, 3=Music
    1453: ("Cursors X Enable", 1, False),
    1454: ("Cursors Y Enable", 1, False),
    1456: ("Cursor X1 Pos", 2, True),
    1458: ("Cursor X2 Pos", 2, True),
    1460: ("Cursor Y1 Pos", 2, True),
    1462: ("Cursor Y2 Pos", 2, True),
    1464: ("CH1 Color Index", 2, True),
    1466: ("Meas Color", 2, False),
    1468: ("Settings-Grid Style", 1, False),        # 0=None, 1=Dash, 2=Solid
    1469: ("HiRate Enable", 1, False),
    1470: ("ETS Enable?", 1, False),
    1471: ("0x2001ddef", 1, False),
    1472: ("Voice Control", 1, False),
    1473: ("Settings-Grid Color", 1, False),        # 0=Dark, 1=Medium, 2=Light
    1474: ("Settings-CH2 Color", 1, False),         # 0=Green, 1=Purple, 2=Cyan
    1475: ("Settings-DMM Window", 1, False),        # 0=Window, 1=Fullscreen
    1476: ("Settings-LCD Invert", 1, False),
    1477: ("0x2001ddf5", 1, False),
    1478: ("Freq Meter Enable", 1, False),
    1480: ("Freq Meter Ref Clock (Hz)", 4, False),  # 10000600
    1485: ("0x2001ddfd", 1, False),
    1486: ("Active Channel", 1, False),             # 0=Ch1, 1=Ch2, 2=Math
    1487: ("Fine-Coarse Movement?", 1, False),
    1488: ("0x2001de00", 1, False),
    1489: ("0x2001de01", 1, False),
    1490: ("0x2001de02", 1, False),
    1491: ("Settings Changed Flag?", 1, False),
    1492: ("0x2001de04", 1, False),
    1493: ("0x2001de05", 1, False),
    1494: ("0x2001de06", 2, False),
    1496: ("HighSpeed Sys Flag?", 1, False),
    1497: ("0x2001de09", 1, False),
    1498: ("0x2001de0a", 1, False),
    1499: ("Long Memory Enable?", 1, False),
    1500: ("0x2001de0c", 1, False),
    1501: ("0x2001de0d", 1, False),
    1502: ("0x2001de0e", 1, False),
    1503: ("0x2001de0f", 1, False),
    1504: ("Force Fine Movement?", 1, False),
    1505: ("0x2001de11", 1, False),
    1506: ("0x2001de12", 1, False),
    1507: ("0x2001de13", 1, False),
    1508: ("Zoom Timebase Index", 1, False),
    1509: ("Zoom Mode", 1, False),
    1512: ("Zoom Center Pos (ps)", 8, True),
    1520: ("Zoom Timing Pass Flag", 1, False),      # Set only while zoomed timing is recomputed
    1521: ("Counter Enable", 1, False),
    1522: ("0x2001de22", 2, False),
    1524: ("CH1 20Mhz Limit", 1, False),
    1525: ("CH2 20Mhz Limit", 1, False),
    1527: ("Trigger Mode 2?", 1, False),            # 0=Auto, 1=Normal
    1528: ("Channel Math Mode", 1, False),          # 0=Off, 1=Add, 2=Subtract
    1529: ("Roll Direction", 1, False),             # 0=Left, 1=Right
    1532: ("0x2001de2c", 2, False),
    1536: ("0x2001de30", 4, False),
    1540: ("0x2001de34", 2, False),
}

# Data offset, label, bytes, signed
DATA_DSO2512G_V2 = {
    1200: ("Run State", 1, False),                  # 0=Stop, 1=Run, 2=Wait
    1201: ("System State", 1, False),
    1202: ("CH2 Enabled", 1, False),
    1204: ("1204", 4, False),
    1208: ("Buffer Depth", 8, False),
    1216: ("HW Buffer Wrap Val?", 4, False),
    1220: ("Timebase Index", 1, False),             # 2=5ns...30=10s
    1224: ("Timebase Value (ns/div)", 8, False),
    1232: ("Horiz Trigger Delay (ps)", 8, True),
    1240: ("View Scroll Offset (ps)?", 8, True),
    1248: ("Buffer Trigger Index?", 4, False),
    1252: ("Hardware Trigger Delay?", 4, False),
    1256: ("Sample Rate (HW)", 8, False),           # Hardware sample rate Hz/100
    1264: ("Trigger Source", 1, False),             # 0=Ch1, 1=Ch2
    1265: ("Trigger Mode", 1, False),               # 0=Auto, 1=Normal
    1266: ("Trigger Edge", 1, False),               # 0=Rise, 1=Fall
    1267: ("Trigger Level Mode", 1, False),         # 0=Auto, 1=Manual
    1268: ("Buffer Write Pointer?", 4, False),
    1272: ("Trigger Level ADC", 2, False),          # 0-255
    1274: ("CH1 V/Div Index", 1, False),
    1276: ("CH1 Volt Scale (uV)", 4, False),
    1280: ("CH1 Zero Volt (pixels)", 4, True),
    1284: ("1284", 4, False),
    1288: ("CH1 Zero Volt (uV)", 8, True),
    1296: ("CH1 Trigger Level Offset (uV)", 8, True),
    1304: ("CH1 Trigger Level (uV)", 8, True),
    1312: ("CH1 Trigger Level (pixels)", 4, True),
    1316: ("CH1 Coupling", 1, False),               # 0=DC, 1=AC
    1317: ("CH1 Probe Mode", 1, False),
    1320: ("CH1 Enabled Measurements", 4, False),   # Bitfield
    1324: ("CH1 Gain Cal", 2, False),
    1328: ("CH1 Vert Offset Buffer (uV)", 8, True),
    1336: ("CH1 Vert Scroll Offset", 4, False),
    1340: ("CH2 V/Div Index", 1, False),
    1344: ("CH2 Volt Scale (uV)", 4, False),
    1348: ("CH2 Zero Volt (pixels)", 4, True),
    1352: ("CH2 Zero Volt (uV)", 8, True),
    1360: ("CH1 Trigger Level Offset (uV)", 8, True),
    1368: ("CH2 Trigger Level (uV)", 8, True),
    1376: ("CH2 Trigger Level (pixels)", 4, True),
    1380: ("CH2 Coupling", 1, False),               # 0=DC, 1=AC
    1381: ("CH2 Probe Mode", 1, False),
    1384: ("CH2 Enabled Measurements", 4, False),   # Bitfield
    1388: ("CH2 Gain Cal", 2, False),
    1392: ("CH2 Vert Offset Buffer (uV)", 8, True),
    1400: ("CH2 Vert Scroll Offset", 4, False),
    1404: ("1404", 4, False),
    1408: ("Sample Rate (Meas)", 8, False),         # Measurements/display sample rate
    1416: ("Pre-Trigger Samples", 4, False),
    1420: ("Post-Trigger Samples", 4, False),
    1424: ("Display Start Column", 2, False),
    1426: ("Display End Column", 2, False),
    1428: ("Samples Per Pixel", 4, False),          # float, raw samples / display pixels
    1432: ("1432", 1, False),
    1433: ("Acq Trigger Pending Flag", 1, False),
    1434: ("1434", 1, False),
    1435: ("1435", 1, False),
    1436: ("Acq State Machine", 1, False),          # 0=Idle, 1=Pre-fill, 2=WaitTrigger, 3=Roll
    1437: ("Roll Mode Enable", 1, False),
    1438: ("Zoom Mode Enable", 1, False),
    1439: ("1439", 1, False),
    1440: ("Interpolation Factor x10000", 4, False),
    1444: ("1444", 1, False),
    1446: ("1446", 1, False),
    1447: ("Persistence Mode", 1, False),
    1448: ("Language", 1, False),
    1449: ("1449", 1, False),
    1450: ("SigGen Enable", 1, False),
    1452: ("SigGen Duty Cycle", 4, False),          # 0.1%
    1456: ("SigGen Frequency", 4, False),           # 0.1Hz
    1460: ("SigGen Amplitude (mV)", 4, False),
    1464: ("SigGen Waveform", 1, False),
    1465: ("1465", 1, False),
    1466: ("Screen Brightness", 1, False),
    1467: ("1467", 1, False),
    1468: ("FFT Mode", 1, False),
    1469: ("Cursors X Enable", 1, False),
    1470: ("Cursors Y Enable", 1, False),
    1472: ("Cursor X1 Pos", 2, True),
    1474: ("Cursor X2 Pos", 2, True),
    1476: ("Cursor Y1 Pos", 2, True),
    1478: ("Cursor Y2 Pos", 2, True),
    1480: ("CH1 Color Index", 2, True),
    1482: ("Meas Color", 2, False),
    1484: ("Gridline Mode", 1, False),
    1485: ("Averaging Enable", 1, False),
    1486: ("Interpolation Enable", 1, False),
    1494: ("Freq Meter Enable", 1, False),
    1496: ("Freq Meter Ref Clock (Hz)?", 4, False),
    1501: ("Current Button Event", 1, False),
    1502: ("Active Channel", 1, False),             # 0=Ch1, 1=Ch2
    1504: ("1504", 1, False),
    1505: ("1505", 1, False),
    1506: ("1506", 1, False),
    1507: ("UI Refresh?", 1, False),
    1508: ("1508", 1, False),
    1509: ("Display Update?", 1, False),
    1510: ("Saved Trigger Level ADC", 2, False),
    1512: ("1512", 1, False),
    1514: ("1514", 1, False),
    1515: ("1515", 1, False),
    1519: ("1519", 1, False),
    1520: ("1520", 1, False),
    1522: ("1522", 1, False),
    1524: ("Zoom Timebase Index", 1, False),
    1525: ("Zoom Mode", 1, False),
    1528: ("Zoom Center Pos (ps)", 8, False),
    1536: ("DSP Filter Enable?", 1, False),
    1537: ("Counter Enable?", 1, False),
    1538: ("FFT Cursor Pos", 2, False),
    1540: ("CH1 20Mhz Limit", 1, False),
    1541: ("CH2 20Mhz Limit", 1, False),
    1542: ("Settings-LCD Invert", 1, False),
    1543: ("FPGA Trigger Armed?", 1, False),
}

# Data offset, label, bytes, signed
DATA_DSO2512G_V1 = {
    1200: ("Run State", 1, False),                  # 0=Stop, 1=Run, 2=Wait
    1201: ("System State", 1, False),
    1202: ("CH2 Enabled", 1, False),
    1204: ("1204", 4, False),
    1208: ("Buffer Depth", 8, False),
    1216: ("HW Buffer Wrap Val?", 4, False),
    1220: ("Timebase Index", 1, False),             # 2=5ns...30=10s
    1224: ("Timebase Value (ns/div)", 8, False),
    1232: ("Horiz Trigger Delay (ps)", 8, True),
    1240: ("View Scroll Offset (ps)?", 8, True),
    1248: ("Buffer Trigger Index?", 4, False),
    1252: ("Hardware Trigger Delay?", 4, False),
    1256: ("Sample Rate (HW)", 8, False),           # Hardware sample rate Hz/100
    1264: ("Trigger Source", 1, False),             # 0=Ch1, 1=Ch2
    1265: ("Trigger Mode", 1, False),               # 0=Auto, 1=Normal
    1266: ("Trigger Edge", 1, False),               # 0=Rise, 1=Fall
    1267: ("Trigger Level Mode", 1, False),         # 0=Auto, 1=Manual
    1268: ("Buffer Write Pointer?", 4, False),
    1272: ("Trigger Level ADC", 2, False),          # 0-255
    1274: ("CH1 V/Div Index", 1, False),
    1276: ("CH1 Volt Scale (uV)", 4, False),
    1280: ("CH1 Zero Volt (pixels)", 4, True),
    1284: ("1284", 4, False),
    1288: ("CH1 Zero Volt (uV)", 8, True),
    1296: ("CH1 Trigger Level Offset (uV)", 8, True),
    1304: ("CH1 Trigger Level (uV)", 8, True),
    1312: ("CH1 Trigger Level (pixels)", 4, True),
    1316: ("CH1 Coupling", 1, False),               # 0=DC, 1=AC
    1317: ("CH1 Probe Mode", 1, False),
    1320: ("CH1 Enabled Measurements", 4, False),   # Bitfield
    1324: ("CH1 Gain Cal", 2, False),
    1328: ("CH1 Vert Offset Buffer (uV)", 8, True),
    1336: ("CH1 Vert Scroll Offset", 4, False),
    1340: ("CH2 V/Div Index", 1, False),
    1344: ("CH2 Volt Scale (uV)", 4, False),
    1348: ("CH2 Zero Volt (pixels)", 4, True),
    1352: ("CH2 Zero Volt (uV)", 8, True),
    1360: ("CH1 Trigger Level Offset (uV)", 8, True),
    1368: ("CH2 Trigger Level (uV)", 8, True),
    1376: ("CH2 Trigger Level (pixels)", 4, True),
    1380: ("CH2 Coupling", 1, False),               # 0=DC, 1=AC
    1381: ("CH2 Probe Mode", 1, False),
    1384: ("CH2 Enabled Measurements", 4, False),   # Bitfield
    1388: ("CH2 Gain Cal", 2, False),
    1392: ("CH2 Vert Offset Buffer (uV)", 8, True),
    1400: ("CH2 Vert Scroll Offset", 4, False),
    1404: ("1404", 4, False),
    1408: ("Sample Rate (Meas)", 8, False),         # Measurements/display sample rate/10
    1416: ("Pre-Trigger Samples", 4, False),
    1420: ("Post-Trigger Samples", 4, False),
    1424: ("Display Start Column", 2, False),
    1426: ("Display End Column", 2, False),
    1428: ("Samples Per Pixel", 4, False),          # float, raw samples / display pixels
    1432: ("1432", 1, False),
    1433: ("Acq Trigger Pending Flag", 1, False),
    1434: ("1434", 1, False),
    1435: ("1435", 1, False),
    1436: ("Acq State Machine", 1, False),          # 0=Idle, 1=Pre-fill, 2=WaitTrigger, 3=Roll
    1437: ("Roll Mode Enable", 1, False),
    1438: ("Zoom Mode Enable", 1, False),
    1439: ("1439", 1, False),
    1440: ("Interpolation Factor x10000", 4, False),
    1444: ("1444", 1, False),
    1446: ("Persistence Mode", 1, False),
    1447: ("1447", 1, False),
    1448: ("Language", 1, False),
    1449: ("1449", 1, False),
    1450: ("SigGen Enable", 1, False),
    1452: ("SigGen Duty Cycle", 4, False),          # 0.1%
    1456: ("SigGen Frequency", 4, False),           # 0.1Hz
    1460: ("SigGen Waveform", 1, False),
    1461: ("1461", 1, False),
    1462: ("Screen Brightness", 1, False),
    1463: ("1463", 1, False),
    1464: ("FFT Mode", 1, False),
    1465: ("Cursors X Enable", 1, False),
    1466: ("Cursors Y Enable", 1, False),
    1468: ("Cursor X1 Pos", 2, True),
    1470: ("Cursor X2 Pos", 2, True),
    1472: ("Cursor Y1 Pos", 2, True),
    1474: ("Cursor Y2 Pos", 2, True),
    1476: ("CH1 Color Index", 2, True),
    1478: ("Meas Color", 2, False),
    1480: ("Gridline Mode", 1, False),
    1481: ("Averaging Enable", 1, False),
    1482: ("Interpolation Enable", 1, False),
    1483: ("Button Event", 1, False),
    1484: ("Active Channel", 1, False),             # 0=Ch1, 1=Ch2
    1486: ("1486", 1, False),
    1487: ("1487", 1, False),
    1488: ("1488", 1, False),
    1489: ("UI Refresh Flag", 1, False),
    1490: ("1490", 1, False),
    1491: ("1491", 1, False),
    1492: ("Saved Trigger Level ADC", 2, False),
    1494: ("1494", 1, False),
    1495: ("1495", 1, False),
    1496: ("1496", 1, False),
    1497: ("1497", 1, False),
    1498: ("1498", 1, False),
    1499: ("1499", 1, False),
    1500: ("Zoom Timebase Index", 1, False),
    1501: ("Zoom Mode", 1, False),
    1504: ("Zoom Center Pos (ps)", 8, True),
    1512: ("1512", 1, False),
}

CONFIG_DSO3D12 = {
    'name': 'DSO3D12',
    'map': DATA_DSO3D12,
    'settings_offset': 1200,
    'settings_length': 340,
    'settings_address': 0x2001dce0, # v3.0.7-III
    'meas_ch1_offset': 1540,
    'meas_ch2_offset': 1640,
    'meas_length': 100,
    'meas_flag_offset_ch1': 1308,
    'meas_flag_offset_ch2': 1372,
    'tb_idx_map_offset': 0,
}
CONFIG_DSO2512G_V2 = {
    'name': 'DSO2512G',
    'map': DATA_DSO2512G_V2,
    'settings_offset': 1200,
    'settings_length': 344,
    'settings_address': 0x801b1fb8, # v2.0.3-III
    'meas_ch1_offset': 1544,
    'meas_ch2_offset': 1648,
    'meas_length': 104,
    'meas_flag_offset_ch1': 1320,
    'meas_flag_offset_ch2': 1384,
    'tb_idx_map_offset': 0,
}
CONFIG_DSO2512G_V1 = {
    'name': 'DSO2512G',
    'map': DATA_DSO2512G_V1,
    'settings_offset': 1200,
    'settings_length': 320,
    'settings_address': 0x8019d7a8, # v1.3.0c
    'meas_ch1_offset': 1520,
    'meas_ch2_offset': 1624,
    'meas_length': 104,
    'meas_flag_offset_ch1': 1320,
    'meas_flag_offset_ch2': 1384,
    'tb_idx_map_offset': 0
}
data_config = CONFIG_DSO3D12
debug_diff_data = None


def get_val(data, offset, size, signed=False):
    if offset + size > len(data): return 0
    chunk = data[offset : offset+size]
    if size == 1: return chunk[0]
    elif size == 2: return struct.unpack('<h' if signed else '<H', chunk)[0]
    elif size == 4: return struct.unpack('<i' if signed else '<I', chunk)[0]
    elif size == 8: return struct.unpack('<q' if signed else '<Q', chunk)[0]
    return 0


def format_voltage_val(uvolts, probe_mode=0):
    volts = uvolts / 1000000.0
    val = volts * (10 ** probe_mode)
    abs_val = abs(val)
    if abs_val == 0: return "0.00V"
    if abs_val < 0.99995e-3: return f"{val * 1000000:.1f}uV"
    if abs_val < 0.99995: return f"{val * 1000:.1f}mV"
    if abs_val < 10.0: return f"{val:.2f}V"
    if abs_val < 100.0: return f"{val:.1f}V"
    return f"{val:.0f}V"


def format_time_val(seconds):
    val = abs(seconds)
    if val == 0: return "0.00s"
    if val < 999.5e-9:
        ns = val * 1e9
        if ns >= 100: return f"{ns:.0f}ns"
        if ns >= 10: return f"{ns:.1f}ns"
        return f"{ns:.2f}ns"
    if val < 999.5e-6:
        us = val * 1e6
        if us >= 100: return f"{us:.0f}us"
        if us >= 10: return f"{us:.1f}us"
        return f"{us:.2f}us"
    if val < 0.9995:
        ms = val * 1e3
        if ms >= 100: return f"{ms:.0f}ms"
        if ms >= 10: return f"{ms:.1f}ms"
        return f"{ms:.2f}ms"
    if val >= 100: return f"{val:.0f}s"
    if val >= 10: return f"{val:.1f}s"
    return f"{val:.2f}s"


def format_freq(hz):
    if hz < 0: hz = 0
    if hz >= 999500:
        val = hz / 1000000.0
        unit = "MHz"
    elif hz >= 999.5:
        val = hz / 1000.0
        unit = "kHz"
    else:
        val = hz
        unit = "Hz"
    if val >= 100: return f"{val:.0f}{unit}"
    elif val >= 10: return f"{val:.1f}{unit}"
    else: return f"{val:.2f}{unit}"


def format_sample_rate(hz):
    if hz < 0: hz = 0
    elif hz >= 999500:
        val = hz / 1000000.0
        unit = "MSa/s"
    elif hz >= 999.5:
        val = hz / 1000.0
        unit = "kSa/s"
    else:
        val = hz
        unit = "Sa/s"
    if val >= 100: return f"{val:.0f}{unit}"
    elif val >= 10: return f"{val:.1f}{unit}"
    else: return f"{val:.2f}{unit}"


def format_delay_val(seconds):
    val = abs(seconds)
    if val == 0: return "0.00s"
    if val < 999.95e-9: return f"{seconds * 1e9:.1f}ns"
    if val < 999.9995e-6: return f"{seconds * 1e6:.3f}us"
    if val < 0.9999995: return f"{seconds * 1e3:.3f}ms"
    return f"{seconds:.3f}s"


def parse_siggen_mode(val):
    if val == 2500: return "=2.5V (Downscale 0.87)"
    if val == 2510: return "2.5V (Downscale 0.77 + Gain?)"
    if val == 3000: return "=3.0V (Fullscale)"
    if val == 3010: return "3.0V (Downscale 0.91 + Gain?)"
    return f"{val/1000:.1f}V (Unknown)"


def debug_diff(current_data):
    global debug_diff_data
    chunk_start = 1200
    chunk_len = 340
    if len(current_data) < (chunk_start + chunk_len): return
    curr_chunk = current_data[chunk_start : chunk_start + chunk_len]
    if debug_diff_data is None:
        print("\nDebug - initial values:")
        debug_diff_data = bytes([0] * chunk_len)
    else: print("Debug:")
    changes = []
    covered_indices = set()
    for abs_offset, (label, size, is_signed) in data_config['map'].items():
        rel_offset = abs_offset - chunk_start
        if rel_offset < 0 or rel_offset >= chunk_len: continue
        for k in range(size): covered_indices.add(rel_offset + k)
        chunk_old = debug_diff_data[rel_offset : rel_offset + size]
        chunk_new = curr_chunk[rel_offset : rel_offset + size]
        val_old = int.from_bytes(chunk_old, byteorder='little', signed=is_signed)
        val_new = int.from_bytes(chunk_new, byteorder='little', signed=is_signed)
        if val_old != val_new:
            hex_old = f"0x{int.from_bytes(chunk_old, byteorder='little', signed=False):X}"
            hex_new = f"0x{int.from_bytes(chunk_new, byteorder='little', signed=False):X}"
            changes.append((abs_offset, f"[{abs_offset}] {label:<25} : {hex_old} > {hex_new} ({val_old} > {val_new})"))
    i = 0
    while i < chunk_len:
        if i in covered_indices:
            i += 1
            continue
        byte_old = debug_diff_data[i]
        byte_new = curr_chunk[i]
        if byte_old != byte_new:
            addr = data_config['settings_address'] + i
            abs_offset = chunk_start + i
            changes.append((abs_offset, f"[{abs_offset}] 0x{addr:X} UNLABELED      : 0x{byte_old:02X} > 0x{byte_new:02X} ({byte_old} > {byte_new})"))
        i += 1
    if not changes: print("Debug: No changed data\n")
    else:
        changes.sort(key=lambda x: x[0])
        for _, msg in changes: print(msg)
        print("\n")
    debug_diff_data = curr_chunk


def parse_debug(buf, f, config=None):
    cfg = config or data_config
    start_offset = cfg['settings_offset']
    byte_count = cfg['settings_length']
    end_offset = start_offset + byte_count
    header = f"{'Address':<10} | {'File':<4} | {'Label':<32} | {'Hex':<18} | {'Decimal'}"
    f.write("\nDebug:\n")
    f.write(header + "\n")
    f.write("-" * len(header))
    f.write("---------------\n")
    curr = start_offset
    data_map = cfg['map']
    while curr < end_offset:
        hw_addr = cfg['settings_address'] + (curr - start_offset)
        if curr in data_map:
            label, size, is_signed = data_map[curr]
            chunk = buf[curr : curr + size]
            if len(chunk) < size:
                f.write(f"{hw_addr:#010x} | {curr:<4} | {label:<32} | {'ERR':<18} | End of Buffer\n")
                break
            val_int = int.from_bytes(chunk, byteorder='little', signed=is_signed)
            val_hex = f"0x{int.from_bytes(chunk, byteorder='little', signed=False):0{size*2}X}"
            f.write(f"{hw_addr:#010x} | {curr:<4} | {label:<32} | {val_hex:<18} | {val_int}\n")
            curr += size
        else:
            if curr < len(buf):
                val = buf[curr]
                val_hex = f"0x{val:02X}"
                f.write(f"{hw_addr:#010x} | {curr:<4} | {'-':<32} | {val_hex:<18} | {val}\n")
            else: f.write(f"{hw_addr:#010x} | {curr:<4} | {'EOF':<32} | {'-':<18} | -\n")
            curr += 1


def parse_all_measurements(data, offset, probe_mode=0):
    length = data_config['meas_length']
    chunk = data[offset : offset+length]
    if len(chunk) < 100: return []
    measurements = []
    try:
        vals = struct.unpack('<12q2h', chunk[:100])
        measurements.append(("Freq", format_freq(vals[11] / 1000000.0)))
        measurements.append(("T", format_time_val(vals[10] / 1e12)))
        measurements.append(("+T", format_time_val(vals[8] / 1e12)))
        measurements.append(("-T", format_time_val(vals[9] / 1e12)))
        measurements.append(("+Duty", f"{vals[12]/10.0:.1f}%"))
        measurements.append(("-Duty", f"{vals[13]/10.0:.1f}%"))
        v_map = [
            ("PkPk", 0), ("Amp", 1), ("Max", 4), ("Min", 5),
            ("Top", 2), ("Base", 3), ("Avg", 6), ("RMS", 7)
        ]
        for label, idx in v_map: measurements.append((label, format_voltage_val(vals[idx], probe_mode)))
    except Exception as e: measurements.append(("Error", f"Parse: {e}"))
    return measurements


def parse_active_measurements_list(data, offset, flag_offset, probe_mode=0, forced_bits=None):
    chunk = data[offset : offset+100]
    if len(chunk) < 100: return []
    try:
        vals = struct.unpack('<12q2h', chunk)
        flags = get_val(data, flag_offset, 2)
        active_meas = []
        if forced_bits is not None:  enabled_bits = forced_bits
        else:  enabled_bits = [bit for bit in range(16) if (flags & (1 << bit))]
        for bit in enabled_bits:
            if bit in MEASUREMENT_FLAGS:
                label, val_idx, mtype = MEASUREMENT_FLAGS[bit]
                if mtype == "F": active_meas.append((label, format_freq(vals[val_idx] / 1000000.0)))
                elif mtype == "D": active_meas.append((label, f"{vals[val_idx] / 10.0:.1f}%"))
                else:
                    raw = vals[val_idx]
                    if mtype == "V": active_meas.append((label, format_voltage_val(raw, probe_mode)))
                    elif mtype == "T": active_meas.append((label, format_time_val(raw / 1e12)))
        return active_meas
    except Exception as e: return []


def apply_plot_style():
    plt.rcParams.update({
        "figure.facecolor": "black",
        "axes.facecolor": "black",
        "axes.edgecolor": "#444444",
        "axes.linewidth": 1,
        "axes.grid": False,
        "text.color": "#AAAAAA",
        "font.family": "sans-serif",
        "font.size": 12,
        "xtick.color": "#AAAAAA",
        "ytick.color": "#AAAAAA",
        "savefig.facecolor": "black",
        "savefig.edgecolor": "black"
    })


def draw_measurement_column(ax, x, y_top, ch_number, color, meas_list, enabled):
    header_w = 46
    header_h = 12
    if enabled:
        rect = patches.FancyBboxPatch((x, y_top - header_h), header_w, header_h, boxstyle="round,pad=1", fc=color, ec="none")
        ax.add_patch(rect)
        ax.text(x + header_w / 2, y_top - header_h / 2 - 1, f"CH{ch_number}", ha="center", va="center", color="#1C1C1C", fontsize=14, fontweight="bold")
        y_cursor = y_top - header_h - 5
        line_spacing = 14
        label_x = x
        value_x = x + 20
        for label, val in meas_list:
            ax.text(label_x, y_cursor, f"{label}", ha="left", va="top", color="#AAAAAA", fontsize=11, fontfamily="monospace")
            ax.text(value_x, y_cursor, f"{val}", ha="left", va="top", color="white", fontsize=11, fontweight="bold")
            y_cursor -= line_spacing
    else:
        rect = patches.FancyBboxPatch((x, y_top - header_h), header_w, header_h, boxstyle="round,pad=1", fc="#555555", ec="none")
        ax.add_patch(rect)
        ax.text(x + header_w / 2, y_top - header_h / 2 - 1, f"CH{ch_number}", ha="center", va="center", color="#333333", fontsize=14, fontweight="bold")

def save_csv(buf, filename, state):
    tb_ns = state.get("Timebase Value (ns/div)", 1000)
    time_step_s = (tb_ns / 25.0) / 1e9

    def get_voltage_scaling(ch_prefix):
        scale_uv = state.get(f"{ch_prefix} Volt Scale (uV)", 100000)
        offset_px = state.get(f"{ch_prefix} Vert Offset (pixels)", 0)
        probe = state.get(f"{ch_prefix} Probe Mode", 0)
        volts_per_pixel = (scale_uv / 1_000_000.0) / 25.0
        multiplier = 10 ** probe
        return volts_per_pixel * multiplier, offset_px
    c1_scale, c1_off = get_voltage_scaling("CH1")
    ch2_en = state.get("CH2 Enabled", 0)
    c2_scale, c2_off = get_voltage_scaling("CH2") if ch2_en else (0,0)
    raw_ch1_min = list(buf[0:300])
    raw_ch1_max = list(buf[300:600])
    raw_ch2_min = list(buf[600:900]) if ch2_en else [0]*300
    raw_ch2_max = list(buf[900:1200]) if ch2_en else [0]*300
    csv_filename = f"{filename}.csv"
    with open(csv_filename, 'w', newline='') as f:
        writer = csv.writer(f)
        headers = ["Time(s)", "CH1_Avg(V)", "CH1_Min(V)", "CH1_Max(V)"]
        if ch2_en: headers.extend(["CH2_Avg(V)", "CH2_Min(V)", "CH2_Max(V)"])
        writer.writerow(headers)
        for i in range(300):
            t = i * time_step_s
            def raw_to_volts(raw, scale, offset):
                pixel_val = 255 - raw
                return (pixel_val - 128 - offset) * scale
            v1_min = raw_to_volts(raw_ch1_min[i], c1_scale, c1_off)
            v1_max = raw_to_volts(raw_ch1_max[i], c1_scale, c1_off)
            v1_avg = (v1_min + v1_max) / 2.0
            row = [f"{t:.9f}", f"{v1_avg:.4f}", f"{v1_min:.4f}", f"{v1_max:.4f}"]
            if ch2_en:
                v2_min = raw_to_volts(raw_ch2_min[i], c2_scale, c2_off)
                v2_max = raw_to_volts(raw_ch2_max[i], c2_scale, c2_off)
                v2_avg = (v2_min + v2_max) / 2.0
                row.extend([f"{v2_avg:.4f}", f"{v2_min:.4f}", f"{v2_max:.4f}"])
            writer.writerow(row)
    print(f"Saved CSV:        {csv_filename}")


def save_capture_csv(filename, info, state, ch1, ch2, start, count, frac):
    if count <= 0:
        return
    rate = info["sample_rate_hz"]
    if rate > 0:
        time_step_s = 1.0 / rate
        first_time_s = -frac / rate
    else:
        tb_ns = state.get("Timebase Value (ns/div)", 1000)
        time_step_s = (tb_ns * 12.0 / count) / 1e9
        first_time_s = -frac * time_step_s

    def get_voltage_scaling(ch_prefix):
        scale_uv = state.get(f"{ch_prefix} Volt Scale (uV)", 100000)
        zero_offset_px = state.get(f"{ch_prefix} Zero Volt (pixels)", 0)
        probe = state.get(f"{ch_prefix} Probe Mode", 0)
        volts_per_pixel = (scale_uv / 1_000_000.0) / 25.0
        return volts_per_pixel * (10 ** probe), 128 + zero_offset_px

    c1_scale, c1_zero = get_voltage_scaling("CH1")
    ch2_en = bool(state.get("CH2 Enabled", 0) and ch2)
    c2_scale, c2_zero = get_voltage_scaling("CH2") if ch2_en else (0, 0)
    csv_filename = f"{filename}.csv"
    with open(csv_filename, 'w', newline='') as f:
        writer = csv.writer(f)
        headers = ["Time(s)", "CH1(V)"]
        if ch2_en: headers.append("CH2(V)")
        writer.writerow(headers)
        for i in range(count):
            t = first_time_s + i * time_step_s
            row = [f"{t:.12f}", f"{(ch1[start + i] - c1_zero) * c1_scale:.6f}"]
            if ch2_en:
                row.append(f"{(ch2[start + i] - c2_zero) * c2_scale:.6f}")
            writer.writerow(row)
    print(f"Saved CSV:        {csv_filename}")


def write_scope_text(buf, filename, state, config=None, title_text=None,
                     debug=False, write_file=True):
    cfg = config or data_config
    t_str = f_str = None
    ch_prefix = None
    y1_str = y2_str = dy_str = None
    with (open(f"{filename}.txt", 'w') if write_file else io.StringIO()) as f:
        if title_text: f.write(f"{title_text}\n\n")
        else: f.write(f"Zeeweii Screenshot Capture ({datetime.now():%Y-%m-%d %H:%M:%S})\n\n")

        # Run State
        run_str = RUN_STATES.get(state["Run State"], "Unknown")
        f.write(f"State:          {run_str}\n")

        # CH1
        c1_vdiv = format_voltage_val(VDIV_BASE_X1.get(state["CH1 V/Div Index"], 0), state["CH1 Probe Mode"])
        c1_cpl = "AC" if state["CH1 Coupling"] else "DC"
        c1_prb = PROBE_LABELS.get(state["CH1 Probe Mode"], "x1")
        c1_bw_limit = state.get("CH1 20Mhz Limit", 0)
        c1_bw_str = " | BW:20M" if c1_bw_limit == 1 else ""
        f.write(f"Channel 1:      {c1_vdiv}/div | {c1_cpl} | {c1_prb}{c1_bw_str}\n")

        # CH2
        c2_vdiv = format_voltage_val(VDIV_BASE_X1.get(state["CH2 V/Div Index"], 0), state["CH2 Probe Mode"])
        c2_cpl = "AC" if state["CH2 Coupling"] else "DC"
        c2_prb = PROBE_LABELS.get(state["CH2 Probe Mode"], "x1")
        c2_bw_limit = state.get("CH2 20Mhz Limit", 0)
        c2_bw_str = " | BW:20M" if c2_bw_limit == 1 else ""
        c2_status_str = " | Disabled" if state["CH2 Enabled"] == 0 else ""
        f.write("Channel 2:      ")
        f.write(f"{c2_vdiv}/div | {c2_cpl} | {c2_prb}{c2_bw_str}{c2_status_str}\n")

        # Timebase
        tb_str = TIMEBASE_LABELS.get(state["Timebase Index"], "?")
        f.write(f"Timebase:       {tb_str}/div\n")

        # Trigger
        trig_src_idx = state["Trigger Source"]
        if state["CH2 Enabled"]: trig_src = " | CH1" if trig_src_idx == 0 else " | CH2"
        else: trig_src = ""
        trig_mode = "Auto" if state.get("Trigger Mode", 0) == 0 else "Normal"
        trig_edge = "Rise" if state.get("Trigger Edge", 0) == 0 else "Fall"
        trig_probe = state.get(f"CH{trig_src_idx + 1} Probe Mode", 0)
        trig_uv = state.get(f"CH{trig_src_idx + 1} Trigger Level (uV)", 0)
        trig_lvl_str = format_voltage_val(trig_uv, trig_probe)
        f.write(f"Trigger:        {trig_mode} | {trig_edge} | {trig_lvl_str}{trig_src}\n")
        delay_ps = state.get("Horiz Trigger Delay (ps)", 0)
        delay_str = format_delay_val(delay_ps / 1e12)
        f.write(f"Horiz Delay:    {delay_str}\n")
        scroll_ps = state.get("View Scroll Offset (ps)", 0)
        offset_str = format_delay_val((delay_ps - scroll_ps) / 1e12) if scroll_ps else None
        if offset_str is not None:
            f.write(f"Horiz Offset:   {offset_str}\n")

        # System
        sr_val = state.get("Sample Rate (Meas)", 0)
        if cfg['name']=="DSO2512G": sr_val = sr_val * 10
        if sr_val == 0: sr_val = state.get("Sample Rate (HW)", 0) * 100
        sr_str = format_sample_rate(sr_val)
        f.write(f"Sample Rate:    {sr_str}\n")
        f.write("Signal Gen:     ")
        if state["SigGen Enable"]:
            wave = SIGGEN_PATTERNS.get(state.get("SigGen Waveform", 0), "Unknown")
            freq = state["SigGen Frequency"] / 10.0
            duty = state["SigGen Duty Cycle"] / 10.0
            if cfg['map']!=DATA_DSO2512G_V1:
                amp_mv = state.get("SigGen Amplitude (mV)", 0)
                amp_str = " | " + parse_siggen_mode(amp_mv)
            else: amp_str = ""
            f.write(f"{wave} | {format_freq(freq)} | {duty}%{amp_str}\n")
        else: f.write("Off\n")

        # Cursors
        if state.get("Cursors X Enable", 0):
            x1 = state["Cursor X1 Pos"]
            x2 = state["Cursor X2 Pos"]
            dx = abs(x2 - x1)
            tb_ns = state.get("Timebase Value (ns/div)", 0)
            dt_ns = dx * (tb_ns / 25.0)
            dt_s = dt_ns / 1e9
            t_str = format_time_val(dt_s)
            f_str = "---"
            if dt_s > 0: f_str = format_freq(1.0 / dt_s)
            f.write(f"Curs X:         {t_str} | {f_str}\n")
        if state.get("Cursors Y Enable", 0):
            y1 = state["Cursor Y1 Pos"]
            y2 = state["Cursor Y2 Pos"]
            act_ch = state.get("Active Channel", 0)
            if act_ch > 1: act_ch = 0
            ch_prefix = f"CH{act_ch+1}"
            probe_mode = state.get(f"{ch_prefix} Probe Mode", 0)
            volt_scale_uv = state.get(f"{ch_prefix} Volt Scale (uV)", 0)
            zero_offset = state.get(f"{ch_prefix} Zero Volt (pixels)", 0)
            dy = abs(y1 - y2)
            if volt_scale_uv > 0:
                uv_pixel = volt_scale_uv / 25.0
                y1_str = format_voltage_val((y1 - zero_offset) * uv_pixel, probe_mode)
                y2_str = format_voltage_val((y2 - zero_offset) * uv_pixel, probe_mode)
                dy_str = format_voltage_val(dy * uv_pixel, probe_mode)
            else:
                y1_str = y2_str = dy_str = "---"
            if state["CH2 Enabled"]: ch_str = " | " + ch_prefix
            else: ch_str = ""
            f.write(f"Curs Y:         Y1 {y1_str} | Y2 {y2_str} | dY {dy_str}{ch_str}\n")

        # Measurements
        f.write("\nCH1 Measurements:\n")
        meas_c1 = parse_all_measurements(buf, cfg['meas_ch1_offset'], state.get("CH1 Probe Mode", 0))
        for label, val in meas_c1: f.write(f"  {label:<6}: {val}\n")
        if state["CH2 Enabled"]:
            f.write("\nCH2 Measurements:\n")
            meas_c2 = parse_all_measurements(buf, cfg['meas_ch2_offset'], state.get("CH2 Probe Mode", 0))
            for label, val in meas_c2: f.write(f"  {label:<6}: {val}\n")

        # Debug
        if debug: parse_debug(buf, f, cfg)

    if write_file:
        print(f"Saved text:       {filename}.txt")
    return dict(run_str=run_str,
                c1_vdiv=c1_vdiv, c1_cpl=c1_cpl, c1_prb=c1_prb,
                c1_bw_limit=c1_bw_limit,
                c2_vdiv=c2_vdiv, c2_cpl=c2_cpl, c2_prb=c2_prb,
                c2_bw_limit=c2_bw_limit,
                tb_str=tb_str, trig_mode=trig_mode, trig_edge=trig_edge,
                trig_lvl_str=trig_lvl_str, delay_str=delay_str,
                h_offset_str=offset_str,
                t_str=t_str, f_str=f_str, ch_prefix=ch_prefix,
                y1_str=y1_str, y2_str=y2_str, dy_str=dy_str)


def process_capture(buf, filename, args):
    state = {}
    for offset, (label, size,is_signed) in data_config['map'].items(): state[label] = get_val(buf, offset, size, signed=is_signed)
    title_text = None
    if args.title:
        title_text = args.title
        if args.datetime: title_text += f" {datetime.now():%Y-%m-%d %H:%M:%S}"

    sidecar = args.debug or args.sidecar
    if sidecar:
        save_csv(buf, filename, state)

    disp = write_scope_text(buf, filename, state, data_config, title_text,
                            args.debug, write_file=sidecar)
    write_scope_image(buf, state, args, filename, title_text, disp)


def draw_wave(ax, x, lo, hi, color, zorder, layer=None, label=None):
    if layer is not None:
        if layer.get("density") is None:
            ax.plot(layer["x"], layer["p50"], color=color, lw=2.0,
                    solid_capstyle="round", solid_joinstyle="round",
                    zorder=zorder + 0.5, clip_on=True)
            return
        rgba = np.zeros(layer["density"].shape + (4,), dtype=float)
        rgba[..., :3] = to_rgb(color)
        rgba[..., 3] = layer["density"]
        ax.imshow(rgba, extent=layer["extent"], origin="lower",
                  interpolation="bilinear", aspect=1.0,
                  zorder=zorder - 0.6, clip_on=True)
        ax.fill_between(layer["x"], layer["p05"], layer["p95"], color=color,
                        alpha=0.10, linewidth=0, zorder=zorder, clip_on=True)
        ax.fill_between(layer["x"], layer["p25"], layer["p75"], color=color,
                        alpha=0.28, linewidth=0, zorder=zorder, clip_on=True)
        ax.plot(layer["x"], layer["p50"], color=color, lw=1.1,
                zorder=zorder + 0.5, clip_on=True)
        ax.plot(layer["x"], layer["lo"], color=color, lw=0.3, alpha=0.7,
                zorder=zorder, clip_on=True)
        ax.plot(layer["x"], layer["hi"], color=color, lw=0.3, alpha=0.7,
                zorder=zorder, clip_on=True)
        return
    ax.fill_between(x, lo, hi, color=color, alpha=0.5, label=label, zorder=zorder, clip_on=True)
    ax.plot(x, lo, color=color, lw=0.5, zorder=zorder, clip_on=True)
    ax.plot(x, hi, color=color, lw=0.5, zorder=zorder, clip_on=True)


def write_scope_image(buf, state, args, filename, title_text, disp, config=None,
                      layers=None, window=None):
    cfg = config or data_config
    run_str = disp["run_str"]
    c1_vdiv, c1_cpl, c1_prb = disp["c1_vdiv"], disp["c1_cpl"], disp["c1_prb"]
    c1_bw_limit = disp["c1_bw_limit"]
    c2_vdiv, c2_cpl, c2_prb = disp["c2_vdiv"], disp["c2_cpl"], disp["c2_prb"]
    c2_bw_limit = disp["c2_bw_limit"]
    tb_str = disp["tb_str"]
    trig_mode = disp["trig_mode"]
    trig_edge = disp["trig_edge"]
    trig_lvl_str = disp["trig_lvl_str"]
    delay_str = disp["delay_str"]
    h_offset_str = disp["h_offset_str"]
    t_str, f_str = disp["t_str"], disp["f_str"]
    ch_prefix = disp["ch_prefix"]
    y1_str, y2_str, dy_str = disp["y1_str"], disp["y2_str"], disp["dy_str"]

    # Image
    apply_plot_style()
    ADC_CENTER = 128
    ADC_DIV = 25
    grid_w = 12 * ADC_DIV
    grid_h = 8 * ADC_DIV
    plot_top = ADC_CENTER + (4 * ADC_DIV)
    plot_bot = ADC_CENTER - (4 * ADC_DIV)
    ch1_color = args.color1
    ch2_color = args.color2
    if ch1_color is None:
        ch1_color = "#e2e500"
    if ch2_color is None:
        color_val = state.get("Settings-CH2 Color", 0)
        if color_val == 0: ch2_color =  "#00bf00"  # Green
        elif color_val == 1: ch2_color = "#bf00bf" # Purple
        elif color_val == 2: ch2_color = "#00bfbc" # Cyan

    # Figure
    apply_plot_style()
    grid_in_w = 8.0
    grid_in_h = grid_in_w * (grid_h / grid_w)
    right_panel_w_in = 3.0
    bottom_panel_h_in = 0.5
    title_height_in = 0.4 if title_text else 0.0
    fig_width_in = grid_in_w + right_panel_w_in
    fig_height_in = grid_in_h + bottom_panel_h_in + title_height_in + 0.1
    fig = plt.figure(figsize=(fig_width_in, fig_height_in))
    if title_text:
        ax_title = fig.add_axes([0, 1 - title_height_in / fig_height_in, 1, title_height_in / fig_height_in])
        ax_title.axis("off")
        ax_title.add_patch(patches.Rectangle((0, 0), 1, 1, transform=ax_title.transAxes, fc="#1C1C1C", ec="none", zorder=1))
        ax_title.text(0.02, 0.4, title_text, ha="left", va="center", fontsize=16, fontweight="bold", color="white", zorder=2, transform=ax_title.transAxes)
    grid_w_norm = grid_in_w / fig_width_in
    grid_h_norm = grid_in_h / fig_height_in
    right_panel_w_norm = right_panel_w_in / fig_width_in
    bottom_panel_h_norm = (bottom_panel_h_in / fig_height_in)

    # Grid
    ax_grid = fig.add_axes([0.02, bottom_panel_h_norm + 0.02, grid_w_norm - 0.03, grid_h_norm - 0.03])
    ax_grid.set_xlim(0, grid_w)
    ax_grid.set_ylim(plot_bot, plot_top)
    ax_grid.set_aspect(1)
    x_ticks = np.linspace(0, grid_w, 13)
    y_ticks = np.arange(plot_bot, plot_top + 1, ADC_DIV)
    for x in x_ticks: ax_grid.axvline(x, color='#444444', linestyle='--', linewidth=0.5, alpha=0.7, zorder=1)
    for y in y_ticks: ax_grid.axhline(y, color='#444444', linestyle='--', linewidth=0.5, alpha=0.7, zorder=1)
    ax_grid.axhline(ADC_CENTER, color='#666666', linewidth=1, zorder=1)
    ax_grid.axvline(grid_w / 2, color='#666666', linewidth=1, zorder=1)
    div_width = grid_w / 12
    for x in np.arange(0, grid_w + 0.01, div_width):
        for i in range(5):
            x_pos = x + (div_width * (i / 5.0))
            ax_grid.plot([x_pos, x_pos], [ADC_CENTER-2, ADC_CENTER+2], color='#666666', lw=0.8)
    for y in y_ticks:
        for i in range(5):
            y_pos = y + (ADC_DIV * (i / 5.0))
            ax_grid.plot([148, 152], [y_pos, y_pos], color='#666666', lw=0.8)
    border = patches.Rectangle((0, plot_bot), grid_w, plot_top - plot_bot, linewidth=0, facecolor='none', zorder=9)
    border.set_path_effects([pe.Stroke(linewidth=2, foreground="#666666"), pe.Normal()])
    ax_grid.add_patch(border)
    ax_grid.set_xticks(x_ticks)
    ax_grid.set_yticks(y_ticks)
    ax_grid.set_xticklabels([])
    ax_grid.set_yticklabels([])
    ax_grid.tick_params(axis='both', which='both', length=0)
    fig.canvas.draw()
    grid_pos = ax_grid.get_position()
    grid_left  = grid_pos.x0
    grid_bottom = grid_pos.y0
    grid_w_real = grid_pos.width
    grid_h_real = grid_pos.height

    # Right panel
    ax_right = fig.add_axes([grid_left + grid_w_real + 0.015, grid_bottom, right_panel_w_norm - 0.02, grid_h_real])
    ax_right.axis('off')
    ax_right.set_xlim(0, 100)
    ax_right.set_ylim(0, 300)

    # Top Box
    box_w = 100
    box_h = 75
    if not args.nocurs:
        if state.get("Cursors X Enable", 0): box_h += 13
        if state.get("Cursors Y Enable", 0): box_h += 23
    if h_offset_str: box_h += 13
    top_y = 300 - box_h
    pad_x = 5
    ax_right.add_patch(patches.FancyBboxPatch((0, top_y), box_w, box_h, boxstyle="round,pad=0,rounding_size=5", fc="#1a1a1a", ec="#444444", lw=1.5, alpha=0.9, zorder=10))
    ax_right.text(pad_x, top_y + box_h - 10, "STATE", ha="left", va="center", color="#888888", fontsize=9, fontweight='bold', zorder=20)
    ax_right.text(95, top_y + box_h - 10, run_str, ha="right", va="center", color="white", fontsize=11, fontweight='bold', zorder=20)
    line_y = top_y + box_h - 18
    ax_right.plot([5, box_w-5], [line_y, line_y], color="#444444", lw=1, zorder=20)
    trig_y_base = line_y - 10
    ax_right.text(pad_x, trig_y_base, "Trigger", ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
    t1 = TextArea(trig_mode, textprops=dict(color="white", fontsize=11, fontweight='bold'))
    t2 = TextArea(" | ", textprops=dict(color="#666666", fontsize=12, fontweight='bold'))
    t3 = TextArea(trig_edge, textprops=dict(color="white", fontsize=11, fontweight='bold'))
    packer = HPacker(children=[t1, t2, t3], align="baseline", pad=0, sep=0)
    ab = AnnotationBbox(packer, (95, trig_y_base), xycoords='data', box_alignment=(1.0, 0.5), frameon=False, pad=0, zorder=20)
    ax_right.add_artist(ab)
    level_y_base = trig_y_base - 13
    ax_right.text(pad_x, level_y_base, "Level", ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
    ax_right.text(95, level_y_base, trig_lvl_str, ha="right", va="center", color="white", fontsize=11, fontweight='bold', zorder=20)
    delay_y_base = level_y_base - 13
    ax_right.text(pad_x, delay_y_base, "Delay", ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
    ax_right.text(95, delay_y_base, delay_str, ha="right", va="center", color="white", fontsize=11, fontweight='bold', zorder=20)
    rate_y_base = delay_y_base - 13
    if h_offset_str:
        ax_right.text(pad_x, rate_y_base, "H Offset", ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
        ax_right.text(95, rate_y_base, h_offset_str, ha="right", va="center", color="white", fontsize=11, fontweight='bold', zorder=20)
        rate_y_base -= 13
    sr_val = state.get("Sample Rate (Meas)", 0)
    if cfg['name']=="DSO2512G": sr_val = sr_val * 10
    sr_str = format_sample_rate(sr_val)
    ax_right.text(pad_x, rate_y_base, "Sample Rate", ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
    ax_right.text(95, rate_y_base, sr_str, ha="right", va="center", color="white", fontsize=11, fontweight='bold', zorder=20)
    if not args.nocurs:
        cursor_x_base = rate_y_base - 13
        cursor_y_base = cursor_x_base
        if state.get("Cursors X Enable", 0):
            cursor_y_base -= 11
            ax_right.text(pad_x, cursor_x_base, "Curs X", ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
            t1 = TextArea(t_str, textprops=dict(color="white", fontsize=10, fontweight='bold'))
            t2 = TextArea(" | ", textprops=dict(color="#666666", fontsize=11, fontweight='bold'))
            t3 = TextArea(f_str, textprops=dict(color="white", fontsize=10, fontweight='bold'))
            packer = HPacker(children=[t1, t2, t3], align="baseline", pad=0, sep=0)
            ab = AnnotationBbox(packer, (95, cursor_x_base), xycoords='data', box_alignment=(1.0, 0.5), frameon=False, pad=0, zorder=20)
            ax_right.add_artist(ab)
        if state.get("Cursors Y Enable", 0):
            if state["CH2 Enabled"]: y_str = "Curs Y-" + ch_prefix
            else: y_str = "Curs Y"
            ax_right.text(pad_x, cursor_y_base, y_str, ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
            t1 = TextArea(y2_str, textprops=dict(color="white", fontsize=10, fontweight='bold'))
            t2 = TextArea(" | ", textprops=dict(color="#666666", fontsize=11, fontweight='bold'))
            t3 = TextArea(y1_str, textprops=dict(color="white", fontsize=10, fontweight='bold'))
            packer = HPacker(children=[t1,t2,t3], align="baseline", pad=0, sep=0)
            ab = AnnotationBbox(packer, (95, cursor_y_base), xycoords='data', box_alignment=(1.0, 0.5), frameon=False, pad=0, zorder=20)
            ax_right.add_artist(ab)
            cursor_y_base -= 11
            ax_right.text(pad_x, cursor_y_base, "Curs dY", ha="left", va="center", color="#AAAAAA", fontsize=9, zorder=20)
            ax_right.text(95, cursor_y_base, dy_str, ha="right", va="center", color="white", fontsize=10, fontweight='bold', zorder=20)

    # Measurements
    col1_x = 2
    col2_x = 52
    top_y  = 300 - box_h - 8
    forced_bits = None
    if args.meas:
        meas_arg = args.meas
        meas_list = [m.strip().lower() for m in meas_arg.split(",")]
        if "all" in meas_list: forced_bits = list(MEASUREMENT_FLAGS.keys())
        else:
            forced_bits = []
            for part in meas_list:
                part = part.strip().lower()
                if part in SELECTED_MEASUREMENTS: forced_bits.append(SELECTED_MEASUREMENTS[part])
                else: print(f"Warning: unknown measurement '{part}'")
            if not forced_bits: forced_bits = None
    else: forced_bits = list(MEASUREMENT_FLAGS.keys())
    meas_c1_list = parse_active_measurements_list(buf, cfg['meas_ch1_offset'], cfg['meas_flag_offset_ch1'], state.get("CH1 Probe Mode", 0), forced_bits)
    if meas_c1_list: draw_measurement_column(ax_right, col1_x, top_y, ch_number=1, color=ch1_color, meas_list=meas_c1_list, enabled=1)
    meas_c2_list = parse_active_measurements_list(buf, cfg['meas_ch2_offset'], cfg['meas_flag_offset_ch2'], state.get("CH2 Probe Mode", 0), forced_bits)
    if meas_c2_list: draw_measurement_column(ax_right, col2_x, top_y, ch_number=2, color=ch2_color, meas_list=meas_c2_list, enabled=state["CH2 Enabled"])

    # Waveforms
    if state["Active Channel"] == 1: c2_z = 6
    else: c2_z = 4
    if layers is not None:
        if layers.get(1) is not None:
            draw_wave(ax_grid, None, None, None, ch1_color, 5, layers[1], "CH1")
        if state["CH2 Enabled"] and layers.get(2) is not None:
            draw_wave(ax_grid, None, None, None, ch2_color, c2_z, layers[2], "CH2")
    else:
        col_lo = max(0, min(state.get("Display Start Column", 0), 299))
        col_hi = max(col_lo, min(state.get("Display End Column", 299), 299))
        cols = slice(col_lo, col_hi + 1)
        x_axis = np.arange(300)[cols]
        raw_ch1 = np.frombuffer(buf[0:600], dtype=np.uint8)
        draw_wave(ax_grid, x_axis, 255 - raw_ch1[0:300][cols], 255 - raw_ch1[300:600][cols],
                  ch1_color, 5, None, "CH1")
        if state["CH2 Enabled"] and len(buf) >= 1200:
            raw_ch2 = np.frombuffer(buf[600:1200], dtype=np.uint8)
            draw_wave(ax_grid, x_axis, 255 - raw_ch2[0:300][cols], 255 - raw_ch2[300:600][cols],
                      ch2_color, c2_z, None, "CH2")

    # Trigger arrow
    trig_src = state["Trigger Source"]
    trig_color = ch1_color if trig_src == 0 else ch2_color
    if trig_src == 0:
        trig_val = state.get("CH1 Trigger Level (uV)", 0)
        scale = state.get("CH1 Volt Scale (uV)", 100000)
    else:
        trig_val = state.get("CH2 Trigger Level (uV)", 0)
        scale = state.get("CH2 Volt Scale (uV)", 100000)
    if scale == 0: scale = 1
    trig_y = 128 + int((trig_val / scale) * 25.0)
    if args.trigline: ax_grid.axhline(trig_y, color=trig_color, linestyle='--', linewidth=0.8, label="Trig", zorder=7)
    if trig_y > plot_top: trig_arrow_y = plot_top
    elif trig_y < plot_bot: trig_arrow_y = plot_bot
    else: trig_arrow_y = trig_y
    ax_grid.plot(303, trig_arrow_y, marker=8, color=trig_color, markersize=8, clip_on=False, zorder=10)

    # Timebase arrow
    tb_val_ns = state.get("Timebase Value (ns/div)", 1)
    tb_marker = 11
    tb_y = plot_top + 3
    if window is not None:
        start, count, trigger = window
        tb_arrow_x = int(round((trigger - start) * 300.0 / count)) if trigger is not None else 150
    else:
        tb_offset_ps = state.get("Horiz Trigger Delay (ps)", 0) - \
            state.get("View Scroll Offset (ps)", 0)
        if tb_val_ns > 0:
            tb_offset_in_divs = (tb_offset_ps / 1000.0) / tb_val_ns
            tb_arrow_x = 150 + int(tb_offset_in_divs * 25.0)
        else: tb_arrow_x = 150
    if tb_arrow_x < 0:
        tb_arrow_x = 0
        tb_marker = 8
        tb_y -= 1
    elif tb_arrow_x > 300:
        tb_arrow_x = 300
        tb_marker = 9
        tb_y -= 1
    ax_grid.plot(tb_arrow_x, tb_y, marker=tb_marker, color='#00fbf7', markersize=8, clip_on=False, zorder=10)

    # Zero voltage arrow
    c1_zero_y = 128 + state.get("CH1 Zero Volt (pixels)")
    if c1_zero_y < plot_bot: c1_zero_y = plot_bot
    if c1_zero_y > plot_top: c1_zero_y = plot_top
    ax_grid.plot(-3, c1_zero_y, marker=9, color=ch1_color, markersize=8, clip_on=False, zorder=10)

    if state["CH2 Enabled"]:
        c2_zero_y = 128 + state.get("CH2 Zero Volt (pixels)")
        if c2_zero_y < plot_bot: c2_zero_y = plot_bot
        if c2_zero_y > plot_top: c2_zero_y = plot_top
        ax_grid.plot(-3, c2_zero_y, marker=9, color=ch2_color, markersize=8, clip_on=False, zorder=c2_z + 5)

    # Cursors
    if not args.nocurs:
        if state.get("Cursors X Enable", 0):
            cx1 = 150 + state["Cursor X1 Pos"]
            cx2 = 150 + state["Cursor X2 Pos"]
            ax_grid.axvline(cx1, color='green', linestyle=(0, (5, 10)))
            ax_grid.axvline(cx2, color='green', linestyle=(0, (5, 10)))

        if state.get("Cursors Y Enable", 0):
            cy1 = 128 + state["Cursor Y1 Pos"]
            cy2 = 128 + state["Cursor Y2 Pos"]
            ax_grid.axhline(cy1, color='green', linestyle=(0, (5, 10)))
            ax_grid.axhline(cy2, color='green', linestyle=(0, (5, 10)))

    ax_grid.axis('off')

    # Bottom panel
    ax_bottom = fig.add_axes([0.02, 0.015, grid_w_real, bottom_panel_h_norm])
    ax_bottom.set_xlim(0, 100)
    ax_bottom.set_ylim(0, 100)
    ax_bottom.axis("off")
    box_h = 60
    box_w = 2.5
    y_base = 15

    # CH1
    x_ch1 = 2
    rect_ch1 = patches.FancyBboxPatch((x_ch1, y_base), box_w, box_h, boxstyle="round,pad=1", fc=ch1_color, ec="none")
    ax_bottom.add_patch(rect_ch1)
    ax_bottom.text(x_ch1 + box_w/2, y_base + box_h/2 - 4, "1", ha="center", va="center", color="#1C1C1C", fontsize=18, fontweight="bold")
    parts = [c1_vdiv, c1_cpl, c1_prb]
    x_pos = x_ch1 + box_w + 3
    if c1_bw_limit == 1: ax_bottom.text(x_pos + 5.5, y_base + box_h/2 - 35, "20M BW Limit", ha="center", va="center", color="#888888", fontsize=8, fontweight="bold")
    y = y_base + box_h/2 - 2
    for i, part in enumerate(parts):
        ax_bottom.text(x_pos, y, part, color="white", fontsize=14, fontweight="bold", va="center")
        renderer = ax_bottom.figure.canvas.get_renderer()
        t = ax_bottom.text(x_pos, y, part, fontsize=14)
        bb = t.get_window_extent(renderer=renderer).transformed(ax_bottom.transData.inverted())
        width = bb.width
        t.remove()
        x_pos += width + 2
        if i < len(parts) - 1:
            ax_bottom.text(x_pos, y + 3, "|", color="#808080", fontsize=12, va="center", fontweight="bold")
            x_pos += 2.4

    # Timebase
    x_tb = 42
    rect_tb = patches.FancyBboxPatch((x_tb, y_base), 16, box_h, boxstyle="round,pad=1", fc="#3498db", ec="none")
    ax_bottom.add_patch(rect_tb)
    ax_bottom.text(x_tb + 16/2, y_base + box_h/2 - 3, tb_str, ha="center", va="center", color="white", fontsize=16, fontweight="bold")

    # CH2
    if state["CH2 Enabled"]:
        box_color   = ch2_color
        text_color  = "white"
        digit_color = "#1C1C1C"
        sep_color   = "#808080"
    else:
        box_color   = "#555555"
        text_color  = "#AAAAAA"
        digit_color = "#333333"
        sep_color   = "#666666"
    x_ch2 = 95.5
    rect_ch2 = patches.FancyBboxPatch((x_ch2, y_base), box_w, box_h, boxstyle="round,pad=1", fc=box_color, ec="none")
    ax_bottom.add_patch(rect_ch2)
    ax_bottom.text(x_ch2 + box_w/2, y_base + box_h/2 - 4, "2", ha="center", va="center", color=digit_color, fontsize=18, fontweight="bold")
    if c2_bw_limit == 1: ax_bottom.text(x_ch2 - 9, y_base + box_h/2 - 35, "20M BW Limit", ha="center", va="center", color="#888888", fontsize=8, fontweight="bold")
    parts = [c2_vdiv, c2_cpl, c2_prb]
    sep = "|"
    renderer = ax_bottom.figure.canvas.get_renderer()
    widths = []
    for part in parts:
        t = ax_bottom.text(0, 0, part, fontsize=14)
        bb = t.get_window_extent(renderer=renderer).transformed(ax_bottom.transData.inverted())
        widths.append(bb.width)
        t.remove()
    t = ax_bottom.text(0, 0, sep, fontsize=12)
    bb = t.get_window_extent(renderer=renderer).transformed(ax_bottom.transData.inverted())
    sep_w = bb.width
    t.remove()
    total_w = sum(widths) + sep_w * (len(parts) - 1)
    x_start = x_ch2 - total_w - 11
    y = y_base + box_h/2 - 2
    x = x_start
    for i, part in enumerate(parts):
        ax_bottom.text(x, y, part, color=text_color, fontsize=14, fontweight="bold", va="center")
        x += widths[i] + 2
        if i < len(parts) - 1:
            ax_bottom.text(x, y + 3, sep, color=sep_color, fontsize=12, fontweight="bold", va="center")
            x += 2.4

    fig = plt.gcf()
    size_inches = fig.get_size_inches()
    calc_dpi = args.width / size_inches[0]
    plt.savefig(f"{filename}.png", dpi=calc_dpi, facecolor='black')
    plt.close(fig)
    print(f"Saved image:      {filename}.png")


DEFAULT_OUTPUT = "Zeeweii_Screenshot"
LCD_SCREENSHOT_PREFIX = "Zeeweii_LCD_Screenshot"
FPGA_CAPTURE_PREFIX = "Zeeweii_Waveform"
PUSH_BUFFER_PREFIX = "Zeeweii_Buffer"


def output_prefix(args, default):
    return default if args.output == DEFAULT_OUTPUT else args.output


def generate_waveform(image_path, scale=False, output_filename="waveform_pattern_mod.bin"):
    try:
        img = Image.open(image_path).convert('L')
    except Exception as e:
        print(f"Error opening image: {e}")
        return False
    target_size = (256, 256)
    if img.size != target_size:
        print(f"Resized: {target_size}")
        if hasattr(Image, 'Resampling'): resample_method = Image.Resampling.LANCZOS
        else: resample_method = Image.LANCZOS
        img = img.resize(target_size, resample_method)
    width, height = img.size
    pixels = np.array(img)
    waveform = []
    for x in range(width):
        col = pixels[:, x]
        bright_indices = np.where(col > 50)[0]
        if len(bright_indices) > 0: avg_y = np.mean(bright_indices)
        else: avg_y = height / 2.0
        val = 255.0 - avg_y
        val = max(0, min(255, val))
        waveform.append(val)
    if scale:
        min_val = min(waveform)
        max_val = max(waveform)
        range_val = max_val - min_val
        if range_val > 0:
            factor = 255.0 / range_val
            print(f"Scaling dynamic range: {factor:.2f}x")
            waveform = [(v - min_val) * factor for v in waveform]
    int_data = [int(round(v)) for v in waveform]
    best_idx = 0
    min_diff = 256
    for i in range(len(int_data)):
        diff = abs(int_data[i] - 128)
        prev = int_data[i-1] if i > 0 else int_data[-1]
        slope = int_data[i] - prev
        if diff < min_diff:
            min_diff = diff
            best_idx = i
        elif diff == min_diff and slope > 0: best_idx = i
    if min_diff == 0: print(f"Aligned waveform start x: {best_idx}")
    else: print(f"Aligned waveform start x: {best_idx} (resampled {int_data[best_idx]:#x} to 0x80)")
    rotated = int_data[best_idx:] + int_data[:best_idx]
    payload = rotated[1:]
    if output_filename == DEFAULT_OUTPUT:
        final_output = "waveform_pattern_mod.bin"
    else:
        final_output = output_filename
        if not final_output.lower().endswith(".bin"): final_output += ".bin"
    try:
        with open(final_output, "wb") as f: f.write(bytearray(payload))
        print(f"Saved: {final_output}")
    except IOError as e:
        print(f"Error writing file: {e}")
        return False
    return True

LCD_SCREENSHOT_MAGIC = b"ZWSHOT\0\0"
LCD_SCREENSHOT_VERSION = 7
LCD_SCREENSHOT_HEADER_LEN = 64
LCD_SCREENSHOT_MODE_RAW = 0
LCD_SCREENSHOT_MODE_RLE = 1

FPGA_CAPTURE_MAGIC = b"ZWDUMP\0\0"
FPGA_CAPTURE_VERSION = 5
FPGA_CAPTURE_VERSIONS = (3, 4, 5)
FPGA_CAPTURE_HEADER_LEN = 128
FPGA_CAPTURE_FLAG_CH2 = 0x1
FPGA_CAPTURE_FLAG_BUSY = 0x2
FPGA_CAPTURE_FLAG_FULL = 0x4
FPGA_CAPTURE_SETTINGS_LEN = 340
FPGA_CAPTURE_MEAS_LEN = 100
FPGA_CAPTURE_STATE_LEN = FPGA_CAPTURE_SETTINGS_LEN + 2 * FPGA_CAPTURE_MEAS_LEN
FPGA_CAPTURE_ENC_RAW = 0
FPGA_CAPTURE_ENC_BLOCKS = 1
FPGA_CAPTURE_MODE_RAW = 0
FPGA_CAPTURE_MODE_DELTA = 1
FPGA_CAPTURE_CODEC_ESCAPE = 0xF
FPGA_CAPTURE_BLOCK_SAMPLES = 1000

FRAME_SYNC = b"\xA5\x5A"
FRAME_VERSION = 1
FRAME_HELLO = 0x01
FRAME_SET_BAUD = 0x02
FRAME_LCD_SCREENSHOT = 0x10
FRAME_FPGA_CAPTURE = 0x11
FRAME_DATA_ACK = 0x40
FRAME_ABORT = 0x41
FRAME_INFO = 0x81
FRAME_BAUD_STATUS = 0x82
FRAME_LCD_SHOT_BEGIN = 0x90
FRAME_FPGA_CAPTURE_BEGIN = 0x91
FRAME_DATA = 0xC0
FRAME_ERROR = 0xFF
FRAME_MAX_CONTROL = 64
FRAME_MAX_DATA = 1024
FRAME_CONTAINER_LCD_SCREENSHOT = 1
FRAME_CONTAINER_FPGA_CAPTURE = 2
FRAME_PERSIST = 0x17
FRAME_PERSIST_BEGIN = 0x97
FRAME_CONTAINER_FLASH = 3
CAP_FLASH = 0x80

PERSIST_MAGIC = b"ZWFLSH\0\0"
PERSIST_VERSION = 1
PERSIST_HEADER_LEN = 32
PERSIST_BASE = 0x08096000
PERSIST_LIMIT = 0x080FF000
PERSIST_FLASH_BASE = 0x08000000
PERSIST_FLASH_SIZE = 0x00100000
BACKUP_PREFIX = "Zeeweii_Backup"
BACKUP_DEFAULT = object()
PERSIST_RECORDS = (
    (0x08096000, 0x001000, "factory info / UUID"),
    (0x08097000, 0x000400, "settings record"),
    (0x08098000, 0x000400, "scope calibration"),
    (0x08098400, 0x000400, "DMM calibration"),
    (0x080C0000, 0x01F800, "screenshots (63 x 0x800)"),
    (0x080BF000, 0x001000, "screenshot index"),
)
FRAME_OK = 0
FRAME_BAD_PARAM = 1
FRAME_BAD_RATE = 2
FRAME_BUSY = 3
FRAME_UNKNOWN_TYPE = 4
FRAME_BAD_LENGTH = 5
FRAME_BAD_VERSION = 6
FRAME_ABORTED = 7
FRAME_CRC_ERROR = 8
FRAME_TIMEOUT = 9
FRAME_INTERNAL = 10
FRAME_OUT_OF_ORDER = 11
FRAME_STATUS_NAMES = {
    0: "OK", 1: "BAD_PARAM", 2: "BAD_RATE", 3: "BUSY", 4: "UNKNOWN_TYPE",
    5: "BAD_LENGTH", 6: "BAD_VERSION", 7: "ABORTED", 8: "CRC_ERROR",
    9: "TIMEOUT", 10: "INTERNAL", 11: "OUT_OF_ORDER", 12: "DROPPED",
}
BAUD_RATES = (2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600, 1000000, 1500000, 2000000)
SCOPE_BOOT_BAUD = 115200
SCOPE_BAUD_WINDOW = 1.0
DEFAULT_BAUD = 1000000
PUSH_IDLE = 0.2
PUSH_STATE_MIN = 2040
PUSH_STATE_MAX = 2056
PUSH_BUF_LIMIT = 1 << 20
EXIT_OK = 0
EXIT_FAIL = 1


def baud_label(rate):
    return ("%gM" % (rate / 1_000_000)) if rate >= 1_000_000 else str(rate)


class LcdScreenshotError(Exception):
    pass


class FpgaCaptureError(Exception):
    pass


class FrameTimeout(Exception):
    pass


class LinkError(Exception):
    pass


class RemoteError(LinkError):
    """Link error"""


class TransferStall(LinkError):
    def __init__(self, message, xid=None):
        super().__init__(message)
        self.xid = xid


class ScopeError(Exception):
    def __init__(self, code, request_type=0, detail=0):
        self.code = code
        self.request_type = request_type
        self.detail = detail
        super().__init__("scope reported %s (type 0x%02X, detail %d)" % (FRAME_STATUS_NAMES.get(code, code), request_type, detail))


def frame_crc16(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte << 8
        for _ in range(8):
            crc = ((crc << 1) ^ 0x1021) & 0xFFFF if crc & 0x8000 else (crc << 1) & 0xFFFF
    return crc


def frame_pack(ftype, seq, payload=b""):
    if len(payload) > FRAME_MAX_DATA:
        raise ValueError("payload %d exceeds %d bytes" % (len(payload), FRAME_MAX_DATA))
    body = struct.pack("<BBHH", FRAME_VERSION, ftype, seq & 0xFFFF, len(payload)) + bytes(payload)
    return FRAME_SYNC + body + struct.pack("<H", frame_crc16(body))


def frame_send(ser, ftype, seq, payload=b""):
    ser.write(frame_pack(ftype, seq, payload))
    ser.flush()


class Frame:
    __slots__ = ("version", "type", "seq", "payload", "crc_ok")

    def __init__(self, version, ftype, seq, payload, crc_ok):
        self.version = version
        self.type = ftype
        self.seq = seq
        self.payload = payload
        self.crc_ok = crc_ok


class FrameParser:
    def __init__(self):
        self.buf = bytearray()
        self.queue = []

    def reset(self):
        del self.buf[:]
        del self.queue[:]

    def pending(self):
        return bool(self.buf) or bool(self.queue)

    def pop(self):
        return self.queue.pop(0) if self.queue else None

    def feed(self, data):
        self.buf.extend(data)
        while True:
            at = self.buf.find(FRAME_SYNC)
            if at < 0:
                if self.buf[-1:] == b"\xA5":
                    del self.buf[:-1]
                else:
                    del self.buf[:]
                break
            if at:
                del self.buf[:at]
            if len(self.buf) < 8:
                break
            version = self.buf[2]
            ftype = self.buf[3]
            seq, plen = struct.unpack_from("<HH", self.buf, 4)
            if plen > FRAME_MAX_DATA:
                del self.buf[:1]
                continue
            total = 8 + plen + 2
            if len(self.buf) < total:
                break
            payload = bytes(self.buf[8:8 + plen])
            want = struct.unpack_from("<H", self.buf, 8 + plen)[0]
            got = frame_crc16(bytes(self.buf[2:8]) + payload)
            if got == want:
                del self.buf[:total]
                self.queue.append(Frame(version, ftype, seq, payload, True))
                continue
            self.queue.append(Frame(version, ftype, seq, payload, False))
            nxt = self.buf.find(FRAME_SYNC, 2)
            del self.buf[:2 if nxt < 0 else nxt]


def wait_frame(ser, parser, timeout, allow_corrupt=False):
    start = time.monotonic()
    last_rx = start
    while True:
        while parser.queue:
            f = parser.pop()
            if not f.crc_ok:
                if allow_corrupt:
                    return f
                continue
            if f.version != FRAME_VERSION:
                frame_send(ser, FRAME_ERROR, f.seq, struct.pack("<BBH", FRAME_BAD_VERSION, f.type, f.seq))
                continue
            return f
        waiting = ser.in_waiting
        if waiting:
            chunk = ser.read(waiting)
            if chunk:
                last_rx = time.monotonic()
                parser.feed(chunk)
        else:
            now = time.monotonic()
            if parser.buf and now - last_rx >= 0.1:
                parser.reset()
            if now - start >= timeout:
                raise FrameTimeout("no frame within %.2f s" % timeout)
            time.sleep(0.002)


def wire_timeout(baud, nbytes=40):
    return max(0.5, nbytes * 10.0 / max(baud, 1) + 0.1)


def format_transfer_stats(stats):
    return ("Transfer: %d DATA frame(s) | CRC failures %d, duplicate DATA %d, out-of-order %d, request tries %d, BUSY retries %d"
            % (stats["frames"], stats["crc_retries"], stats["duplicates"], stats["out_of_order"], stats["request_tries"], stats["busy_retries"]))


def ack_timeout(baud, frame_size=FRAME_MAX_DATA):
    t_frame = (frame_size + 12) * 10.0 / max(baud, 1)
    return max(0.5, 2.0 * t_frame + 0.1)


def scope_error(frame):
    if len(frame.payload) < 4:
        return ScopeError(FRAME_INTERNAL, frame.type, frame.seq)
    code, rtype, detail = struct.unpack_from("<BBH", frame.payload, 0)
    return ScopeError(code, rtype, detail)


class ScopeLink:
    def __init__(self, ser):
        self.ser = ser
        self.parser = FrameParser()
        self.seq = 0
        self.wave_xid = None
        self.baud = getattr(ser, "baudrate", None) or SCOPE_BOOT_BAUD

    def next_seq(self):
        self.seq = self.seq % 0xFFFF + 1
        return self.seq

    def send(self, ftype, seq, payload=b""):
        frame_send(self.ser, ftype, seq, payload)

    def switch_rate(self, rate):
        self.ser.baudrate = rate
        self.parser.reset()
        self.ser.reset_input_buffer()
        self.baud = rate

    def wait_reply(self, seq, timeout):
        end = time.monotonic() + timeout
        while True:
            remaining = end - time.monotonic()
            if remaining <= 0:
                raise FrameTimeout("no reply within %.2f s" % timeout)
            frame = wait_frame(self.ser, self.parser, remaining)
            if frame.type == FRAME_DATA:
                self.send(FRAME_ABORT, self.next_seq(), struct.pack("<H", 0))
                continue
            if frame.type == FRAME_ERROR:
                if frame.seq != seq:
                    continue
                raise scope_error(frame)
            if frame.seq == seq:
                return frame

    def hello(self, attempts=3, timeout=None):
        timeout = timeout if timeout is not None else wire_timeout(self.baud)
        seq = self.next_seq()
        for attempt in range(attempts):
            self.send(FRAME_HELLO, seq)
            try:
                frame = self.wait_reply(seq, timeout)
            except FrameTimeout:
                if attempt == attempts - 1:
                    raise
                continue
            if frame.type != FRAME_INFO or len(frame.payload) < 9:
                raise LinkError("unexpected reply 0x%02X to HELLO" % frame.type)
            version, max_control, max_data, caps = struct.unpack_from("<BHHI", frame.payload, 0)
            return dict(version=version, max_control=max_control,
                        max_data=max_data, caps=caps)
        raise FrameTimeout("no INFO after %d attempts" % attempts)

    def set_baud(self, rate):
        seq = self.next_seq()
        self.send(FRAME_SET_BAUD, seq, struct.pack("<I", rate))
        frame = self.wait_reply(seq, wire_timeout(self.baud))
        if frame.type != FRAME_BAUD_STATUS or not frame.payload:
            raise LinkError("unexpected reply 0x%02X to SET_BAUD" % frame.type)
        return frame.payload[0]

    def abort(self, xid):
        for attempt in range(2):
            seq = self.next_seq()
            self.send(FRAME_ABORT, seq, struct.pack("<H", 0 if attempt else xid))
            end = time.monotonic() + 0.5
            while time.monotonic() < end:
                try:
                    frame = wait_frame(self.ser, self.parser, max(0.02, end - time.monotonic()))
                except FrameTimeout:
                    break
                if frame.type == FRAME_ERROR and len(frame.payload) >= 4:
                    if struct.unpack_from("<B", frame.payload, 0)[0] == FRAME_ABORTED:
                        return True
        return False



    def persist(self, addr=PERSIST_BASE, length=None, timeout=5.0, caps=None,
                stats=None, debug=False, retries=2):
        if caps is not None and not (caps & CAP_FLASH):
            raise RemoteError("persistent flash backup unsupported by firmware (caps: 0x%02X)" % caps)
        if length is None:
            length = PERSIST_LIMIT - addr
        if addr < PERSIST_BASE or addr >= PERSIST_LIMIT:
            raise ValueError("0x%08X is outside the persistent window 0x%08X-0x%08X" % (addr, PERSIST_BASE, PERSIST_LIMIT - 1))
        if not 1 <= length <= PERSIST_LIMIT - addr:
            raise ValueError("%d bytes from 0x%08X runs past the window end 0x%08X" % (length, addr, PERSIST_LIMIT - 1))
        return self.fetch_retry(FRAME_PERSIST, FRAME_PERSIST_BEGIN,
                                FRAME_CONTAINER_FLASH, timeout, stats=stats,
                                retries=retries, debug=debug,
                                payload=struct.pack("<II", addr, length))

    def request(self, ftype, timeout, payload=b""):
        seq = self.next_seq()
        for attempt in range(3):
            self.send(ftype, seq, payload)
            try:
                return seq, self.wait_reply(seq, timeout), attempt + 1
            except ScopeError as e:
                e.tries = attempt + 1
                raise
            except FrameTimeout:
                if attempt == 2:
                    raise LinkError("no reply to request 0x%02X after 3 attempts" % ftype)
        raise LinkError("request failed")

    def fetch(self, req_type, begin_type, container, timeout, stats=None,
              payload=b""):
        if stats is None:
            stats = {}
        stats.update(frames=0, request_tries=0, busy_retries=0,
                     crc_retries=0, duplicates=0, out_of_order=0)
        while True:
            try:
                seq, begin, tries = self.request(req_type, timeout, payload)
                stats["request_tries"] += tries
                break
            except ScopeError as e:
                stats["request_tries"] += getattr(e, "tries", 1)
                if e.code == FRAME_BUSY and stats["busy_retries"] < 2:
                    stats["busy_retries"] += 1
                    self.abort(0)
                    time.sleep(0.1)
                    continue
                raise
        if begin.type != begin_type or len(begin.payload) < 10:
            raise LinkError("unexpected reply 0x%02X to request 0x%02X" % (begin.type, req_type))
        status, xid, kind, frame_size, total = struct.unpack_from("<BHBHI", begin.payload, 0)
        if status != FRAME_OK:
            raise ScopeError(status, req_type, seq)
        if xid != seq:
            raise LinkError("BEGIN xid %d does not match request seq %d" % (xid, seq))
        if kind != container:
            raise LinkError("BEGIN container %d, expected %d" % (kind, container))
        if not 0 < frame_size <= FRAME_MAX_DATA:
            raise LinkError("bad BEGIN frame size %d" % frame_size)

        self.send(FRAME_DATA_ACK, xid, struct.pack("<HHB", xid, 0, FRAME_OK))

        data = bytearray()
        expected = 0
        t_ack = ack_timeout(self.baud, frame_size)
        while len(data) < total:
            try:
                frame = wait_frame(self.ser, self.parser, t_ack, allow_corrupt=True)
            except FrameTimeout:
                raise TransferStall("transfer stalled after %d of %d bytes" % (len(data), total), xid)
            if frame.type == FRAME_ERROR:
                raise scope_error(frame)
            if not frame.crc_ok:
                stats["crc_retries"] += 1
                self.send(FRAME_DATA_ACK, expected, struct.pack("<HHB", xid, expected, FRAME_CRC_ERROR))
                continue
            if frame.type in (FRAME_LCD_SHOT_BEGIN, FRAME_FPGA_CAPTURE_BEGIN) and frame.seq == xid:
                self.send(FRAME_DATA_ACK, xid, struct.pack("<HHB", xid, 0, FRAME_OK))
                continue
            if frame.type != FRAME_DATA:
                continue
            if frame.seq == expected:
                if not frame.payload or len(frame.payload) > frame_size or len(data) + len(frame.payload) > total:
                    raise LinkError("DATA %d has %d bytes, %d already of %d" % (expected, len(frame.payload), len(data), total))
                data.extend(frame.payload)
                expected += 1
                self.send(FRAME_DATA_ACK, frame.seq, struct.pack("<HHB", xid, expected, FRAME_OK))
            elif frame.seq < expected:
                stats["duplicates"] += 1
                self.send(FRAME_DATA_ACK, frame.seq, struct.pack("<HHB", xid, expected, FRAME_OK))
            else:
                stats["out_of_order"] += 1
                self.send(FRAME_DATA_ACK, expected, struct.pack("<HHB", xid, expected, FRAME_OUT_OF_ORDER))

        stats["frames"] = expected

        end = time.monotonic() + 3.0 * t_ack
        while time.monotonic() < end:
            try:
                frame = wait_frame(self.ser, self.parser, min(0.05, max(0.01, end - time.monotonic())))
            except FrameTimeout:
                continue
            if frame.type == FRAME_DATA and frame.seq == expected - 1:
                self.send(FRAME_DATA_ACK, frame.seq, struct.pack("<HHB", xid, expected, FRAME_OK))
        return bytes(data), stats

    def fetch_retry(self, req_type, begin_type, container, timeout, stats=None, retries=2, debug=False, payload=b""):
        for attempt in range(retries + 1):
            try:
                return self.fetch(req_type, begin_type, container, timeout, stats, payload)
            except TransferStall as e:
                if attempt == retries:
                    raise
                if debug:
                    print("Transfer stalled (%s); retry %d of %d" % (e, attempt + 1, retries))
                self.abort(e.xid or 0)
                self.parser.reset()
                self.ser.reset_input_buffer()
                time.sleep(0.2)


def probe_link(link, timeout=0.25):
    try:
        return link.hello(attempts=1, timeout=timeout)
    except (FrameTimeout, LinkError, ScopeError):
        return None


def negotiate_baud(link, target):
    if target not in BAUD_RATES:
        print(f"{baud_label(target)} baud not supported, kept {baud_label(link.baud)}")
        return link.baud
    if target == link.baud:
        return link.baud

    old = link.baud
    requested_at = time.monotonic()
    try:
        status = link.set_baud(target)
    except (FrameTimeout, LinkError) as e:
        time.sleep(max(0.0, requested_at + SCOPE_BAUD_WINDOW + 0.15 - time.monotonic()))
        link.parser.reset()
        drain_serial(link.ser, idle=0.05, limit=0.2)
        confirmed = probe_link(link, 0.3) is not None
        print("Baud rate: no answer to the retune request (%s); %s at %s" % (e, "scope confirmed back" if confirmed else "staying", baud_label(old)))
        return old
    if status == FRAME_BAD_RATE:
        print(f"Baud rate: scope refused {baud_label(target)}, staying at {baud_label(old)}")
        return old
    if status != FRAME_OK:
        print(f"Baud rate: unexpected status {status}, staying at {baud_label(old)}")
        return old

    try:
        link.switch_rate(target)
    except (ValueError, OSError) as e:
        print(f"Baud rate: adapter refused {baud_label(target)} ({e}), staying at {baud_label(old)}")
        time.sleep(1.05)
        link.switch_rate(old)
        probe_link(link)
        return old
    retuned_at = time.monotonic()
    for delay in (0.1, 0.3, 0.5):
        time.sleep(max(0.0, retuned_at + delay - time.monotonic()))
        if probe_link(link, 0.2) is not None:
            return target

    link.switch_rate(old)
    time.sleep(max(0.0, retuned_at + 1.05 - time.monotonic()))
    if probe_link(link, 0.3) is not None:
        print(f"Baud rate: scope did not confirm {baud_label(target)}, staying at {baud_label(old)}")
        return old

    for attempt in range(8):
        rate = target if attempt % 2 == 0 else old
        link.switch_rate(rate)
        time.sleep(0.25)
        if probe_link(link, 0.25) is not None:
            print(f"Baud rate: {baud_label(rate)} (recovered)")
            return rate
    raise LinkError("link lost after retuning; power-cycle the scope or retry")


def open_link(ser, target):
    link = ScopeLink(ser)
    rates = [SCOPE_BOOT_BAUD]
    if target != SCOPE_BOOT_BAUD and target in BAUD_RATES:
        rates.append(target)
    for rate in rates:
        link.switch_rate(rate)
        drain_serial(ser, idle=0.05, limit=0.3)
        info = probe_link(link, max(0.5, wire_timeout(rate)))
        if info is None:
            continue
        if rate != SCOPE_BOOT_BAUD:
            print(f"Baud rate: {baud_label(rate)} (already set)")
        if target != rate:
            rate = negotiate_baud(link, target)
        return link, rate, info
    raise LinkError("no HELLO reply at %s baud; power-cycle the scope" % " or ".join(baud_label(r) for r in rates))


def drain_serial(ser, idle=0.2, limit=1.0):
    end = time.monotonic() + limit
    while time.monotonic() < end:
        if ser.in_waiting:
            ser.read(ser.in_waiting)
        else:
            time.sleep(idle)
            if not ser.in_waiting:
                return


def lcd_screenshot_rle_decode(encoded, expect):
    if len(encoded) & 1:
        raise LcdScreenshotError("RLE payload has an odd length (%d)" % len(encoded))
    out = bytearray()
    for i in range(0, len(encoded), 2):
        count = encoded[i]
        if count == 0:
            raise LcdScreenshotError("RLE run at byte %d has zero count" % i)
        if len(out) + count > expect:
            raise LcdScreenshotError("RLE payload decodes past %d bytes" % expect)
        out += bytes((encoded[i + 1],)) * count
    if len(out) != expect:
        raise LcdScreenshotError("RLE payload decodes to %d bytes, want %d" % (len(out), expect))
    return bytes(out)


def lcd_parse_screenshot(data):
    if len(data) < LCD_SCREENSHOT_HEADER_LEN:
        raise LcdScreenshotError("screenshot is %d bytes, shorter than the header" % len(data))
    (magic, version, width, height, fb_len, pal_len, payload_len, fb_crc,
     pal_crc, block_size, total_blocks) = struct.unpack_from("<8s10I", data, 0)
    mode, enc_len = struct.unpack_from("<II", data, 48)
    if magic != LCD_SCREENSHOT_MAGIC:
        raise LcdScreenshotError("bad container magic %r" % magic)
    if version != LCD_SCREENSHOT_VERSION:
        raise LcdScreenshotError("unsupported container version %d (want %d)" % (version, LCD_SCREENSHOT_VERSION))
    if block_size not in (128, 1024) or total_blocks == 0:
        raise LcdScreenshotError("bad block geometry %d x %d" % (block_size, total_blocks))
    if width == 0 or height == 0 or fb_len != width * height:
        raise LcdScreenshotError("bad geometry %dx%d fb=%d" % (width, height, fb_len))
    if pal_len == 0 or pal_len > 4096 or (pal_len & 1):
        raise LcdScreenshotError("bad palette length %d" % pal_len)
    if payload_len != pal_len + fb_len:
        raise LcdScreenshotError("payload length %d != pal %d + fb %d" % (payload_len, pal_len, fb_len))
    if mode == LCD_SCREENSHOT_MODE_RAW:
        if enc_len != payload_len:
            raise LcdScreenshotError("raw container says %d payload bytes, want %d" % (enc_len, payload_len))
    elif mode == LCD_SCREENSHOT_MODE_RLE:
        if not 0 < enc_len <= payload_len:
            raise LcdScreenshotError("bad RLE encoded length %d" % enc_len)
    else:
        raise LcdScreenshotError("unsupported payload mode %d" % mode)
    content_len = LCD_SCREENSHOT_HEADER_LEN + enc_len
    if len(data) not in (content_len, total_blocks * block_size):
        raise LcdScreenshotError("screenshot is %d bytes, container is %d (header %d + payload %d)" % (len(data), content_len, LCD_SCREENSHOT_HEADER_LEN, enc_len))
    payload = data[LCD_SCREENSHOT_HEADER_LEN:LCD_SCREENSHOT_HEADER_LEN + enc_len]
    if mode == LCD_SCREENSHOT_MODE_RLE:
        payload = lcd_screenshot_rle_decode(payload, payload_len)
    pal = payload[:pal_len]
    fb = payload[pal_len:]
    if (zlib.crc32(pal) & 0xFFFFFFFF) != pal_crc:
        raise LcdScreenshotError("palette CRC32 mismatch")
    if (zlib.crc32(fb) & 0xFFFFFFFF) != fb_crc:
        raise LcdScreenshotError("framebuffer CRC32 mismatch")
    info = dict(width=width, height=height, fb_len=fb_len, pal_len=pal_len,
                block_size=block_size, total_blocks=total_blocks,
                mode=mode, enc_len=enc_len)
    return info, fb, pal


def lcd_save_screenshot_png(fb, pal, width, height, path):
    lut = bytearray()
    for i in range(256):
        value = pal[i * 2] | (pal[i * 2 + 1] << 8)
        r5, g6, b5 = (value >> 11) & 0x1F, (value >> 5) & 0x3F, value & 0x1F
        lut += bytes(((r5 * 255 + 15) // 31, (g6 * 255 + 31) // 63, (b5 * 255 + 15) // 31))
    rgb = bytearray(3 * len(fb))
    for i, index in enumerate(fb):
        rgb[3 * i:3 * i + 3] = lut[3 * index:3 * index + 3]
    Image.frombytes("RGB", (width, height), bytes(rgb)).save(path)


def unique_stem(prefix, ext):
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    stem = f"{prefix}_{stamp}"
    n = 2
    while os.path.exists(f"{stem}{ext}"):
        stem = f"{prefix}_{stamp}_{n}"
        n += 1
    return stem


def lcd_screenshot_path(prefix):
    return unique_stem(prefix, ".png") + ".png"


def lcd_process_screenshot_buffer(data, stem):
    info, fb, pal = lcd_parse_screenshot(data)
    path = lcd_screenshot_path(stem)
    lcd_save_screenshot_png(fb, pal, info["width"], info["height"], path)
    print(f"Saved image:      {path}")


def lcd_capture_screenshot(link, prefix, debug=False):
    print("\nRequesting LCD screenshot...")
    stats = {}
    try:
        data, _ = link.fetch(FRAME_LCD_SCREENSHOT, FRAME_LCD_SHOT_BEGIN, FRAME_CONTAINER_LCD_SCREENSHOT, timeout=2.0, stats=stats)
    except Exception:
        print(format_transfer_stats(stats))
        raise
    lcd_process_screenshot_buffer(data, prefix)
    if debug:
        print(format_transfer_stats(stats))


def fpga_capture_decode_blocks(data, start, samples, block_samples):
    out = bytearray(samples)
    pos = start
    prev = 0
    done = 0
    while done < samples:
        n = min(block_samples, samples - done)
        if pos >= len(data):
            raise FpgaCaptureError("encoded stream ends mid-block")
        mode = data[pos]
        pos += 1
        if mode == FPGA_CAPTURE_MODE_RAW:
            if pos + n > len(data):
                raise FpgaCaptureError("raw block runs past the encoded payload")
            out[done:done + n] = data[pos:pos + n]
            prev = data[pos + n - 1]
            pos += n
        elif mode == FPGA_CAPTURE_MODE_DELTA:
            acc = nbits = 0
            for i in range(done, done + n):
                if nbits < 4:
                    if pos >= len(data):
                        raise FpgaCaptureError("delta block runs past the encoded payload")
                    acc = (acc << 8) | data[pos]
                    pos += 1
                    nbits += 8
                code = (acc >> (nbits - 4)) & 0xF
                nbits -= 4
                if code == FPGA_CAPTURE_CODEC_ESCAPE:
                    if nbits < 8:
                        if pos >= len(data):
                            raise FpgaCaptureError("delta escape runs past the encoded payload")
                        acc = (acc << 8) | data[pos]
                        pos += 1
                        nbits += 8
                    sample = (acc >> (nbits - 8)) & 0xFF
                    nbits -= 8
                else:
                    delta = code // 2 if code % 2 == 0 else -(code + 1) // 2
                    sample = (prev + delta) & 0xFF
                acc &= (1 << nbits) - 1
                out[i] = prev = sample
        else:
            raise FpgaCaptureError("unknown block mode %d" % mode)
        done += n
    return bytes(out), pos


def fpga_capture_parse(data):
    if len(data) < FPGA_CAPTURE_HEADER_LEN:
        raise FpgaCaptureError("waveform capture is %d bytes, shorter than the header" % len(data))
    (magic, version, flags, samples_ch1, samples_ch2, bytes_per_sample,
     sample_rate_hz, timebase_ns_l, timebase_ns_h, crc_ch1, crc_ch2,
     payload_len, block_size, blocks, ring_len, settings_len, settings_crc,
     meas_ch1_len, meas_ch1_crc, meas_ch2_len, meas_ch2_crc,
     state_len, encoding, encoded_len, block_samples) = struct.unpack_from("<8s24I", data, 0)
    if magic != FPGA_CAPTURE_MAGIC:
        raise FpgaCaptureError("bad waveform capture magic %r" % magic)
    if version not in FPGA_CAPTURE_VERSIONS:
        raise FpgaCaptureError("unsupported waveform capture version %d (want %d)" % (version, FPGA_CAPTURE_VERSION))
    if encoding == FPGA_CAPTURE_ENC_RAW:
        if encoded_len != payload_len:
            raise FpgaCaptureError("raw payload says %d bytes, want %d" % (encoded_len, payload_len))
    elif encoding == FPGA_CAPTURE_ENC_BLOCKS:
        if block_samples != FPGA_CAPTURE_BLOCK_SAMPLES:
            raise FpgaCaptureError("unexpected codec block size %d (want %d)" % (block_samples, FPGA_CAPTURE_BLOCK_SAMPLES))
        if not 0 < encoded_len <= payload_len:
            raise FpgaCaptureError("encoded length %d does not fit %d samples" % (encoded_len, payload_len))
    else:
        raise FpgaCaptureError("unsupported sample encoding %d" % encoding)
    if block_size != 1024:
        raise FpgaCaptureError("bad block size %d (want 1024)" % block_size)
    if blocks == 0:
        raise FpgaCaptureError("waveform capture reports zero blocks")
    content_len = FPGA_CAPTURE_HEADER_LEN + encoded_len + state_len
    if len(data) not in (content_len, blocks * block_size):
        raise FpgaCaptureError("waveform capture is %d bytes, container is %d (header %d + payload %d + state %d)"
                        % (len(data), content_len, FPGA_CAPTURE_HEADER_LEN, encoded_len, state_len))
    if bytes_per_sample != 1:
        raise FpgaCaptureError("unsupported sample width %d bytes" % bytes_per_sample)
    if (settings_len, meas_ch1_len, meas_ch2_len) != (FPGA_CAPTURE_SETTINGS_LEN, FPGA_CAPTURE_MEAS_LEN, FPGA_CAPTURE_MEAS_LEN):
        raise FpgaCaptureError("unexpected state geometry %d + %d + %d" % (settings_len, meas_ch1_len, meas_ch2_len))
    if state_len != settings_len + meas_ch1_len + meas_ch2_len:
        raise FpgaCaptureError("state length %d != %d + %d + %d" % (state_len, settings_len, meas_ch1_len, meas_ch2_len))

    busy = bool(flags & FPGA_CAPTURE_FLAG_BUSY)
    ch2_en = bool(flags & FPGA_CAPTURE_FLAG_CH2)
    trigger_sample = None
    if version >= 5:
        visible_offset, visible_samples, record_start, trigger_sample = struct.unpack_from("<iIII", data, 104)
        full = bool(flags & FPGA_CAPTURE_FLAG_FULL) and not busy
    elif version >= 4:
        visible_offset, visible_samples, record_start = struct.unpack_from("<3I", data, 104)
        full = bool(flags & FPGA_CAPTURE_FLAG_FULL) and not busy
    else:
        visible_offset, visible_samples, record_start = 0, 0, 0
        full = False
    info = dict(version=version, flags=flags, busy=busy, ch2=ch2_en,
                full=full, visible_offset=visible_offset,
                visible_samples=visible_samples,
                window_start=visible_offset, window_length=visible_samples,
                trigger_sample=trigger_sample, record_start=record_start,
                samples_ch1=samples_ch1, samples_ch2=samples_ch2,
                sample_rate_hz=sample_rate_hz,
                timebase_ns=timebase_ns_l | (timebase_ns_h << 32),
                payload_len=payload_len, encoded_len=encoded_len,
                encoding=encoding, block_samples=block_samples,
                block_size=block_size, blocks=blocks, ring_len=ring_len)
    if busy:
        if samples_ch1 or samples_ch2 or payload_len or encoded_len:
            raise FpgaCaptureError("busy waveform capture carries sample data")
        info.update(samples_ch1=0, samples_ch2=0, payload_len=0,
                    encoded_len=0, encoding=FPGA_CAPTURE_ENC_RAW,
                    full=False, visible_offset=0, visible_samples=0,
                    window_start=0, window_length=0, trigger_sample=None,
                    record_start=0)
        encoded_len = 0
    else:
        if full:
            if visible_samples == 0:
                raise FpgaCaptureError("full waveform capture reports an empty visible window")
            if version >= 5:
                if trigger_sample is None or trigger_sample > samples_ch1:
                    raise FpgaCaptureError("trigger sample %s is outside the %d-sample record" % (trigger_sample, samples_ch1))
            elif (visible_samples > samples_ch1 or
                    visible_offset > samples_ch1 - visible_samples):
                raise FpgaCaptureError("visible window %d+%d does not fit %d samples" % (visible_offset, visible_samples, samples_ch1))
            if ring_len and record_start >= ring_len:
                raise FpgaCaptureError("record start %d is outside the %d-sample ring" % (record_start, ring_len))
        else:
            info.update(visible_offset=0, visible_samples=samples_ch1,
                        window_start=0, window_length=samples_ch1,
                        trigger_sample=None)
        if samples_ch2 != (samples_ch1 if ch2_en else 0):
            raise FpgaCaptureError("CH2 has %d samples, CH1 has %d (CH2 %s)" % (samples_ch2, samples_ch1, "enabled" if ch2_en else "disabled"))
        if payload_len != samples_ch1 + samples_ch2:
            raise FpgaCaptureError("payload length %d != %d + %d samples" % (payload_len, samples_ch1, samples_ch2))
    if FPGA_CAPTURE_HEADER_LEN + encoded_len + state_len > len(data):
        raise FpgaCaptureError("waveform capture content runs past the file")
    payload = data[FPGA_CAPTURE_HEADER_LEN:FPGA_CAPTURE_HEADER_LEN + encoded_len]
    state = data[FPGA_CAPTURE_HEADER_LEN + encoded_len:FPGA_CAPTURE_HEADER_LEN + encoded_len + state_len]
    if encoding == FPGA_CAPTURE_ENC_BLOCKS:
        ch1, pos = fpga_capture_decode_blocks(payload, 0, samples_ch1, block_samples)
        ch2 = b""
        if ch2_en:
            ch2, pos = fpga_capture_decode_blocks(payload, pos, samples_ch2, block_samples)
        if pos != len(payload):
            raise FpgaCaptureError("decoded %d of %d encoded bytes" % (pos, len(payload)))
    else:
        ch1 = payload[:samples_ch1]
        ch2 = payload[samples_ch1:]
    if not busy:
        if (zlib.crc32(ch1) & 0xFFFFFFFF) != crc_ch1:
            raise FpgaCaptureError("CH1 CRC32 mismatch")
        if ch2_en and (zlib.crc32(ch2) & 0xFFFFFFFF) != crc_ch2:
            raise FpgaCaptureError("CH2 CRC32 mismatch")
    settings = state[:settings_len]
    meas_ch1 = state[settings_len:settings_len + meas_ch1_len]
    meas_ch2 = state[settings_len + meas_ch1_len:]
    if (zlib.crc32(settings) & 0xFFFFFFFF) != settings_crc:
        raise FpgaCaptureError("settings CRC32 mismatch")
    if (zlib.crc32(meas_ch1) & 0xFFFFFFFF) != meas_ch1_crc:
        raise FpgaCaptureError("CH1 measurements CRC32 mismatch")
    if (zlib.crc32(meas_ch2) & 0xFFFFFFFF) != meas_ch2_crc:
        raise FpgaCaptureError("CH2 measurements CRC32 mismatch")
    info.update(settings=settings, meas_ch1=meas_ch1, meas_ch2=meas_ch2)
    return info, ch1, ch2


def fpga_capture_state_buffer(info):
    cfg = CONFIG_DSO3D12
    buf = bytearray(cfg['meas_ch2_offset'] + cfg['meas_length'])
    buf[cfg['settings_offset']:cfg['settings_offset'] + cfg['settings_length']] = info["settings"]
    buf[cfg['meas_ch1_offset']:cfg['meas_ch1_offset'] + cfg['meas_length']] = info["meas_ch1"]
    buf[cfg['meas_ch2_offset']:cfg['meas_ch2_offset'] + cfg['meas_length']] = info["meas_ch2"]
    return bytes(buf)


def fpga_capture_state_dict(info):
    cfg = CONFIG_DSO3D12
    buf = fpga_capture_state_buffer(info)
    state = {label: get_val(buf, off, size, signed=signed)
             for off, (label, size, signed) in cfg['map'].items()}
    return buf, state


# Fast-render interpolation bank from the stock firmware
_ZW_SINC_BANK = ("eNp9lP1LVFkYx+95mTvXUcepGNzA3ghrqx9cFFEytWQF26SYoMzwByHaUhwozCTzhVZxjY2BEmES84cFqRVZKk3UWAmMGpNSEEoEHc2XmVR8ievMvfecc+8+f0Hnt8M5POc83+f7+d6SGq0/pQrrb6nQGpN2W070n9mKvokksq7faeiXX/Mj+Ir5G1o3V6U0q18qsdqkaqte+svySkuSw3KgWTMXdZo+dNx04Raxk2wyy+ZTw3UivlQvou/4IzwrJtF1sxwNmT+jLdOQfrKmpHPIbzajInMSGSIflwtMyngVPWC0KysbnrsjbilSL6eyCfKF9+IukYj3mX3ohnkTdcNrz9EvZhTNiGL8u1jDPXyGXGV9tiZtwRG7Nly9uefld5/SqwsaZM1knQ9in8jEmgiiX81OJONJcRnfEBN4gdcTO++gjcZ7+WD0U5wazqksP3R/o8bh0XbIwsinBfwMiRP/4gciD4eFis7iZti5RRqp4jqpZVm2gN5tJ5ELzq7lOW9iSsdaelxilNgzjVU6wD6Qdu4mKcKP/SIHt+ACsYU/8j/IXl5MXWzAlqFfUo5uVyYkLQ1em86QVnrjnZFxe6t+23aKpdJsXka+8iAuEjX4BU4S+6HaEJlnT+iI4ZQntXGlXU12nV+cK207GQiFnCe2KxS3HrSFjHs0yp6Rf/guclg8xaMYiyxSy6fJMBuhj41suVOLjbmoel25i97iY6cdy4GEbnVKeaMlyz3GKzoKmjfxdKKIt3gcM54Hvc6TfjZGHxr5sl9zxpSoha7Pi3WeOs/nxUJXieqM8Wv58kNjjPazebidRxgfx2+xItKh0gQZZa9oj5Esv9GmlG41kOBYPnbaWwyvuy6qsTGdWrb82Bihw2wafplFsBjFT/FhsQs6eEai7B4NGUGbW69QTmyHnIFQ28m50vOLya52dVyZ1JzyiPGEzrMhUGc/SRIvcA0oFsRfQb1snkpPsdu2Vn3c7oz0xksr0xmD15KWKhOObl9SMvQBm4sV070wkY98C6bTgnNgUn6cItxQ7QMZYKs00yD2xGh6XMdaYsqct2v5gpNEuu0BPctWy3ToNY24wRHN4ixWURhc8gB2ceIMKeD5VBg7ZI9W47i/UX4op1INf4o7GH0vNxod1A7OW+AT4MLL4EYZd4Izg0gDl/rEIF7nzSTIBO3VfcrL75t7hqtj1xYcTVqf7SqbIT18DVxfjGdEFCh4jnKBiJtARh/aZyYCKb34C2ieyuplKTLi9txd2WhXDhhVtIxjUg6kGcBiEZDnN8+hKSDRkLaAyiGg8zqwOCse4Xe8iJbqIj5c51Mt2ybbSVqECx8HwjuBvVnTgRzWkuSFBKiHJGiDROiHZFiV1iElrphH8GveL99pWNeTyDfRCmniRLshWQohYSogaRqtW9KPl9Xwo9P/AfR+Op8=")
_ZW_SINC_TAP31 = ("eNoBKADX/5r/Nf/V/nz+LP7n/a79hP1p/V/9Zf18/aP92P0c/m3+x/4r/5T/AABi1Rxu")
_zw_sinc_cache = None


def zw_sinc_bank():
    global _zw_sinc_cache
    if _zw_sinc_cache is None:
        raw = zlib.decompress(base64.b64decode(_ZW_SINC_BANK))
        bank = np.frombuffer(raw, dtype="<i2").reshape(20, 30)
        tail = np.frombuffer(zlib.decompress(base64.b64decode(_ZW_SINC_TAP31)), dtype="<i2").reshape(20, 1)
        _zw_sinc_cache = np.hstack((bank, tail)).astype(np.int64)
    return _zw_sinc_cache


def trigger_crossing(samples, level, edge, center, margin=32):
    if not samples or level is None:
        return None
    a = np.frombuffer(samples, dtype=np.uint8).astype(np.int32)
    lo = max(0, int(center) - margin)
    hi = min(len(a) - 1, int(center) + margin)
    rising = edge == 0
    best = None
    for i in range(lo, hi):
        x, y = int(a[i]), int(a[i + 1])
        if x == y or (y > x) != rising or not (min(x, y) <= level <= max(x, y)):
            continue
        pos = i + (level - x) / (y - x)
        if best is None or abs(pos - center) < abs(best - center):
            best = pos
    return best


def sinc_trigger_crossing(samples, level, edge, center, span=3.0):
    if not samples or level is None:
        return None
    ctx = np.frombuffer(samples, dtype=np.uint8).astype(np.int64)
    bank = zw_sinc_bank()
    offs = np.arange(31)
    last = len(ctx) - 1
    high = min(int(level) + 2, 240)
    low = max(int(level) - 2, 10)
    rising = edge == 0
    n = int(round(2.0 * span * 20.0)) + 1
    ps = center - span + np.arange(n) / 20.0
    vals = np.empty(n)
    for i, p in enumerate(ps):
        k = int(np.floor(p))
        phase = int(np.floor(20.0 * (p - k) - 1.0 + 1e-9))
        if phase < 0:
            phase, base = 19, k - 15
        else:
            base = k - 14
        acc = int(bank[phase] @ ctx[np.clip(base + offs, 0, last)])
        vals[i] = min(max(acc, 0), 255 << 15) >> 15
    outside = vals <= low if rising else vals >= high
    entered = vals >= high if rising else vals <= low
    seen = False
    for i in range(n):
        if outside[i]:
            seen = True
        if seen and entered[i]:
            return float(ps[i])
    return None


def fpga_capture_interp_trace(bins, context, ctx_left, n, frac):
    xs = np.concatenate(([0.0], np.arange(300) + 0.5, [300.0]))
    cols = np.concatenate(([0], np.arange(300), [299]))
    pos = frac + cols * n / 300.0
    ctx = np.frombuffer(context, dtype=np.uint8).astype(np.int64)
    bank = zw_sinc_bank()
    last = len(ctx) - 1
    offs = np.arange(31)
    curve = np.empty(len(xs))
    for i, p in enumerate(pos):
        k = int(np.floor(p))
        phase = int(np.floor(20.0 * (p - k) - 1.0 + 1e-9))
        if phase < 0:
            phase, base = 19, k - 15 + ctx_left
        else:
            base = k - 14 + ctx_left
        idx = np.clip(base + offs, 0, last)
        acc = int(bank[phase] @ ctx[idx])
        curve[i] = min(max(acc, 0), 255 << 15) >> 15
    return dict(x=xs, lo=curve, hi=curve, p05=curve, p25=curve, p50=curve,
                p75=curve, p95=curve, density=None,
                extent=(0.0, 300.0, -0.5, 255.5))

MAX_INTERP_SAMPLES = 300


def fpga_capture_wave_layers(samples, bins, columns=None, span=None, interp=False,
                     context=None, ctx_left=0, n=None, frac=0.0,
                     col_start=0, col_end=300):
    a = np.frombuffer(samples, dtype=np.uint8).astype(np.int32)
    if n is None:
        n = len(a)
    if interp and context is not None and 2 <= n <= MAX_INTERP_SAMPLES:
        return fpga_capture_interp_trace(bins, context, ctx_left, n, frac)
    u = np.arange(len(a)) - frac
    keep = u <= n
    u = u[keep]
    a = a[keep]
    scale = 300.0 / n
    columns = max(1, int(round(bins)) if columns is None else int(round(columns)))
    if len(a) == 0:
        return dict(x=np.empty(0), lo=np.empty(0), hi=np.empty(0),
                    p05=np.empty(0), p25=np.empty(0), p50=np.empty(0),
                    p75=np.empty(0), p95=np.empty(0),
                    density=np.zeros((256, columns)),
                    extent=(0.0, 300.0, -0.5, 255.5))
    span_frac = (len(a) * scale) / 300.0
    nb = max(1, min(int(round(columns * span_frac)), len(a)))
    edges = np.linspace(0, len(a), nb + 1).astype(np.int64)
    lo = np.minimum.reduceat(a, edges[:-1])
    hi = np.maximum.reduceat(a, edges[:-1])
    pct = np.empty((5, nb))
    for i in range(nb):
        pct[:, i] = np.percentile(a[edges[i]:edges[i + 1]], (5, 25, 50, 75, 95))
    x0 = u[0] * scale
    x = x0 + (np.arange(nb) + 0.5) * (len(a) * scale) / nb
    cidx = np.clip(np.floor((u + 0.5) * columns / n).astype(np.int64),
                   0, columns - 1)
    hist = np.bincount(cidx * 256 + a, minlength=columns * 256).reshape(columns, 256)
    peak = hist.max()
    density = np.zeros(hist.shape)
    if peak > 0:
        np.power(hist / peak, 0.5, out=density)
        density *= 0.85
    if col_start > 0 or col_end < 300:
        xc = (np.arange(columns) + 0.5) * 300.0 / columns
        density[(xc < col_start) | (xc >= col_end), :] = 0.0
        mask = (x < col_start) | (x >= col_end)
        lo = np.where(mask, np.nan, lo)
        hi = np.where(mask, np.nan, hi)
        pct[:, mask] = np.nan
    return dict(x=x, lo=lo, hi=hi, p05=pct[0], p25=pct[1], p50=pct[2],
                p75=pct[3], p95=pct[4],
                density=density.T, extent=(0.0, 300.0, -0.5, 255.5))


def timebase_label(ns):
    if ns < 1000: return f"{ns:g}ns"
    if ns < 1000000: return f"{ns / 1000:g}us"
    if ns < 1000000000: return f"{ns / 1e6:g}ms"
    return f"{ns / 1e9:g}s"


def fpga_capture_process_buffer(data, stem, args):
    info, ch1, ch2 = fpga_capture_parse(data)
    if info["busy"]:
        print("Scope is busy - stop acquisition or trigger the scope, then retry.")
        return False
    buf, state = fpga_capture_state_dict(info)
    explicit = args.window is not None
    if explicit:
        start, requested = args.window
        count = len(ch1) - start if requested is None else requested
        if not 0 <= start < len(ch1) or count <= 0:
            print(f"Error: window {start}:{count} is outside the {len(ch1)}-sample record.")
            return False
        count = min(count, len(ch1) - start)
        data_start, data_count = start, count
        win_len, frac = count, 0.0
        window = (start, count, info["trigger_sample"])
        image_stem = f"{stem}_w{start}_{count}"
        print(f"Window:           Samples {start}-{start + count}/{len(ch1)}")
    else:
        win_start, win_len = info["window_start"], info["window_length"]
        if win_len <= 0:
            win_start, win_len = 0, len(ch1)
        trigger = info["trigger_sample"]
        if trigger is None and info["full"]:
            tb_ns = state.get("Timebase Value (ns/div)", 0)
            delay_ps = state.get("Horiz Trigger Delay (ps)", 0)
            pos = 150.0 + (((delay_ps / 1000.0) / tb_ns) * 25.0 if tb_ns > 0 else 0.0)
            trigger = info["visible_offset"] + pos / 300.0 * info["visible_samples"]
        w_off = state.get("Window Address Offset (1/1000 smp)", 0) / 1000.0
        disp_start = float(win_start)
        if (info["full"] and trigger is not None
                and state.get("Fast Render Enable", 0) == 1):
            trig_samples = ch2 if state.get("Trigger Source", 0) == 1 and ch2 else ch1
            level = state.get("Trigger Level ADC")
            edge = state.get("Trigger Edge", 0)
            cross = None
            if state.get("Render Scale Factor", 0) >= 20001:
                cross = sinc_trigger_crossing(trig_samples, level, edge, trigger)
            if cross is None:
                cross = trigger_crossing(trig_samples, level, edge, trigger)
            if cross is not None and 0.0 <= cross - w_off \
                    and cross - w_off + win_len <= len(ch1):
                disp_start = cross - w_off
        lo = max(int(np.floor(disp_start)), 0)
        hi = min(int(np.ceil(disp_start + win_len)), len(ch1))
        data_start, data_count = lo, max(hi - lo, 0)
        frac = disp_start - data_start
        window = (disp_start, win_len, disp_start + w_off) if info["full"] else None
        image_stem = stem
        if window is not None and data_count == 0:
            print(f"Note:             the {win_len}-sample window at {win_start} "
                  f"misses the {len(ch1)}-sample record; rendering an empty window.")
        elif window is not None and (win_start, win_len) != (0, len(ch1)):
            print(f"Window:           {data_count} samples {win_start}-{win_start + win_len}/{len(ch1)}")
    title_text = None
    if args.title:
        title_text = args.title
        if args.datetime: title_text += f" {datetime.now():%Y-%m-%d %H:%M:%S}"
    sidecar = args.debug or args.sidecar
    if sidecar:
        save_capture_csv(image_stem, info, state, ch1, ch2,
                         data_start, data_count, frac)
    disp = write_scope_text(buf, image_stem, state, CONFIG_DSO3D12,
                            title_text=title_text or
                            f"Zeeweii Buffer Dump ({datetime.now():%Y-%m-%d %H:%M:%S})",
                            debug=args.debug,
                            write_file=sidecar)
    if explicit and info["sample_rate_hz"]:
        disp["tb_str"] = timebase_label(count * 1e9 / (info["sample_rate_hz"] * 12.0))
    bins = max(300, int(round(args.width * 0.73)))
    fast_interp = (state.get("Fast Render Enable", 0) == 1
                   and state.get("Render Scale Factor", 0) >= 20001)
    col_start, col_end = 0, 300
    if not explicit and state.get("Roll Mode Enable", 0) == 1:
        col_start = max(0, min(int(state.get("Display Start Column", 0)), 299))
        col_end = min(300, max(col_start + 1,
                               int(state.get("Display End Column", 299)) + 1))
    layers = {}
    if data_count > 0:
        trig_src = state.get("Trigger Source", 0)
        skew = 0.5 if ch2 and state.get("CH2 Enabled", 0) == 1 else 0.0
        for ch, samples in ((1, ch1), (2, ch2)):
            if not samples:
                continue
            ch_frac = frac
            if skew:
                if ch == 2 and trig_src == 0: ch_frac += skew
                elif ch == 1 and trig_src == 1: ch_frac -= skew
            lo_ctx = max(0, data_start - 18)
            hi_ctx = min(len(samples), data_start + win_len + 19)
            layers[ch] = fpga_capture_wave_layers(
                samples[data_start:data_start + data_count], bins,
                interp=fast_interp,
                context=samples[lo_ctx:hi_ctx], ctx_left=data_start - lo_ctx,
                n=win_len, frac=ch_frac, col_start=col_start, col_end=col_end)
    title_text = None
    if args.title:
        title_text = args.title
        if args.datetime: title_text += f" {datetime.now():%Y-%m-%d %H:%M:%S}"
    write_scope_image(buf, state, args, image_stem, title_text, disp,
                      config=CONFIG_DSO3D12, layers=layers, window=window)
    return True


def process_push(buffer, args):
    if len(buffer) >= 800 and b"--CH1--" in buffer:
        base_name = unique_stem(PUSH_BUFFER_PREFIX, ".bin")
        with open(f"{base_name}.bin", "wb") as f: f.write(buffer)
        print(f"\nSaved data:       {base_name}.bin")
        text = buffer.replace(b"\x00", b"").decode("utf-8", errors="ignore")
        parts = text.split("--------CH1--------")
        if len(parts) > 1:
            content = parts[1]
            ch1_str, ch2_str = content, ""
            if "--------CH2--------" in content:
                ch1_str, ch2_str = content.split("--------CH2--------", 1)
            for suffix, section in (("ch1", ch1_str), ("ch2", ch2_str)):
                if not section:
                    continue
                samples = bytes(int(t) & 0xFF for t in re.findall(r"\b\d+\b", section))
                if not samples:
                    continue
                path = f"{base_name}-{suffix}.bin"
                with open(path, "wb") as f: f.write(samples)
                print(f"Extracted {suffix.upper()}:    {path} ({len(samples)} samples)")
    elif PUSH_STATE_MIN <= len(buffer) <= PUSH_STATE_MAX:
        stem = unique_stem(output_prefix(args, DEFAULT_OUTPUT), ".bin")
        with open(f"{stem}.bin", "wb") as f: f.write(buffer)
        print(f"\nSaved data:       {stem}.bin")
        process_capture(buffer, stem, args)
        if args.debug: debug_diff(buffer)
    elif len(buffer) < 800:
        text = buffer.decode("utf-8", errors="ignore").strip()
        if text:
            print(text)
    else:
        print(f"Invalid data size: {len(buffer)} bytes")


def fpga_capture_path(prefix):
    return unique_stem(prefix, ".bin")


def fpga_capture_request(link, prefix, args):
    print("\nRequesting waveform capture...")
    stats = {}
    try:
        data, _ = link.fetch_retry(FRAME_FPGA_CAPTURE, FRAME_FPGA_CAPTURE_BEGIN,
                                   FRAME_CONTAINER_FPGA_CAPTURE, timeout=5.0,
                                   stats=stats, debug=args.debug)
    except Exception:
        print(format_transfer_stats(stats))
        raise
    if args.debug:
        print(format_transfer_stats(stats))
    stem = fpga_capture_path(prefix)
    path = f"{stem}.bin"
    with open(path, "wb") as f: f.write(data)
    print(f"Saved data:       {path}")
    fpga_capture_process_buffer(data, stem, args)


def _open_scope_once(port, baud, timeout, toggle_lines):
    ser = serial.Serial(None, baud, bytesize=8, parity="N", stopbits=1,
                        timeout=timeout)
    ser.port = port
    if toggle_lines:
        ser.dsrdtr = True
        ser.dtr = False
        ser.rts = False
    else:
        ser._zt_orig_update_dtr = getattr(ser, "_update_dtr_state", None)
        ser._zt_orig_update_rts = getattr(ser, "_update_rts_state", None)
        for name in ("_update_dtr_state", "_update_rts_state"):
            if hasattr(ser, name):
                setattr(ser, name, lambda: None)
    ser.open()
    return ser


def _clear_hangup(ser, port, toggle_lines):
    if toggle_lines:
        return
    if termios is None:
        return
    try:
        attrs = termios.tcgetattr(ser.fd)
        attrs[2] &= ~termios.HUPCL
        termios.tcsetattr(ser.fd, termios.TCSANOW, attrs)
    except Exception as e:
        print("could not clear HUPCL on %s (%s), power cycle the scope." % (port, e))


SCOPE_WAIT_POLL = 0.25
SCOPE_WAIT_DROP = 2.0
SCOPE_HELLO_TRIES = 3
SCOPE_HELLO_PAUSE = 1.0


def looks_like_serial_port(port):
    if not port:
        return False
    if port.startswith("/dev/") or port.startswith("\\\\."):
        return True
    if port.startswith(("cu.", "tty.")):
        return True
    return port.upper().startswith("COM") and port[3:].isdigit()


def normalize_scope_port(port):
    if port and port.startswith(("cu.", "tty.")) and not os.path.exists(port):
        return "/dev/" + port
    return port


def scope_port_nodes(port):
    port = normalize_scope_port(port)
    twin = serial_node_twin(port)
    if twin is None:
        return [port]
    if port.startswith("/dev/tty."):
        return [twin, port]
    return [port, twin]


def wait_for_scope_port(port, poll=SCOPE_WAIT_POLL, drop=SCOPE_WAIT_DROP):
    if not sys.stdin.isatty():
        return None
    nodes = scope_port_nodes(port)
    fd = saved = None
    try:
        import tty as tty_mod
    except ImportError:
        return None
    try:
        fd = sys.stdin.fileno()
        saved = termios.tcgetattr(fd)
        tty_mod.setcbreak(fd)
    except Exception:
        return None
    gone = False
    announced = False
    deadline = time.monotonic() + drop
    try:
        while True:
            try:
                ready = select.select([sys.stdin], [], [], poll)[0]
            except (OSError, ValueError):
                return None
            if ready:
                try:
                    os.read(fd, 1)
                except OSError:
                    return None
                return False
            present = any(os.path.exists(node) for node in nodes)
            if present:
                if gone:
                    return True
                if time.monotonic() >= deadline:
                    return None
                continue
            gone = True
            if not announced:
                print("Port is no longer available, power the scope back on to retry, or press any key to cancel...")
                announced = True
    finally:
        if saved is not None:
            try:
                termios.tcsetattr(fd, termios.TCSADRAIN, saved)
            except Exception:
                pass


def open_scope_port(port, baud=SCOPE_BOOT_BAUD, timeout=10, toggle_lines=False, quiet=False):
    targets = [node for node in scope_port_nodes(port) if os.path.exists(node)]
    if not targets:
        targets = [port]
    failure = None
    for index, attempt in enumerate(targets):
        try:
            ser = _open_scope_once(attempt, baud, timeout, toggle_lines)
        except serial_exceptions as e:
            failure = e
            continue
        _clear_hangup(ser, attempt, toggle_lines)
        return ser
    raise LinkError("cannot open %s%s (%s), power cycle the scope" % (port, "" if len(targets) == 1 else " (nor its sibling)", failure))


def close_quietly(ser):
    if ser is not None:
        try:
            ser.close()
        except Exception:
            pass


def open_scope_link(port, baud, hello_tries=None, hello_pause=None):
    tries = max(1, SCOPE_HELLO_TRIES if hello_tries is None else hello_tries)
    pause = SCOPE_HELLO_PAUSE if hello_pause is None else hello_pause
    ser = None
    while True:
        if ser is None:
            try:
                ser = open_scope_port(port, quiet=True)
            except LinkError as e:
                reason = str(e)
            else:
                for attempt in range(tries):
                    try:
                        link, rate, info = open_link(ser, baud)
                    except LinkError as e:
                        reason = str(e)
                        if attempt + 1 == tries:
                            break
                        time.sleep(pause)
                    except serial_exceptions as e:
                        reason = "lost %s during the handshake: %s" % (port, e)
                        break
                    else:
                        return ser, link, rate, info
                close_quietly(ser)
                ser = None
        retry = wait_for_scope_port(port)
        if retry is None:
            raise BackupError(BACKUP_NO_PORT, reason)
        if not retry:
            raise BackupError(BACKUP_NO_PORT, "canceled")


def try_scope_link(port, baud):
    try:
        ser = open_scope_port(port, quiet=True)
    except serial_exceptions + (LinkError,):
        return None
    try:
        for attempt in range(SCOPE_HELLO_TRIES):
            try:
                link, rate, _info = open_link(ser, baud)
            except (LinkError, FrameTimeout, ScopeError) as e:
                if attempt + 1 == SCOPE_HELLO_TRIES:
                    raise e
                time.sleep(SCOPE_HELLO_PAUSE)
            else:
                return ser, link, rate
    except (serial_exceptions + (LinkError, FrameTimeout, ScopeError)):
        pass
    close_quietly(ser)
    return None


serial_exceptions = (OSError, serial.SerialException)
if termios:
    serial_exceptions += (termios.error,)


CONTAINER_MAGIC = 0xA0FFFF9F
CONTAINER_HEADER_LEN = 0x40
CONTAINER_HEADER_PAGE = 0x400
CONTAINER_TYPE_SECBOOT = 0
CONTAINER_TYPE_APP = 1

ISP_FRAME_OPENER = 0x21
ISP_ESC = 0x1B
ISP_CMD_BAUD = 0x31
ISP_CMD_REBOOT = 0x3F
ISP_RATES = (115200, 460800, 921600, 1000000, 2000000)
ISP_DOWNLOAD_BAUD = 2000000
ISP_LADDER = (2000000, 1000000, 921600, 460800, 115200)
ISP_SWITCH_DELAY = 0.02
ISP_COMMAND_WINDOW = 0.15
ISP_POLL = 0.001
ISP_SYNC_MIN = 3
ISP_SYNC_TIMEOUT = 60.0
ISP_SYNC_QUICK = 10.0
ISP_ESC_CADENCE = 0.01
ISP_SYNC_GAP = 0.03
ISP_SWITCH_SYNC = 1.5

APP_HDR_ADDR = 0x08010000
FLASH_BASE = 0x08000000
FLASH_SECTOR = 0x1000
CAL_START = 0x08096000
MARKER_ADDR = 0x080FF000
FLASH_END = 0x08100000
CH340_VID = 0x1A86
CH340_PIDS = (0x7523, 0x7522, 0x5523)

XMODEM_STX = 0x02
XMODEM_EOT = 0x04
XMODEM_ACK = 0x06
XMODEM_CAN = 0x18
XMODEM_NAK = 0x15
XMODEM_C = ord('C')
XMODEM_P = ord('P')
XMODEM_BLOCK_LEN = 1024
XMODEM_FILL = 0x1A
XMODEM_WIRE_LEN = 3 + XMODEM_BLOCK_LEN + 2
XMODEM_RETRIES = 16
XMODEM_BYTE_TIMEOUT = 1.0
XMODEM_EOT_TRIES = 4
ISP_READY = (XMODEM_C, XMODEM_P)

ISP_BEACONS = {
    XMODEM_C: "ready / waiting for an XMODEM start",
    ord('D'): "host cancelation",
    ord('F'): "no data received after timeout",
    ord('G'): "packet number incorrect",
    ord('I'): "image too large",
    ord('J'): "image burning address illegal",
    ord('K'): "image page not aligned",
    ord('L'): "image head verification error",
    ord('M'): "image content verification error",
    XMODEM_P: "image incomplete or missing",
    ord('N'): "flash ID self-check failed",
    ord('Q'): "firmware type error",
    ord('Y'): "decryption read of secboot failed",
    ord('Z'): "signature verification failed",
    ord('R'): "command verification error",
    ord('S'): "command parameter error",
    ord('T'): "failed to obtain FT parameters",
    ord('U'): "failed to set gain",
    ord('V'): "setting MAC failed",
}

FLASH_REFUSED = 2
FLASH_NO_PORT = 3
FLASH_NO_SYNC = 4
FLASH_FRAME_REJECTED = 5
FLASH_TRANSFER = 6
FLASH_ABORTED = 7
FLASH_PORT_GONE = 8


class FlashError(Exception):
    def __init__(self, code, message):
        super().__init__(message)
        self.code = code


def isp_frame(cmd, *params):
    body = struct.pack("<%dI" % (1 + len(params)), cmd, *params)
    return struct.pack("<BHH", ISP_FRAME_OPENER, 2 + len(body), frame_crc16(body)) + body


def xmodem_crc16(data):
    crc = 0x0000
    for byte in data:
        crc ^= byte << 8
        for _ in range(8):
            crc = ((crc << 1) ^ 0x1021) & 0xFFFF if crc & 0x8000 else (crc << 1) & 0xFFFF
    return crc


def jamcrc32(data):
    return zlib.crc32(data) ^ 0xFFFFFFFF


class FlashImage:
    __slots__ = ("index", "offset", "record_len", "image_type", "attrs",
                 "run_addr", "run_len", "hdr_addr", "upgrade_addr", "upd_no",
                 "version", "flags", "next_boot", "stream", "path")

    def __init__(self, index, offset, image_type, attrs, run_addr, run_len,
                 hdr_addr, upgrade_addr, upd_no, version, flags, next_boot,
                 stream, path):
        self.index = index
        self.offset = offset
        self.image_type = image_type
        self.attrs = attrs
        self.run_addr = run_addr
        self.run_len = run_len
        self.hdr_addr = hdr_addr
        self.upgrade_addr = upgrade_addr
        self.upd_no = upd_no
        self.version = version
        self.flags = flags
        self.next_boot = next_boot
        self.stream = stream
        self.path = path
        self.record_len = len(stream)

    @property
    def label(self):
        name = {CONTAINER_TYPE_SECBOOT: "secboot", CONTAINER_TYPE_APP: "app"}.get(self.image_type)
        return name if name else "type %d" % self.image_type

    @property
    def name(self):
        text = self.version.split(b"\x00")[0].decode("latin-1")
        return text or ("image%d %s" % (self.index, self.label))

    @property
    def span(self):
        lo = min(self.hdr_addr, self.run_addr)
        hi = max(self.hdr_addr + CONTAINER_HEADER_PAGE,
                 self.run_addr + self.run_len)
        return lo, hi

    @property
    def sectors(self):
        lo, hi = self.span
        return ((lo - FLASH_BASE) // FLASH_SECTOR, (hi - 1 - FLASH_BASE) // FLASH_SECTOR)

    def blocks(self):
        return (self.run_len + CONTAINER_HEADER_LEN + XMODEM_BLOCK_LEN - 1) // XMODEM_BLOCK_LEN

    def wire_bytes(self):
        return self.blocks() * XMODEM_WIRE_LEN

    def describe(self):
        lo, hi = self.span
        first, last = self.sectors
        return ("%s  run 0x%08X  header 0x%08X  body %d bytes 0x%08X..0x%08X  sectors %d-%d  upd_no %d"
                % (self.name, self.run_addr, self.hdr_addr, self.run_len, lo, hi, first, last, self.upd_no))


def parse_container(blob, path):
    records = []
    offset = 0
    while offset < len(blob):
        if len(blob) - offset < CONTAINER_HEADER_LEN:
            raise FlashError(FLASH_REFUSED, "%s: %d bytes after image%d are shorter than a 64-byte header" % (path, len(blob) - offset, len(records)))
        (magic, image_type, attrs, run_addr, run_len, hdr_addr, upgrade_addr,
         body_crc, upd_no, version, flags, reserved, next_boot,
         header_crc) = struct.unpack_from("<IHH6I16s4I", blob, offset)
        if magic != CONTAINER_MAGIC:
            raise FlashError(FLASH_REFUSED, "%s: no container header at offset 0x%X (magic 0x%08X), file not recognized." % (path, offset, magic))
        record_len = CONTAINER_HEADER_LEN + run_len
        if offset + record_len > len(blob):
            raise FlashError(FLASH_REFUSED, "%s: image%d declares a %d-byte body but the file ends %d bytes later" % (path, len(records), run_len, len(blob) - offset - CONTAINER_HEADER_LEN))
        if jamcrc32(blob[offset:offset + 0x3C]) != header_crc:
            raise FlashError(FLASH_REFUSED, "%s: image%d header checksum is 0x%08X, the bytes are 0x%08X" % (path, len(records), header_crc, jamcrc32(blob[offset:offset + 0x3C])))
        stream = blob[offset:offset + record_len]
        if jamcrc32(stream[CONTAINER_HEADER_LEN:]) != body_crc:
            raise FlashError(FLASH_REFUSED, "%s: image%d content checksum does not match the body" % (path, len(records)))
        records.append(FlashImage(len(records), offset, image_type, attrs, run_addr, run_len, hdr_addr, upgrade_addr,
                                  upd_no, version, flags, next_boot, stream, path))
        offset += record_len
    if not records:
        raise FlashError(FLASH_REFUSED, "%s is empty" % path)
    return records


def select_app_image(records, path):
    for image in records:
        if (image.image_type == CONTAINER_TYPE_APP
                and image.hdr_addr == APP_HDR_ADDR):
            return image
    raise FlashError(FLASH_REFUSED, "application image not found in %s at 0x%08X (types: %s)." % (path, APP_HDR_ADDR, ", ".join("%s at 0x%08X" % (image.label, image.hdr_addr) for image in records)))


def check_app_span(image):
    lo, hi = image.span
    if hi > FLASH_END:
        reason = "reaches past end of flash: 0x%08X" % hi
    elif hi > MARKER_ADDR:
        reason = ("reaches bootloader: 0x%08X" % MARKER_ADDR)
    elif hi > CAL_START:
        reason = ("reaches persistent storage; 0x%08X" % CAL_START)
    elif lo < APP_HDR_ADDR:
        reason = ("starts at 0x%08X, below the app image at 0x%08X" % (lo, APP_HDR_ADDR))
    else:
        return
    raise FlashError(FLASH_REFUSED, "%s (%s) invalid: %s" % (image.name, image.describe(), reason))


def flash_preflight(path):
    try:
        with open(path, "rb") as handle:
            blob = handle.read()
    except OSError as e:
        raise FlashError(FLASH_REFUSED, "cannot read %s (%s)" % (path, e))
    records = parse_container(blob, path)
    image = select_app_image(records, path)
    check_app_span(image)
    return records, image


def is_flash_container(path):
    if not path or not os.path.isfile(path):
        return False
    try:
        with open(path, "rb") as handle:
            head = handle.read(4)
    except OSError:
        return False
    return len(head) == 4 and struct.unpack("<I", head)[0] == CONTAINER_MAGIC


def isp_rate_arg(rate):
    if rate in ISP_RATES:
        return
    raise FlashError(FLASH_REFUSED, "--baud %s unsupported, specify %s" % (baud_label(rate), ", ".join(baud_label(r) for r in ISP_RATES)))


def beacon_name(byte):
    if byte is None:
        return "nothing at all"
    letter = chr(byte) if 32 <= byte < 127 else None
    meaning = ISP_BEACONS.get(byte)
    if letter and meaning:
        return "'%s' (%s)" % (letter, meaning)
    if letter:
        return "'%s'" % letter
    return "byte 0x%02X" % byte


def prompt_text(prompt):
    if not sys.stdin.isatty():
        raise FlashError(FLASH_REFUSED, "valid terminal required for flashing.")
    try:
        return input(prompt)
    except EOFError:
        raise FlashError(FLASH_REFUSED, "the prompt was not answered; nothing was sent")
    except KeyboardInterrupt:
        raise FlashError(FLASH_ABORTED, "stopped before the first byte")


def serial_node_twin(port):
    for prefix, other in (("/dev/tty.", "/dev/cu."), ("/dev/cu.", "/dev/tty.")):
        if port.startswith(prefix):
            return other + port[len(prefix):]
    return None


def is_ch340_port(info):
    if info.vid == CH340_VID and info.pid in CH340_PIDS:
        return True
    if info.vid is not None and info.pid is not None:
        return False
    text = " ".join(str(getattr(info, field) or "")
                    for field in ("device", "description", "hwid", "manufacturer", "product"))
    text = text.lower()
    return any(tag in text for tag in ("ch34", "wch", "1a86"))


def default_serial_port_index(infos):
    if len(infos) == 1:
        return 0
    bridges = [index for index, info in enumerate(infos) if is_ch340_port(info)]
    return bridges[0] if len(bridges) == 1 else None


def serial_port_candidates():
    try:
        found = list(serial.tools.list_ports.comports())
    except Exception as e:
        print("could not enumerate serial ports (%s)" % e)
        return None
    real = []
    for info in found:
        if not is_ch340_port(info):
            continue
        dev = info.device
        if dev.startswith("/dev/ttyS"):
            continue
        if dev.startswith("/dev/tty.") and any(d.device == "/dev/cu." + dev[9:] for d in found):
            continue
        real.append(info)
    return sorted(real, key=lambda info: info.device)


def print_serial_ports(infos):
    default = default_serial_port_index(infos)
    for index, info in enumerate(infos, 1):
        bridge = "  [CH340]" if is_ch340_port(info) else ""
        default_tag = "  (default)" if index - 1 == default else ""
        print("  %2d) %-24s %s%s%s"
              % (index, info.device, info.description, bridge, default_tag))
    return default


def list_serial_ports():
    found = serial_port_candidates()
    if found is None:
        print("use --port to specify a port")
        return []
    if not found:
        return []
    print_serial_ports(found)
    return found


PORT_LIST = object()


def show_serial_ports():
    infos = serial_port_candidates()
    if infos is None:
        return EXIT_FAIL
    if not infos:
        print("No eligible serial ports found, power cycle the scope and retry.")
        return EXIT_FAIL
    print_serial_ports(infos)
    return EXIT_OK


def auto_connect_port(baud):
    infos = serial_port_candidates()
    if not infos:
        return None, None
    bridges = [info for info in infos if is_ch340_port(info)]
    if len(bridges) != 1:
        return None, None
    device = bridges[0].device
    return device, try_scope_link(device, baud)


def choose_serial_port(infos, prompt="Port to flash"):
    default = default_serial_port_index(infos)
    if default is None:
        answer = prompt_text("%s [1-%d]: " % (prompt, len(infos))).strip()
        if not answer:
            raise FlashError(FLASH_REFUSED, "no port selected")
    else:
        answer = prompt_text("%s [Enter = %d]: " % (prompt, default + 1)).strip()
        if not answer:
            return infos[default].device
    try:
        index = int(answer)
    except ValueError:
        raise FlashError(FLASH_REFUSED, "invalid value: %r" % answer)
    if not 1 <= index <= len(infos):
        raise FlashError(FLASH_REFUSED, "invalid value: %d" % index)
    return infos[index - 1].device


def resolve_flash_port(args):
    infos = list_serial_ports()
    if args.port:
        wanted = normalize_scope_port(args.port.strip())
        twin = serial_node_twin(wanted)
        for info in infos:
            if info.device in (wanted, twin):
                return info.device
        raise FlashError(FLASH_NO_PORT, "port not available (%s), hold power button and retry." % wanted)
    if not infos:
        raise FlashError(FLASH_NO_PORT, "port not available, hold power button and retry.")
    return choose_serial_port(infos)


class IspLink:
    def __init__(self, ser, port=None, label="image"):
        self.ser = ser
        self.port = port
        self.label = label
        self.baud = getattr(ser, "baudrate", None) or SCOPE_BOOT_BAUD
        self.ser.timeout = ISP_POLL
        self.checks_node = bool(port and port.startswith("/dev/"))
        self.retries = 0
        self.block_acked = 0
        self.total_blocks = 0
        self.transfer_running = False

    def _gone(self, action, exc=None):
        if self.total_blocks:
            where = " at block %d of %d" % (self.block_acked, self.total_blocks)
        else:
            where = " before the first block"
        cause = "" if exc is None else " (%s)" % exc
        return FlashError(FLASH_PORT_GONE,
                          "port no longer available during %s%s%s, power cycle the scope and retry"
                          % (action, where, cause))

    def _node_present(self):
        return (not self.checks_node) or os.path.exists(self.port)

    def poll_byte(self):
        try:
            data = self.ser.read(1)
        except serial_exceptions as e:
            raise self._gone("a read", e)
        return data[0] if data else None

    def read_byte(self, timeout):
        end = time.monotonic() + timeout
        while True:
            byte = self.poll_byte()
            if byte is not None:
                return byte
            if time.monotonic() >= end:
                return None
            if not self._node_present():
                raise self._gone("a read")

    def write(self, data):
        try:
            self.ser.write(bytes(data))
            self.ser.flush()
        except serial_exceptions as e:
            raise self._gone("a write", e)

    def pending(self):
        try:
            return self.ser.in_waiting
        except serial_exceptions as e:
            raise self._gone("a poll", e)

    def drain(self, idle=0.05, limit=0.3):
        end = time.monotonic() + limit
        while time.monotonic() < end:
            count = self.pending()
            if count:
                self.ser.read(count)
                continue
            time.sleep(idle)
            if not self.pending():
                return

    def retune(self, rate):
        try:
            self.ser.baudrate = rate
        except serial_exceptions as e:
            print("  %s baud is not available (%s)"
                  % (baud_label(rate), e))
            return False
        except ValueError as e:
            print("  %s baud is not available (%s)"
                  % (baud_label(rate), e))
            return False
        self.baud = rate
        try:
            self.ser.reset_input_buffer()
        except serial_exceptions as e:
            raise self._gone("a retune", e)
        return True

    def _pulse_reset_lines(self):
        upd_dtr = getattr(self.ser, "_zt_orig_update_dtr", None)
        upd_rts = getattr(self.ser, "_zt_orig_update_rts", None)
        if upd_dtr is None or upd_rts is None:
            return False
        try:
            self.ser.dtr = 0
            upd_dtr()
            self.ser.rts = 1
            upd_rts()
            time.sleep(0.01)
            self.ser.dtr = 1
            upd_dtr()
            self.ser.rts = 0
            upd_rts()
            time.sleep(0.01)
            self.ser.dtr = 0
            upd_dtr()
        except serial_exceptions:
            return False
        return True

    def _esc_burst(self, ms):
        count = max(1, int(ms / 10))
        for _ in range(count):
            self.write(bytes((ISP_ESC,)))
            time.sleep(0.01)

    def _zw_reset_round(self):
        self._pulse_reset_lines()
        self._esc_burst(20)
        self.write(b"AT+RST\r\n")
        self._esc_burst(20)
        self.write(b"reboot\r\n")
        self._esc_burst(50)

    def sync(self, budget=ISP_SYNC_TIMEOUT, storm=False,
             min_ready=ISP_SYNC_MIN, gap=0.0):
        self.drain()
        if storm:
            self.write(bytes((ISP_ESC,) * ISP_SYNC_MIN))
        deadline = time.monotonic() + budget
        next_esc = time.monotonic()
        ready = 0
        last = None
        while True:
            now = time.monotonic()
            if now >= deadline:
                break
            byte = self.poll_byte()
            if byte is None:
                if storm and now >= next_esc:
                    self.write(bytes((ISP_ESC,)))
                    next_esc = now + ISP_ESC_CADENCE
                    last = None
                    ready = 0
                continue
            if byte not in ISP_READY:
                ready = 0
                continue
            if last is not None and now - last < gap:
                continue
            last = now
            ready += 1
            storm = False
            if ready >= min_ready:
                return ready
        raise FlashError(FLASH_NO_SYNC, "no %d ready beacons at %s baud within %.0f s, power cycle the scope and retry." % (min_ready, baud_label(self.baud), budget))

    def command(self, cmd, *params):
        self.write(isp_frame(cmd, *params))
        return self.read_byte(ISP_COMMAND_WINDOW)

    def dial_in(self, target, probe_budget=ISP_SWITCH_SYNC, verbose=True):
        if target == self.baud:
            if verbose:
                print("Download rate %s baud: staying at the boot rate" % baud_label(target))
            return target
        ladder = [rate for rate in ISP_LADDER if rate <= target]
        for index, rate in enumerate(ladder):
            if not self.retune(SCOPE_BOOT_BAUD):
                raise FlashError(FLASH_NO_PORT, "scope will not go back to %s baud" % baud_label(SCOPE_BOOT_BAUD))
            if index:
                self.sync(budget=probe_budget, gap=ISP_SYNC_GAP)
            refused = None
            if rate != SCOPE_BOOT_BAUD:
                time.sleep(ISP_SWITCH_DELAY)
                answer = self.command(ISP_CMD_BAUD, rate)
                if answer == ord('S'):
                    if verbose:
                        print("  scope refused %s baud with %s, reducing" % (baud_label(rate), beacon_name(answer)))
                    continue
                if answer not in (None, ord('R')):
                    answer = None
                refused = answer
            self.retune(rate)
            time.sleep(ISP_SWITCH_DELAY)
            try:
                self.sync(budget=probe_budget, gap=ISP_SYNC_GAP)
            except FlashError as e:
                if e.code != FLASH_NO_SYNC:
                    raise
                if refused is not None:
                    raise FlashError(FLASH_FRAME_REJECTED, "scope answered with %s, did not confirm %s baud" % (beacon_name(refused), baud_label(rate)))
                if verbose:
                    print("  %s baud was not confirmed, reducing" % baud_label(rate))
                continue
            if verbose:
                print("Download rate %s baud" % baud_label(rate))
            return rate
        raise FlashError(FLASH_NO_SYNC, "no download rate from %s could be confirmed at %s, stopped." % ("/".join(baud_label(rate) for rate in ladder), self.port or ""))

    def enter_isp(self, budget=ISP_SYNC_QUICK, silent=False):
        deadline = time.monotonic() + budget
        rounds = 0
        while time.monotonic() < deadline:
            rounds += 1
            self._zw_reset_round()
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                break
            probe = min(remaining, 2.0)
            try:
                self.sync(budget=probe, storm=True)
                if not silent:
                    print("ISP ready at %s baud (round %d)." % (baud_label(self.baud), rounds))
                return
            except FlashError as e:
                if e.code != FLASH_NO_SYNC:
                    raise
                continue
        raise FlashError(FLASH_NO_SYNC, "no %d ready beacons at %s baud within %.0f s after %d reset rounds." % (ISP_SYNC_MIN, baud_label(self.baud), budget, rounds))


    def _block(self, chunk, seq):
        head = struct.pack("<BBB", XMODEM_STX, seq, 0xFF - seq) + chunk
        return head + struct.pack(">H", xmodem_crc16(chunk))

    def _progress(self, number, total):
        step = max(1, total // 20)
        if number != total and number % step:
            return
        print("  block %d/%d (%3d%%) at %s baud - keep the power button held"
              % (number, total, 100 * number // total,
                 baud_label(self.baud)))

    def _send_block(self, block, number, total):
        for attempt in range(1, XMODEM_RETRIES + 1):
            self.write(block)
            byte = self.read_byte(XMODEM_BYTE_TIMEOUT)
            if byte == XMODEM_ACK:
                self.block_acked = number
                self._progress(number, total)
                return
            if byte == XMODEM_CAN:
                raise FlashError(FLASH_TRANSFER, "scope canceled download at block %d of %d with %s" % (number, total, beacon_name(byte)))
            if byte not in (XMODEM_NAK, XMODEM_C) and byte in ISP_BEACONS:
                raise FlashError(FLASH_TRANSFER, "block %d of %d: scope answered %s" % (number, total, beacon_name(byte)))
            self.retries += 1
        raise FlashError(FLASH_TRANSFER, "block %d of %d not accepted in %d attempts, last byte %s" % (number, total, XMODEM_RETRIES, beacon_name(byte)))

    def xmodem_send(self, stream):
        chunks = [stream[offset:offset + XMODEM_BLOCK_LEN]
                  for offset in range(0, len(stream), XMODEM_BLOCK_LEN)]
        padded = [chunk + bytes((XMODEM_FILL,)) * (XMODEM_BLOCK_LEN - len(chunk))
                  if len(chunk) < XMODEM_BLOCK_LEN else chunk for chunk in chunks]
        self.total_blocks = len(padded)
        self.transfer_running = True
        seq = 1
        for index, chunk in enumerate(padded):
            self._send_block(self._block(chunk, seq), index + 1, len(padded))
            seq = (seq + 1) & 0xFF
        self._send_eot(len(padded))
        self.transfer_running = False
        return len(padded)


    def xmodem_send_with_progress(self, stream, total_blocks):
        chunks = [stream[offset:offset + XMODEM_BLOCK_LEN]
                  for offset in range(0, len(stream), XMODEM_BLOCK_LEN)]
        padded = [chunk + bytes((XMODEM_FILL,)) * (XMODEM_BLOCK_LEN - len(chunk))
                  if len(chunk) < XMODEM_BLOCK_LEN else chunk for chunk in chunks]
        self.total_blocks = len(padded)
        self.transfer_running = True
        seq = 1
        for index, chunk in enumerate(padded):
            block = self._block(chunk, seq)
            for attempt in range(1, XMODEM_RETRIES + 1):
                self.write(block)
                byte = self.read_byte(XMODEM_BYTE_TIMEOUT)
                if byte == XMODEM_ACK:
                    self.block_acked = index + 1
                    break
                if byte == XMODEM_CAN:
                    raise FlashError(FLASH_TRANSFER, "scope canceled the download at block %d of %d with %s" % (index + 1, len(padded), beacon_name(byte)))
                if byte not in (XMODEM_NAK, XMODEM_C) and byte in ISP_BEACONS:
                    raise FlashError(FLASH_TRANSFER, "block %d of %d: scope answered %s" % (index + 1, len(padded), beacon_name(byte)))
                self.retries += 1
            else:
                raise FlashError(FLASH_TRANSFER, "block %d of %d not accepted in %d attempts, last byte was %s" % (index + 1, len(padded), XMODEM_RETRIES, beacon_name(byte)))
            pct = 100 * (index + 1) // total_blocks
            bar_len = 30
            filled = bar_len * (index + 1) // total_blocks
            bar = '#' * filled + '-' * (bar_len - filled)
            sys.stdout.write("\r  [%s] %3d%%  %d/%d blocks" % (bar, pct, index + 1, total_blocks))
            sys.stdout.flush()
            seq = (seq + 1) & 0xFF
        byte = None
        for attempt in range(XMODEM_EOT_TRIES):
            self.write(bytes((XMODEM_EOT,)))
            byte = self.read_byte(XMODEM_BYTE_TIMEOUT)
            if byte == XMODEM_ACK:
                break
            if byte in ISP_BEACONS and byte not in ISP_READY:
                raise FlashError(FLASH_TRANSFER, "scope answered transfer with %s" % beacon_name(byte))
            self.retries += 1
        else:
            raise FlashError(FLASH_TRANSFER, "incomplete after %d tries (scope said %s)" % (XMODEM_EOT_TRIES, beacon_name(byte)))
        self.transfer_running = False
        print()
        return len(padded)


    def _send_eot(self, total):
        byte = None
        for attempt in range(XMODEM_EOT_TRIES):
            self.write(bytes((XMODEM_EOT,)))
            byte = self.read_byte(XMODEM_BYTE_TIMEOUT)
            if byte == XMODEM_ACK:
                return
            if byte in ISP_BEACONS and byte not in ISP_READY:
                raise FlashError(FLASH_TRANSFER, "scope answered transfer with %s" % beacon_name(byte))
            self.retries += 1
        raise FlashError(FLASH_TRANSFER, "incomplete after %d tries (scope said %s)" % (XMODEM_EOT_TRIES, beacon_name(byte)))

    def reboot(self):
        self.write(isp_frame(ISP_CMD_REBOOT))
        byte = self.read_byte(0.5)
        return byte

    def abort(self):
        if self.transfer_running:
            try:
                self.write(bytes((XMODEM_CAN,) * 2))
            except FlashError:
                return
            self.transfer_running = False
        try:
            self.drain(limit=0.3)
        except FlashError:
            pass

    def close(self):
        try:
            self.ser.close()
        except serial_exceptions:
            pass


def run_flash(args):
    records, image = flash_preflight(args.source)
    target = args.baud if args.baud is not None else ISP_DOWNLOAD_BAUD
    isp_rate_arg(target)
    print("Found image: %s (CRC verified)" % (image.name))
    port = resolve_flash_port(args)
    answer = prompt_text("Ready to flash, press Enter to continue or q to cancel: ")
    answer = answer.strip().lower()
    if answer == "q":
        raise FlashError(FLASH_REFUSED, "canceled, no data sent")
    if answer != "":
        raise FlashError(FLASH_REFUSED, "only Enter proceeds, no data sent")
    try:
        ser = open_scope_port(port, baud=SCOPE_BOOT_BAUD, timeout=ISP_POLL,
                              toggle_lines=False)
    except LinkError as e:
        raise FlashError(FLASH_NO_PORT, str(e))

    link = IspLink(ser, port=port, label=image.name)
    try:
        link.enter_isp(silent=True)
        link.dial_in(target, verbose=False)
        try:
            link.xmodem_send_with_progress(image.stream, image.blocks())
        except KeyboardInterrupt:
            link.abort()
            raise FlashError(FLASH_ABORTED, "stopped after block %d of %d, flash is partially-written and must be reflashed" % (link.block_acked, link.total_blocks))
        link.reboot()
        link._pulse_reset_lines()
        print("Flash completed successfully! Power cycle the scope to enable the USB/serial port.")
        return 0
    finally:
        link.abort()
        link.close()

# Backup flash persistent region
BACKUP_OK = 0
BACKUP_FAILED = 1
BACKUP_REFUSED = 2
BACKUP_NO_PORT = 3
BACKUP_ABORTED = 4


class BackupError(Exception):
    def __init__(self, code, message):
        super().__init__(message)
        self.code = code


def parse_persist_container(data):
    if len(data) < PERSIST_HEADER_LEN:
        raise BackupError(BACKUP_FAILED, "container is %d bytes, shorter than the %d-byte header" % (len(data), PERSIST_HEADER_LEN))
    if data[:8] != PERSIST_MAGIC:
        raise BackupError(BACKUP_FAILED, "container magic is %r, expected %r"  % (bytes(data[:8]), PERSIST_MAGIC))
    version, addr, length, fbase, fsize, crc = \
        struct.unpack_from("<IIIIII", data, 8)
    if version != PERSIST_VERSION:
        raise BackupError(BACKUP_FAILED, "container version %d, expected %d" % (version, PERSIST_VERSION))
    if addr < PERSIST_BASE or addr >= PERSIST_LIMIT or \
            length > PERSIST_LIMIT - addr:
        raise BackupError(BACKUP_FAILED, "container names 0x%08X+%d, outside the persistent " "window" % (addr, length))
    payload = bytes(data[PERSIST_HEADER_LEN:])
    if len(payload) != length:
        raise BackupError(BACKUP_FAILED, "container holds %d payload bytes, header says %d" % (len(payload), length))
    want = zlib.crc32(payload) & 0xFFFFFFFF
    if crc != want:
        raise BackupError(BACKUP_FAILED, "payload CRC32 0x%08X, recomputed 0x%08X" % (crc, want))
    return addr, payload, dict(version=version, fbase=fbase, fsize=fsize, crc=crc)


def write_persist_manifest(out_path, addr, payload, meta, stats, baud):
    stem, _ = os.path.splitext(out_path)
    manifest_path = (stem or out_path) + ".json"
    records = []
    for base, size, name in PERSIST_RECORDS:
        if base >= addr and base + size <= addr + len(payload):
            chunk = payload[base - addr:base - addr + size]
            records.append(dict(addr="0x%08X" % base, size=size, name=name, sha256=hashlib.sha256(chunk).hexdigest()))
    doc = dict(container="ZWFLSH",
               version=meta["version"],
               base="0x%08X" % addr,
               length=len(payload),
               flash_base="0x%08X" % meta["fbase"],
               flash_size=meta["fsize"],
               crc32="0x%08X" % meta["crc"],
               sha256=hashlib.sha256(payload).hexdigest(),
               baud=baud,
               transfer=stats,
               captured=datetime.now().isoformat(timespec="seconds"),
               records=records)
    with open(manifest_path, "w") as f:
        json.dump(doc, f, indent=2)
        f.write("\n")
    print("Manifest:         %s" % manifest_path)


def capture_persist(link, caps, addr, length, out_path, args):
    if args.debug:
        print("Requesting %d bytes at 0x%08X from the persistent region..." % (length, addr))
    stats = {}
    try:
        data, _ = link.persist(addr, length, caps=caps, stats=stats, debug=args.debug)
    except Exception:
        if args.debug:
            print(format_transfer_stats(stats))
        raise
    if args.debug:
        print(format_transfer_stats(stats))

    addr_in, payload, meta = parse_persist_container(data)
    if addr_in != addr or len(payload) != length:
        raise BackupError(BACKUP_FAILED, "scope answered 0x%08X+%d, asked for 0x%08X+%d" % (addr_in, len(payload), addr, length))

    with open(out_path, "wb") as f:
        f.write(data)

    if not args.debug:
        print("Saved backup:     %s (%d bytes)" % (out_path, len(data)))
        return BACKUP_OK

    erased = sum(1 for b in payload if b == 0xFF)
    print("Saved backup:     %s (%d bytes)" % (out_path, len(data)))
    print("Region:           0x%08X-0x%08X, %d bytes, %d of them erased"
          % (addr_in, addr_in + length - 1, length, erased))
    print("Payload CRC32:    0x%08X (matches the container header)" % meta["crc"])
    print("SHA-256:          %s" % hashlib.sha256(data).hexdigest())
    for base, size, name in PERSIST_RECORDS:
        if base >= addr_in and base + size <= addr_in + length:
            chunk = payload[base - addr_in:base - addr_in + size]
            print("  0x%08X  %-26s %6d B  %s" % (base, name, size, hashlib.sha256(chunk).hexdigest()[:16]))
    write_persist_manifest(out_path, addr_in, payload, meta, stats, link.baud)
    return BACKUP_OK


def backup_path():
    stamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    path = "%s_%s.bin" % (BACKUP_PREFIX, stamp)
    n = 2
    while (os.path.exists(path)
           or os.path.exists(os.path.splitext(path)[0] + ".json")):
        path = "%s_%s_%d.bin" % (BACKUP_PREFIX, stamp, n)
        n += 1
    return path


def run_backup(args):
    if args.source in ("-",) or os.path.isfile(args.source) or \
            os.path.isdir(args.source):
        raise BackupError(BACKUP_REFUSED, "specify a serial port with --backup")
    out_path = backup_path() if args.backup is BACKUP_DEFAULT else args.backup
    addr, length = PERSIST_BASE, PERSIST_LIMIT - PERSIST_BASE

    ser, link, rate, info = open_scope_link(args.source, args.baud)
    try:
        caps = info["caps"]
        if not (caps & CAP_FLASH):
            raise BackupError(BACKUP_REFUSED, "scope firmware does not support backup")
        if args.debug:
            print("Connected at %s baud." % baud_label(rate))
        else:
            print("Connected at %s baud, requesting backup..."
                  % baud_label(rate))
        return capture_persist(link, caps, addr, length, out_path, args)
    finally:
        close_quietly(ser)


def baud_arg(value):
    text = value.strip().lower()
    try:
        rate = round(float(text[:-1]) * 1_000_000) if text.endswith("m") else int(text)
    except ValueError:
        raise argparse.ArgumentTypeError(
            "invalid baud rate %r (set 115200, 1M, 1.5M, 2M, etc)" % value)
    if rate <= 0:
        raise argparse.ArgumentTypeError(
            "invalid baud rate %r (set 115200, 1M, 1.5M, 2M, etc)" % value)
    return rate


def window_arg(value):
    parts = value.split(":")
    try:
        start = int(parts[0], 0)
        count = int(parts[1], 0) if len(parts) == 2 and parts[1] else None
    except ValueError:
        raise argparse.ArgumentTypeError("window must be START or START:COUNT")
    if len(parts) > 2 or start < 0 or (count is not None and count <= 0):
        raise argparse.ArgumentTypeError("window must be START or START:COUNT")
    return start, count


def main():
    parser = argparse.ArgumentParser(description="Waveform/Screenshot Capture + Flashing for Zeeweii scopes")
    parser.add_argument("source", nargs="?", help="Serial port, saved waveform .bin file/directory, .fls firmware to flash")
    parser.add_argument("--port", nargs="?", const=PORT_LIST, default=None, metavar="PORT", help="Scope serial port, leave blank to list valid ports")
    parser.add_argument("--baud", type=baud_arg, default=None, help="Serial port baud rate 115200-2M (default 1M)")
    parser.add_argument("--output", default=DEFAULT_OUTPUT, help="Output filename prefix")
    parser.add_argument("--sidecar", action="store_true", help="Write .txt/.csv data files")
    parser.add_argument("--width", type=int, default=1650, help="Output image width in pixels (default 1650)")
    parser.add_argument("--title", type=str, default=None, help="Display custom title")
    parser.add_argument("--datetime", action="store_true", help="Append current datetime to title")
    parser.add_argument("--meas", type=str, default=None, help="Display custom measurements (original: --meas, custom: --meas=\"freq,amp\", etc)")
    parser.add_argument("--window", type=window_arg, default=None, metavar="START:COUNT", help="Set custom waveform capture window for faster timebases")
    parser.add_argument("--trigline", action="store_true", help="Draw dashed line at trigger level")
    parser.add_argument("--nocurs", action="store_true", help="Disable drawing cursors and measurements")
    parser.add_argument("--color1", default=None, help="Override channel 1 color")
    parser.add_argument("--color2", default=None, help="Override channel 2 color")
    parser.add_argument("--waveform", action="store_true", help="Convert an image to a signal generator waveform")
    parser.add_argument("--scale", action="store_true", help="Scale signal generator waveform to full dynamic range (0-255)")
    parser.add_argument("--backup", nargs="?", const=BACKUP_DEFAULT, default=None, metavar="FILE", help="Backup flash persistent region")
    parser.add_argument("--dso2512g_v1", action="store_true", help="DSO2512G v1.x firmware")
    parser.add_argument("--dso2512g_v2", action="store_true", help="DSO2512G v2.x firmware")
    parser.add_argument("--debug", action="store_true", help="Display debug output")
    args = parser.parse_args()

    preset = None
    if len(sys.argv) == 1:
        held = io.StringIO()
        with contextlib.redirect_stdout(held):
            device, found = auto_connect_port(DEFAULT_BAUD)
        if found is None:
            parser.print_help()
            sys.exit(EXIT_OK)
        sys.stdout.write(held.getvalue())
        args.source = device
        preset = found
    elif args.port is not PORT_LIST and args.source is None:
        if args.waveform:
            parser.error("specify an image with --waveform")
        args.source = args.port
        args.port = None
    elif args.port is PORT_LIST:
        if args.source is not None and is_flash_container(args.source):
            parser.error("specify a port with --port for firmware")
        if args.source is not None or args.backup is not None:
            sys.exit(show_serial_ports())
        device, found = auto_connect_port(args.baud or DEFAULT_BAUD)
        if found is None:
            if device is not None:
                print("No answer from the scope on %s." % device)
            show_serial_ports()
            sys.exit(EXIT_FAIL)
        args.source = device
        preset = found
        args.port = None

    global data_config
    if args.dso2512g_v1: data_config = CONFIG_DSO2512G_V1
    elif args.dso2512g_v2: data_config = CONFIG_DSO2512G_V2
    else: data_config = CONFIG_DSO3D12

    if args.baud is None:
        args.baud = (ISP_DOWNLOAD_BAUD
                     if is_flash_container(args.source) else DEFAULT_BAUD)


    if args.source is None:
        offer_ports = args.backup is not None and args.port is None
        if offer_ports:
            infos = serial_port_candidates()
            if infos and any(is_ch340_port(info) for info in infos):
                if not sys.stdin.isatty():
                    print("source is required without a terminal")
                    sys.exit(2)
                print_serial_ports(infos)
                try:
                    args.source = choose_serial_port(infos, "Port to use")
                except FlashError as e:
                    print("Serial port failed: %s" % e)
                    sys.exit(e.code)
        if args.source is None:
            parser.error("source is required")

    if is_flash_container(args.source):
        for name, asked in (("--waveform", args.waveform),):
            if asked:
                parser.error("%s does not apply with firmware"
                             % name)
        try:
            code = run_flash(args)
        except FlashError as e:
            print("Flash failed: %s" % e)
            code = e.code
        except KeyboardInterrupt:
            print("\nFlash interrupted, transfer unfinished")
            code = FLASH_ABORTED
        sys.exit(code)
    elif args.port:
        parser.error("--port applies with firmware")

    if args.backup is not None:
        for name, asked in (("--waveform", args.waveform),
                            ("--scale", args.scale),
                            ("--window", args.window is not None)):
            if asked:
                parser.error("%s does not apply to --backup" % name)
        try:
            code = run_backup(args)
        except BackupError as e:
            print("Backup failed: %s" % e)
            code = e.code
        except KeyboardInterrupt:
            print("\nBackup interrupted, transfer incomplete.")
            code = BACKUP_ABORTED
        sys.exit(code)

    elif args.waveform:
        ok = generate_waveform(args.source, scale=args.scale, output_filename=args.output)
        sys.exit(EXIT_OK if ok else EXIT_FAIL)

    elif os.path.isdir(args.source):
        print(f"Scanning directory: {args.source}")
        failures = 0
        try:
            for fname in os.listdir(args.source):
                if fname.lower().endswith(".bin"):
                    full_path = os.path.join(args.source, fname)
                    try:
                        size = os.path.getsize(full_path)
                        with open(full_path, 'rb') as f: buffer = f.read()
                        base_name = os.path.splitext(os.path.basename(fname))[0]
                        if buffer[:8] == FPGA_CAPTURE_MAGIC:
                            print(f"\nProcessing:       {fname}")
                            if args.output != DEFAULT_OUTPUT:
                                base_name = f"{args.output}_{base_name}"
                            if args.datetime: base_name += f"_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
                            if not fpga_capture_process_buffer(buffer, base_name, args):
                                failures += 1
                        elif buffer[:8] == LCD_SCREENSHOT_MAGIC:
                            print(f"\nProcessing:       {fname}")
                            if args.output != DEFAULT_OUTPUT:
                                base_name = f"{args.output}_{base_name}"
                            if args.datetime: base_name += f"_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
                            lcd_process_screenshot_buffer(buffer, base_name)
                        elif size == 2048:
                            print(f"\nProcessing:       {fname}")
                            if args.output == DEFAULT_OUTPUT: filename = base_name
                            else: filename = f"{args.output}_{base_name}"
                            if args.datetime: filename += f"_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
                            process_capture(buffer, filename, args)
                    except KeyboardInterrupt: raise
                    except Exception as e:
                        print(f"Error processing {fname}: {e}")
                        failures += 1
        except KeyboardInterrupt:
            print("Cancelling...")
        print("Done.")
        sys.exit(EXIT_FAIL if failures else EXIT_OK)

    # File
    elif os.path.isfile(args.source):
        print(f"Processing:       {args.source}")
        try:
            size = os.path.getsize(args.source)
            with open(args.source, 'rb') as f: buffer = f.read()
            base_name = os.path.splitext(os.path.basename(args.source))[0]
            if args.output != DEFAULT_OUTPUT: base_name = args.output
            if args.datetime: base_name += f"_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
            if buffer[:8] == FPGA_CAPTURE_MAGIC:
                sys.exit(EXIT_OK if fpga_capture_process_buffer(buffer, base_name, args)
                         else EXIT_FAIL)
            if buffer[:8] == LCD_SCREENSHOT_MAGIC:
                lcd_process_screenshot_buffer(buffer, base_name)
                sys.exit(EXIT_OK)
            if not (2034 <= size <= 2048):
                print(f"Error: Invalid file size ({size} bytes, expected 2048).")
                sys.exit(EXIT_FAIL)
            if args.output == DEFAULT_OUTPUT: filename = os.path.splitext(os.path.basename(args.source))[0]
            else: filename = args.output
            if args.datetime: filename += f"_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
            process_capture(buffer, filename, args)
            sys.exit(EXIT_OK)
        except Exception as e:
            print(f"File Error: {e}")
            sys.exit(EXIT_FAIL)

    # Serial
    if not looks_like_serial_port(args.source):
        print(f"Error: {args.source} is not an existing file, directory, or serial port.")
        sys.exit(EXIT_FAIL)
    try: import msvcrt
    except ImportError: msvcrt = None
    try: import tty
    except ImportError: tty = None

    stdin_fd = None
    stdin_saved = None
    single_key = False
    if msvcrt is None and termios is not None and tty is not None:
        try:
            fd = sys.stdin.fileno()
            if os.isatty(fd):
                stdin_fd = fd
                stdin_saved = termios.tcgetattr(fd)
                tty.setcbreak(fd)
                single_key = True
        except (OSError, ValueError):
            stdin_fd = None
            single_key = False
    try:
        stdin_enabled = True
        status_width = 0

        def redraw_status(text):
            nonlocal status_width
            pad = ' ' * max(0, status_width - len(text))
            print(f"\r{text}{pad}", end='', flush=True)
            status_width = max(status_width, len(text))

        def clear_status():
            nonlocal status_width
            if status_width:
                print(f"\r{' ' * status_width}\r", end='', flush=True)
                status_width = 0

        while True:
            ser = None
            link = None
            active_baud = None
            if preset is not None:
                ser, link, active_baud = preset
                preset = None
                clear_status()
            while ser is None:
                try:
                    ser = open_scope_port(args.source,
                                          toggle_lines=False)
                except (serial_exceptions + (LinkError,)):
                    if ser:
                        try: ser.close()
                        except Exception: pass
                    ser = None
                    redraw_status(f"Waiting for {args.source}... (Ctrl+C to cancel)")
                    time.sleep(1.0)
                except KeyboardInterrupt: raise
            while link is None:
                clear_status()
                try:
                    link, active_baud, _ = open_link(ser, args.baud)
                    break
                except serial_exceptions:
                    if ser:
                        try: ser.close()
                        except Exception: pass
                    ser = None
                    redraw_status(f"Waiting for {args.source}... (Ctrl+C to cancel)")
                    time.sleep(1.0)
                    break
                except (LinkError, FrameTimeout, ScopeError) as e:
                    redraw_status(f"{e}; retrying handshake... (Ctrl+C to cancel)")
                    time.sleep(1.0)
                except KeyboardInterrupt: raise
            if ser is None:
                continue
            baud_text = baud_label(active_baud)
            print(f"\nZeeweii DSO3D12 connected. ({baud_text} baud)")
            print("Press 'c' to capture the live waveform, 'l' for an LCD screenshot, or open a saved screenshot to download ('q' to quit):")
            lcd_screenshot_pending = False
            fpga_capture_pending = False
            push_buf = bytearray()
            push_last_rx = time.monotonic()
            push_notified = False
            try:
                while True:
                    if stdin_enabled:
                        if msvcrt is not None:
                            while msvcrt.kbhit():
                                key = msvcrt.getwch()
                                if key == "\x03":
                                    raise KeyboardInterrupt
                                elif key.lower() == "c":
                                    fpga_capture_pending = True
                                elif key.lower() == "l":
                                    lcd_screenshot_pending = True
                                elif key.lower() == "q":
                                    raise KeyboardInterrupt
                                else:
                                    print("Press 'c' to capture the live waveform, 'l' for an LCD screenshot, or open a saved screenshot to download ('q' to quit):")
                        else:
                            try:
                                ready, _, _ = select.select([sys.stdin], [], [], 0)
                            except (OSError, ValueError):
                                ready = []
                                stdin_enabled = False
                            if ready:
                                if single_key:
                                    line = os.read(stdin_fd, 1).decode("utf-8", "ignore")
                                else:
                                    line = sys.stdin.readline()
                                cmd = line.strip().lower()
                                if line == "\x03":
                                    raise KeyboardInterrupt
                                if line == "":
                                    stdin_enabled = False
                                elif cmd in ("q", "quit", "exit"):
                                    raise KeyboardInterrupt
                                elif cmd in ("c", "capture", "waveform"):
                                    fpga_capture_pending = True
                                elif cmd in ("l", "lcd", "screenshot"):
                                    lcd_screenshot_pending = True
                                else:
                                    print("Press 'c' to capture the live waveform, 'l' for an LCD screenshot, or open a saved screenshot to download ('q' to quit):")
                    if ser.in_waiting:
                        chunk = ser.read(ser.in_waiting)
                        if chunk:
                            push_buf.extend(chunk)
                            push_last_rx = time.monotonic()
                            if not push_notified and len(push_buf) > 2064:
                                print("\nReceiving scope data...", end='', flush=True)
                                push_notified = True
                            if len(push_buf) > PUSH_BUF_LIMIT:
                                push_buf.clear()
                                push_notified = False
                                push_last_rx = time.monotonic()
                    elif push_buf and time.monotonic() - push_last_rx > PUSH_IDLE:
                        push = bytes(push_buf)
                        push_buf.clear()
                        push_notified = False
                        if push.startswith(FRAME_SYNC):
                            pass
                        else:
                            try:
                                process_push(push, args)
                            except serial_exceptions:
                                raise
                            except Exception as e:
                                print(f"Push data error: {e}")
                    line_idle = (not push_buf and not ser.in_waiting and time.monotonic() - push_last_rx >= PUSH_IDLE)
                    if lcd_screenshot_pending and line_idle:
                        lcd_screenshot_pending = False
                        try: lcd_capture_screenshot(link, output_prefix(args, LCD_SCREENSHOT_PREFIX), args.debug)
                        except serial_exceptions: raise
                        except (LinkError, FrameTimeout, ScopeError, LcdScreenshotError) as e:
                            print(f"Screenshot failed: {e}")
                        except Exception as e:
                            print(f"Screenshot failed: {e}")
                    if fpga_capture_pending and line_idle:
                        fpga_capture_pending = False
                        prefix = output_prefix(args, FPGA_CAPTURE_PREFIX)
                        try: fpga_capture_request(link, prefix, args)
                        except serial_exceptions: raise
                        except (LinkError, FrameTimeout, ScopeError, FpgaCaptureError) as e:
                            print(f"Waveform capture failed: {e}")
                        except Exception as e:
                            print(f"Waveform capture failed: {e}")
                    time.sleep(0.002)
            except serial_exceptions:
                print("\nConnection lost, reconnecting...")
                try: ser.close()
                except Exception: pass
    except KeyboardInterrupt: print("\nExiting...")
    finally:
        if stdin_saved is not None:
            try: termios.tcsetattr(stdin_fd, termios.TCSADRAIN, stdin_saved)
            except Exception: pass
        if 'ser' in locals() and ser and ser.is_open:
            ser.close()

if __name__ == "__main__":
    main()
