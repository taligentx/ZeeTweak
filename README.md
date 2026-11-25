# ZeeTweak
ZeeTweak is modified firmware and companion `zeetweak.py` tool for the [Zeeweii DSO3D12 oscilloscope](http://www.zeeweii.com/productinfo/dso3d12.html):
  * **Waveform capture and download over USB**:
    * Live waveforms: capture current running waveforms directly from the FPGA to render new, high resolution screenshots (up to 60k samples, single keypress on-demand).
    * Saved waveforms: capture screenshot data saved on the scope to render new screenshots (up to 600 samples).
    * Optional txt/csv sidecar files: export data for use with applications like [sigrok PulseView](https://sigrok.org/wiki/PulseView).
  * **Live LCD screenshots**: capture the current 320x240 LCD display (all modes scope/DMM/signal generator).
  * **New DMM serial protocol**: interface natively with apps that support FS9922-based multimeters:
    * Software: [QtDMM](https://github.com/qtdmm/QtDMM), [UltraDMM](https://www.ultradmm.com), [Test Controller](https://lygte-info.dk/project/TestControllerIntro%20UK.html), etc.
    * Compatible models: UNI-T UT61B/C/D, PeakTech 2025, Voltcraft VC-830/850, more.
  * **Arbitrary waveforms**: Add new waveforms to the signal generator.
  * **UI**: New fonts, images, home screen with multiple background options, fixes for UI quirks.
  * **Targeted firmware flashing**: preserves the scope bootloader and only flashes the application for safe recovery.
  * **Buildable and extendable source**: enables adding custom code or replacing existing code.

![Zeeweii_DSO3D12_mod_v3.1](https://github.com/user-attachments/assets/88fa9dd7-0761-489b-bc0e-031cb9fce3c7)

**Waveform capture and screenshot render:**
![ZeeTweak_FPGA_Screenshot_Capture](https://github.com/user-attachments/assets/cae962c3-fe1a-4e35-b327-cf24baae9b16)

**Waveform capture vs saved screenshots:**

FPGA-captured waveforms contain all original signal data and are processed to render a median trace, precise min/max envelope, and density grading.
  * Saved screenshots (decimated 600 samples) vs live FPGA waveforms (up to 60k samples):
![FPGA-Comparison](https://github.com/user-attachments/assets/07b1b016-aecb-40b6-bcbc-5c91d08a8583)

**DMM interface with [QtDMM](https://github.com/qtdmm/QtDMM):**
![QtDMM](https://github.com/user-attachments/assets/3a01312e-11eb-44e2-82f9-4d95f41ae651)

## Quick Start
  1. Download the latest release from [Releases](https://github.com/taligentx/ZeeTweak/releases).
  2. Install the following [Python](https://www.python.org/downloads/latest/python3.14/) packages:
      - macOS/Linux: `pip3 install pyserial numpy matplotlib`
      - Windows: `py -m pip install pyserial numpy matplotlib`
  3. Flash the firmware (see Flashing below for details): `python3 zeetweak.py ZeeTweak_v5.0.fls`
  4. Run `python3 zeetweak.py` to automatically connect to the scope.
  5. Done!
     ```
     Zeeweii DSO3D12 connected (1M baud)
     Press 'c' to capture the live waveform, 'l' for an LCD screenshot,
     or open a saved screenshot to download ('q' to quit):
     ```

## Notes
- This supports the `-III` generation DSO3D12 scopes and is based on version 3.0.7-III firmware.
- Fully reversible by flashing the stock 3.0.7-III firmware.
- Feel free to post an [Issue](https://github.com/taligentx/ZeeTweak/issues) or (especially) a [Pull Request](https://github.com/taligentx/ZeeTweak/pulls). Discussion and contributions are welcome!
  - Also see the [EEVBlog forum thread](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/) for extensive discussion.

## Release Notes
- 5.0
  - `zeetweak.py`:
    - New: Live waveform capture from FPGA
    - New: Live LCD screenshots
    - New: Built-in firmware flashing support
    - New: Backup flash persistent data (scope UUID, settings, screenshots, etc)
  - Firmware:
    - New: Custom serial protocol for scope/host interface and data transfer
    - New: Adjustable baud rate, default 1M baud
    - New: 5x faster FPGA waveform capture with metadata (~650ms @ 1Mbaud)
    - New: LCD framebuffer capture for live screenshots
    - New: DMM fullscreen mode sends data as FS9922 with auto-switch to 2400 baud
    - New: Signal generator in scope window mode supports up to 10MHz sine (previously 5MHz)
    - New: DMM can be enabled in scope window mode while USB is connected
    - New: Persistent flash data backup
    - Fixed: CH2 50% auto-set level changing in stopped mode
  - Reverse engineering:
    - New: buildable and extendable source - see [source/README.md](source/README.md)
    - Updated: Ghidra project 0.5
- 4.1
  - `zeetweak.py`:
    - New: Cursors measurements for rendered screenshots
    - New: Generate waveform CSV files for other applications
    - New: Support for DSO2512G screenshot data files (requires [modified firmware](https://www.eevblog.com/forum/testgear/new-2ch-pocket-dsosg-sigpeak-dso2512g/))
    - Fixed: Windows serial port handling
    - Fixed: Voltage calculations for probes x1/x100 modes
  - Firmware:
    - New: CH2 50% auto-set level to 0 (originally offset by a few pixels)
  - Reverse engineering:
    - Updated: Ghidra project 0.3 - all functions are now identified
- 4.0
  - New: `zeetweak.py`
      - Screenshot data capture and rendering to new images with matplotlib
      - Arbitrary signal generator waveforms
      - Buffer dump capture (via secret debug mode)
  - Firmware:
    - New: Screenshot counter UI repositioned, no longer obscures waveforms or cursor measurements
    - Updated: Home screen icons
- 3.2
  - New: Zeeweii firmware 3.0.7
  - New: image for the new DMM side menu (press Menu in full-screen DMM mode)
  - New: images for the new channel math menu (long-press Menu in scope mode)
  - Updated: images for the DMM mode selection menu
  - Updated: flashing with wm-tools
- 3.1
  - New: `zrle2bmp.py` tool to convert Zeeweii-custom RLE compressed images
  - New: images from [@Dmitur](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/msg5789049/#msg5789049): sig. gen. numbers, trigger edge icon
  - New: images for channel level icon, trigger icon
  - Updated: measurement label background
  - Updated: menu display setting for persistence relabeled from 1s to 3s based on measured fade time
- 3.0
  - New bitmaps for most UI elements
  - Added image previews
  - Forked from FLSTweak repo
- 2.0
  - Updated example `mod.fls` file with measurement label changes, fixed `Normal` label
- 1.1
  - Rendered new small font with all characters shifted down 1 pixel
- 1.0
  - Initial release

## Flashing:
  1. With the DSO3D12 turned off, connect via USB then press and hold the power button - the scope will enter a boot loop and enable the scope's serial port for flashing. Keep the power button pressed until flashing is complete.
  2. Run `zeetweak.py` with the .fls firmware file: `% python3 zeetweak.py ZeeTweak_v5.0.fls`
  3. Select the scope serial port and flash:
     ```
     Found image: ZeeTweak v5.0 (CRC verified)
        1) /dev/cu.usbserial-1420   USB Serial  [CH340]  (default)
     Port to flash [Enter = 1]:
     Ready to flash, press Enter to continue or q to cancel:
       [##############################] 100%  461/461 blocks
     Flash completed successfully! Power cycle the scope to enable the USB/serial port.
     ```
  4. Done! Release the power button.

After flashing, power cycle the scope once - this makes the USB/serial port available for connection. Note that `zeetweak.py` only flashes the application, never the bootloader - this allows for safe recovery in case of any issues.

The firmware can also be flashed with other tools:
  * [wm-tools](https://github.com/rssdev10/wm-tools) (Linux/macOS/Windows): A flashing utility and GUI by @rssdev10 that does not require installing Python.
  * [Winner Micro SDK](https://doc.winnermicro.net/download/version/) (Linux/macOS)
  * [WM Upgrade Tools](http://www.isme.fun/?log=blog&id=34) (Windows)

## Options
```
zeetweak.py --options source

  source                 Serial port, saved waveform .bin file/directory, .fls firmware to flash

  --port PORT            Scope serial port
  --baud BAUD            Serial port baud rate 115200-2M (default 1M)
  --output OUTPUT        Output filename prefix
  --sidecar              Write txt/csv data files
  --width WIDTH          Output image width in pixels (default 1650)
  --title TITLE          Display custom title
  --meas MEAS            Display custom measurements (original: --meas, custom: --meas="freq,amp", default all)
  --window START[:COUNT] Render part of the FPGA waveform capture instead of the scope's window
  --trigline             Draw dashed line at trigger level
  --nocurs               Disable drawing cursors and measurements
  --datetime             Append current datetime to title and filenames
  --color1 COLOR1        Override channel 1 color (--color1="yellow", --color1="#ff00ff")
  --color2 COLOR2        Override channel 2 color
  --waveform             Convert an image to a signal generator waveform
  --scale                Scale signal generator waveform to full dynamic range (0-255)
  --backup [FILE]        Backup flash persistent region
  --debug                Display debug output
```

## Files
- `ZeeTweak_v5.0.fls` - modified firmware to flash to the scope.

- `zeetweak.py` - companion tool for waveform capture, image/text report generation, arbitrary waveform generation, and flashing.

- `mods` - binary patches for the stock firmware, apply with [FLSTweak](https://github.com/taligentx/FLSTweak) to customize mods (different signal generator waveforms, home screen backgrounds, etc).

- `resources`
  - `images` - original and modified UI images.
  - `dso3d12_v3.0.7_ghidra_project_v0.5.gar` - reverse engineering project for [Ghidra](https://github.com/NationalSecurityAgency/ghidra).
    1. Install the [ghidra_csky_WinnerMicro](https://github.com/taligentx/ghidra_csky_WinnerMicro) extension - I've forked the original extension and added all C-SKY instructions seen in the Zeeweii firmware for complete disassembly and decompilation.
    2. Open the firmware project in Ghidra using File > Restore Project.
    3. Double-click the firmware image to launch CodeBrowser and view the disassembly and decompiler output.

- `source` - buildable and extendable firmware source, see [source/README.md](source/README.md).

## Arbitrary Waveform Patterns
Most signal generator waveforms are calculated, but the Sinc function (pattern `7`) is actually stored as hardcoded data. This makes it possible to replace it with other waveforms. To generate a new waveform:
  1. Create a 256x256 image (bmp, png, etc) with a black background and white waveform. The script will resize larger images and pick the bright pixels to use as waveform data.
  2. Run: `zeetweak.py --waveform my_waveform.png` (add `--scale` if needed)
  3. Use the output `waveform_pattern_mod.bin` file with [FLSTweak](https://github.com/taligentx/FLSTweak) to generate a new flash file.
  4. Flash the firmware and select the Sinc waveform in the signal generator to see your waveform!

A few included examples:

mod_staircase / mod_am:

![Waveform-Staircase-AM](https://github.com/user-attachments/assets/56d3beb0-0b8e-41b9-8772-0a83ac9a4e3e)

mod_ecg / mod_heart:

![Waveform-ECG-Heart](https://github.com/user-attachments/assets/a4c47713-9cf5-4bfe-94fa-a0f1feb4f005)

## Home Screen Images
The home screen (accessed by pressing the power button once) is simply a full-color image (320x240 16bpp RGB565), which opens up the possibility to use any photo or image. I've included a few different options as an example of customizing this UI.

Original -> New:

![Home](https://github.com/user-attachments/assets/0b468aa4-55ff-4fe8-83e5-3cf91fa71cf3)

mod_mono / mod_texture:

![Home-Mono-Texture](https://github.com/user-attachments/assets/144d42ff-838a-4f93-ac3c-b2b99ef49a93)

mod_smoke / mod_webb:

![Home-Smoke-Webb](https://github.com/user-attachments/assets/d0f2669c-4645-4731-81f6-66ec38950ae1)

## UI Tweaks - Fonts and Images
- `mods/font_large, font_small` - fonts covering ASCII characters 32-126 as 1-bit data. [ImageMagick](https://imagemagick.org) can convert the raw data to a series of images and also be used to generate new fonts:
  - `$ magick -depth 1 -size 8x13 gray:font_small_ref.bin font_small_ref.png`
  - `$ magick -depth 1 -size 16x16 gray:font_large_ref.bin font_large_ref.png`
  - Thanks to [@timschuerewegen](https://www.eevblog.com/forum/testgear/new-2ch-pocket-dsosg-sigpeak-dso2512g/msg5124096/#msg5124096) for developing the fonts (originally for the DSO2512G) and permitting their addition to this repo! Check out the Discord channel for a detailed discussion of Zeeweii firmware and reverse engineering work for the DSO2512G.

- `mods/image_XXXXXX` - images are either monochrome 1-bit PNG or color 16-bit RGB565 BMP; filenames are the offset of the data in the firmware file. ImageMagick can convert the 1-bit images:
  - Convert raw data to image (must specify the size): `$ magick -depth 1 -size 67x198 gray:image_368172_ref.bin image_368172_ref.png`
  - Convert image to raw data: `$ magick image.png -depth 1 gray:image.bin`
  - Thanks to [@Dmitur](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/msg5789049/#msg5789049) for locating and documenting these resources, and for permitting their addition to this repo! See the post for additional info.

## Screenshots
Original -> New:

![Menu-Comparison-Measure](https://github.com/user-attachments/assets/20faf2a1-d9a6-480d-85c6-a74f02b31df7)

![Menu-Comparison-Trig](https://github.com/user-attachments/assets/1bde81cb-ce6d-4d94-aee8-319c04118183)

![Menu-Comparison-Disp](https://github.com/user-attachments/assets/0b95324f-32bc-4017-9aa8-e17c1c6442a8)

![Menu-Comparison-Set](https://github.com/user-attachments/assets/c46b1b98-a0ed-4e19-b20e-b6ad2292acf9)

![Menu-Comparison-Math](https://github.com/user-attachments/assets/7a111e48-3185-44f8-8950-8a6a1ead32ba)

![Menu-Comparison-DMM1](https://github.com/user-attachments/assets/a45bac94-8c37-4435-be33-61fe54ae5645)

![Menu-Comparison-DMM2](https://github.com/user-attachments/assets/f635e3a7-54dc-4735-bb9e-77c2837121fa)

![Menu-Comparison-Custom](https://github.com/user-attachments/assets/b8e4b46e-0f64-4b33-8b7b-4c98babe9ac4)

## Additional Resources
- Discussion thread: [EEVBlog forums](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/) Another DSO+DMM - Zeeweii DSO3D12, claimed 120MHz/250MSps (june 2023)
- [wm-tools](https://github.com/rssdev10/wm-tools) - flashing utility and desktop app for screenshots by @rssdev10
