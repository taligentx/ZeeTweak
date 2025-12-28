#!/usr/bin/env python3

'''
ZeeTweak 4.1 - Transfer and process data for Zeeweii oscilloscopes.

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
import time
import struct
import argparse
import numpy as np
from PIL import Image
from datetime import datetime
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.patheffects as pe
from matplotlib.offsetbox import TextArea, HPacker, AnnotationBbox
import re
import csv
import os
import sys

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
    1228: ("Horiz Trigger Delay (ps)", 8, True),
    1236: ("View Scroll Offset (ps)?", 8, True),
    1244: ("Buffer Trigger Index?", 4, False),      # Position in buffer (0-60000)
    1248: ("Hardware Trigger Delay?", 4, False),
    1252: ("Sample Rate (HW)", 4, False),           # Hardware sample rate Hz/100
    1256: ("Trigger Source", 1, False),             # 0=Ch1, 1=Ch2
    1257: ("Trigger Mode", 1, False),               # 0=Auto, 1=Normal
    1258: ("Trigger Edge", 1, False),               # 0=Rise, 1=Fall
    1259: ("Trigger Level Mode", 1, False),         # 0=Auto, 1=Manual
    1260: ("Buffer Write Pointer?", 4, False),      # Dynamic per waveform
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
    1400: ("Pre-Trigger Samples?", 4, False),       # Combines with Post-Trigger = 60000
    1404: ("Post-Trigger Samples?", 4, False),    
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
    1520: ("Horiz Ref Mode?", 1, False),            # 0=Center?, 1=Trig lock?
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


def parse_debug(buf, f):
    start_offset = data_config['settings_offset']
    byte_count = data_config['settings_length']
    end_offset = start_offset + byte_count
    header = f"{'Address':<10} | {'File':<4} | {'Label':<32} | {'Hex':<18} | {'Decimal'}"
    f.write("\nDebug:\n")
    f.write(header + "\n")
    f.write("-" * len(header))
    f.write("---------------\n")
    curr = start_offset
    data_map = data_config['map']
    while curr < end_offset:
        hw_addr = data_config['settings_address'] + (curr - start_offset)
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
    print(f"Saved CSV:   {csv_filename}")

def process_capture(buf, filename, args):
    state = {}
    for offset, (label, size,is_signed) in data_config['map'].items(): state[label] = get_val(buf, offset, size, signed=is_signed)
    title_text = None
    if args.title:
        title_text = args.title
        if args.datetime: title_text += f" {datetime.now():%Y-%m-%d %H:%M:%S}"

    # CSV
    save_csv(buf, filename, state)

    # Text
    with open(f"{filename}.txt", 'w') as f:
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
        f.write(f"Channel 2:      ")
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

        # System
        sr_val = state.get("Sample Rate (Meas)", 0)
        if data_config['name']=="DSO2512G": sr_val = sr_val * 10
        if sr_val == 0: sr_val = state.get("Sample Rate (HW)") * 100
        sr_str = format_sample_rate(sr_val)
        f.write(f"Sample Rate:    {sr_str}\n")
        f.write(f"Signal Gen:     ")
        if state["SigGen Enable"]:
            wave = SIGGEN_PATTERNS.get(state.get("SigGen Waveform", 0), "Unknown")
            freq = state["SigGen Frequency"] / 10.0
            duty = state["SigGen Duty Cycle"] / 10.0
            if data_config['map']!=DATA_DSO2512G_V1:
                amp_mv = state.get("SigGen Amplitude (mV)", 0)
                amp_str = " | " + parse_siggen_mode(amp_mv)
            else: amp_str = ""
            f.write(f"{wave} | {format_freq(freq)} | {duty}%{amp_str}\n")
        else: f.write(f"Off\n")

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
            if volt_scale_uv > 0: uv_pixel = volt_scale_uv / 25.0
            zero_offset = state.get(f"{ch_prefix} Zero Volt (pixels)", 0)
            y1_offset = y1 - zero_offset
            y2_offset = y2 - zero_offset
            dy = abs(y1 - y2)
            y1_uv = y1_offset * uv_pixel
            y2_uv = y2_offset * uv_pixel
            dy_uv = dy * uv_pixel
            y1_str = format_voltage_val(y1_uv, probe_mode)
            y2_str = format_voltage_val(y2_uv, probe_mode)
            dy_str = format_voltage_val(dy_uv, probe_mode)
            if state["CH2 Enabled"]: ch_str = " | " + ch_prefix
            else: ch_str = ""
            f.write(f"Curs Y:         Y1 {y1_str} | Y2 {y2_str} | dY {dy_str}{ch_str}\n")

        # Measurements
        f.write("\nCH1 Measurements:\n")
        meas_c1 = parse_all_measurements(buf, data_config['meas_ch1_offset'], state.get("CH1 Probe Mode", 0))
        for label, val in meas_c1: f.write(f"  {label:<6}: {val}\n")
        if state["CH2 Enabled"]:
            f.write("\nCH2 Measurements:\n")
            meas_c2 = parse_all_measurements(buf, data_config['meas_ch2_offset'], state.get("CH2 Probe Mode", 0))
            for label, val in meas_c2: f.write(f"  {label:<6}: {val}\n")

        # Debug
        if args.debug: parse_debug(buf, f)

    print(f"Saved text:  {filename}.txt")

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
    sr_val = state.get("Sample Rate (Meas)", 0)
    if data_config['name']=="DSO2512G": sr_val = sr_val * 10
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
    meas_c1_list = parse_active_measurements_list(buf, data_config['meas_ch1_offset'], data_config['meas_flag_offset_ch1'], state.get("CH1 Probe Mode", 0), forced_bits)
    if meas_c1_list: draw_measurement_column(ax_right, col1_x, top_y, ch_number=1, color=ch1_color, meas_list=meas_c1_list, enabled=1)
    meas_c2_list = parse_active_measurements_list(buf, data_config['meas_ch2_offset'], data_config['meas_flag_offset_ch2'], state.get("CH2 Probe Mode", 0), forced_bits)
    if meas_c2_list: draw_measurement_column(ax_right, col2_x, top_y, ch_number=2, color=ch2_color, meas_list=meas_c2_list, enabled=state["CH2 Enabled"])
    
    # Waveforms
    x_axis = np.arange(300)
    raw_ch1 = np.frombuffer(buf[0:600], dtype=np.uint8)
    c1_min = 255 - raw_ch1[0:300]
    c1_max = 255 - raw_ch1[300:600]
    ax_grid.fill_between(x_axis, c1_min, c1_max, color=ch1_color, alpha=0.5, label="CH1", zorder=5, clip_on=True)
    ax_grid.plot(x_axis, c1_min, color=ch1_color, lw=0.5, zorder=5, clip_on=True)
    ax_grid.plot(x_axis, c1_max, color=ch1_color, lw=0.5, zorder=5, clip_on=True)
    if state["Active Channel"] == 1: c2_z = 6
    else: c2_z = 4
    if state["CH2 Enabled"] and len(buf) >= 1200:
        raw_ch2 = np.frombuffer(buf[600:1200], dtype=np.uint8)
        c2_min = 255 - raw_ch2[0:300]
        c2_max = 255 - raw_ch2[300:600]
        ax_grid.fill_between(x_axis, c2_min, c2_max, color=ch2_color, alpha=0.5, label="CH2", zorder=c2_z, clip_on=True)
        ax_grid.plot(x_axis, c2_min, color=ch2_color, lw=0.5, zorder=c2_z, clip_on=True)
        ax_grid.plot(x_axis, c2_max, color=ch2_color, lw=0.5, zorder=c2_z, clip_on=True)

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
    tb_offset_ps = state.get("Horiz Trigger Delay (ps)", 0)
    tb_val_ns = state.get("Timebase Value (ns/div)", 1)
    tb_marker = 11
    tb_y = plot_top + 3
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
    colors = ["white", "#808080"]
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
    print(f"Saved image: {filename}.png")


def generate_waveform(image_path, scale=False, output_filename="waveform_pattern_mod.bin"):
    try:
        img = Image.open(image_path).convert('L')
    except Exception as e:
        print(f"Error opening image: {e}")
        return
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
        else: _y = height / 2.0
        val = 255.0 - avg_y
        val = max(0, min(255, val))
        waveform.append(val)
    if scale:
        min_val = min(waveform)
        max_val = max(waveform)
        range_val = max_val - min_val
        if range_val > 0:
            scale = 255.0 / range_val
            print(f"Scaling dynamic range: {scale:.2f}x")
            waveform = [(v - min_val) * scale for v in waveform]
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
    if output_filename == "Zeeweii_Screenshot": 
        final_output = "waveform_pattern_mod.bin"
    else:
        final_output = output_filename
        if not final_output.lower().endswith(".bin"): final_output += ".bin"
    try:
        with open(final_output, "wb") as f: f.write(bytearray(payload))
        print(f"Saved: {final_output}")
    except IOError as e: print(f"Error writing file: {e}")


def main():
    parser = argparse.ArgumentParser(description="Zeeweii Screenshot Capture")
    parser.add_argument("source", help="Serial port, .bin file, or directory containing .bin files")
    parser.add_argument("-o", "--output", default="Zeeweii_Screenshot", help="Output filename")
    parser.add_argument("--color1", default=None, help="Override channel 1 color")
    parser.add_argument("--color2", default=None, help="Override channel 2 color")
    parser.add_argument("--meas", type=str, default=None, help="Display custom measurements (--meas=\"all\", \"freq,amp\", etc)")
    parser.add_argument("--trigline", action="store_true", help="Draw dashed line at trigger level")
    parser.add_argument("--nocurs", action="store_true", help="Disable drawing cursors and measurements")
    parser.add_argument("--title", type=str, default=None, help="Display custom title")
    parser.add_argument("--datetime", action="store_true", help="Append current datetime to title")
    parser.add_argument("-w", "--width", type=int, default=1650, help="Output image width in pixels")
    parser.add_argument("--debug", action="store_true", help="Display raw state/settings data with diff in serial mode")
    parser.add_argument("--waveform", action="store_true", help="Convert an image to waveform data")
    parser.add_argument("--scale", action="store_true", help="Scale waveform to full dynamic range (0-255)")
    parser.add_argument("--dso2512g_v1", action="store_true", help="DSO2512G v1.x firmware")
    parser.add_argument("--dso2512g_v2", action="store_true", help="DSO2512G v2.x firmware")
    args = parser.parse_args()

    global data_config
    if args.dso2512g_v1: data_config = CONFIG_DSO2512G_V1
    elif args.dso2512g_v2: data_config = CONFIG_DSO2512G_V2
    else: data_config = CONFIG_DSO3D12

    # Directory
    if args.waveform:
        if not os.path.isfile(args.source):
            print(f"Error: Source image '{args.source}' not found.")
            return
        generate_waveform(args.source, scale=args.scale, output_filename=args.output)
        return

    elif os.path.isdir(args.source):
        print(f"Scanning directory: {args.source}")
        try:
            for fname in os.listdir(args.source):
                if fname.lower().endswith(".bin"):
                    full_path = os.path.join(args.source, fname)
                    try:
                        size = os.path.getsize(full_path)
                        if size == 2048:
                            print(f"\nProcessing: {fname}")
                            with open(full_path, 'rb') as f: buffer = f.read()
                            base_name = os.path.splitext(os.path.basename(fname))[0]
                            if args.output == "Zeeweii_Screenshot": filename = base_name
                            else: filename = f"{args.output}_{base_name}"
                            if args.datetime: filename += f"_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
                            process_capture(buffer, filename, args)
                    except KeyboardInterrupt: raise
                    except Exception as e: print(f"Error processing {fname}: {e}")
        except KeyboardInterrupt:
            print("Cancelling...")
        print("Done.")
        return

    # File
    elif os.path.isfile(args.source):
        print(f"Processing: {args.source}")
        try:
            size = os.path.getsize(args.source)
            if not (2034 <= size <= 2048):
                print(f"Error: Invalid file size ({size} bytes, expected 2048).")
                return
            with open(args.source, 'rb') as f: buffer = f.read()
            if args.output == "Zeeweii_Screenshot": filename = os.path.splitext(os.path.basename(args.source))[0]
            else: filename = args.output
            if args.datetime: filename += f"_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
            process_capture(buffer, filename, args)
            return
        except Exception as e:
            print(f"File Error: {e}")
            return

    # Serial
    try: import termios
    except ImportError: termios = None
    serial_exceptions = (OSError, serial.SerialException)
    if termios: serial_exceptions += (termios.error,)
    try:
        while True:
            ser = None
            while ser is None:
                try:
                    ser = serial.Serial(None, 115200, timeout=10)
                    ser.port = args.source
                    ser.dsrdtr = True
                    ser.dtr = False
                    ser.rts = False
                    ser.open()
                    print(f"\r{' ' * 60}\rConnected, open saved waveforms to trigger capture:")
                except serial_exceptions:
                    if ser:
                        try: ser.close()
                        except: pass
                    ser = None
                    print(f"Waiting for {args.source}... (Ctrl+C to cancel)", end='\r', flush=True)
                    time.sleep(1.0)
                except KeyboardInterrupt: raise
            buffer = bytearray()
            last_rx_time = time.time()
            PACKET_TIMEOUT = 0.2
            is_receiving = False
            try:
                while True:
                    if ser.in_waiting:
                        if not is_receiving and len(buffer) > 2064:
                            print("\nReceiving data...", end='', flush=True)
                            is_receiving = True
                        chunk = ser.read(ser.in_waiting)
                        buffer.extend(chunk)
                        last_rx_time = time.time()
                    else:
                        if len(buffer) > 0 and (time.time() - last_rx_time > PACKET_TIMEOUT):
                            is_receiving = False
                            if len(buffer) >= 800 and b'--CH1--' in buffer:
                                ts = datetime.now().strftime("%Y%m%d_%H%M%S")
                                base_name = f"Zeeweii_Buffer_{ts}"
                                fname = f"{base_name}.bin"
                                with open(fname, 'wb') as f: f.write(buffer)
                                print(f"\nSaved buffer dump: {fname} ({len(buffer)} bytes)")
                                try:
                                    text_data = buffer.replace(b'\x00', b'').decode('utf-8', errors='ignore')
                                    parts = text_data.split('--------CH1--------')
                                    if len(parts) > 1:
                                        content = parts[1]
                                        ch1_str = content
                                        ch2_str = ""
                                        if '--------CH2--------' in content:
                                            split_c2 = content.split('--------CH2--------')
                                            ch1_str = split_c2[0]
                                            if len(split_c2) > 1: ch2_str = split_c2[1]
                                        def extract_samples(txt, suffix):
                                            tokens = re.findall(r'\b\d+\b', txt)
                                            if tokens:
                                                data = bytes([int(t) & 0xFF for t in tokens])
                                                out_name = f"{base_name}-{suffix}.bin"
                                                with open(out_name, 'wb') as f: f.write(data)
                                                print(f"Extracted {suffix.upper()}: {out_name} ({len(data)} samples)")
                                        extract_samples(ch1_str, "ch1")
                                        if ch2_str:
                                            extract_samples(ch2_str, "ch2")
                                except Exception as e:
                                    print(f"Error parsing dump: {e}")
                            elif 2040 <= len(buffer) <= 2056:
                                filename = f"{args.output}_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
                                with open(f"{filename}.bin", 'wb') as f:
                                    f.write(buffer)
                                    print(f"\nSaved data:  {filename}.bin")
                                process_capture(buffer, filename, args)
                                if args.debug: debug_diff(buffer)
                            elif len(buffer) < 800:
                                try:
                                    text = buffer.decode('utf-8', errors='ignore').strip()
                                    if text: print(f"{text}")
                                except: pass
                            else: print(f"Invalid data size: {len(buffer)} bytes")
                            buffer = bytearray()
                    time.sleep(0.01)
            except serial_exceptions as e:
                print(f"\nConnection lost, reconnecting...")
                try: ser.close()
                except: pass      
    except KeyboardInterrupt: print("\nExiting...")
    finally:
        if 'ser' in locals() and ser and ser.is_open:
            ser.close()

if __name__ == "__main__":
    main()
