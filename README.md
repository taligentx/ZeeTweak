# ZeeTweak
ZeeTweak is a collection of firmware and UI changes for the [Zeeweii DSO3D12 oscilloscope](http://www.zeeweii.com/productinfo/dso3d12.html), including:
  * Saved waveform download: Capture screenshot data via serial and render new waveform images + text reports
  * Arbitrary signal generator waveforms
  * UI overhaul: New fonts, replacement of most UI elements, screenshot counter repositioning
  * New home screen graphics (with multiple home screen background options)
  * Sample buffer download: Capture and extract the secret dump mode output that sends the complete buffer (up to 60k samples)

![Zeeweii_DSO3D12_mod_v3.1](https://github.com/user-attachments/assets/88fa9dd7-0761-489b-bc0e-031cb9fce3c7)

ZeeTweak capture and render:

![ZeeTweak_Screenshot_Capture](https://github.com/user-attachments/assets/3f2c1050-9e6e-4f96-8044-913bcf68042a)

The provided example firmware has all mods applied, see Flashing below to apply the firmware.
- To customize the firmware, place the desired mod files in a directory and use [FLSTweak](https://github.com/taligentx/FLSTweak) to generate a new firmware file.

## Notes
- Most UI mods in this repo cover resources that are directly stored in the firmware (not part of the compiled code), so images are altered but not functionally changed.
    * With release 4.0, some mods are based on reverse engineering of the firmware code (screenshot transfer, arbitrary waveforms, screenshot counter repositioning), which opens up the possibility of more functional changes. See the `Ghidra` files section below.
- Since UI preferences are highly subjective, post an [Issue](https://github.com/taligentx/ZeeTweak/issues) or [Pull Request](https://github.com/taligentx/ZeeTweak/pulls) for what you'd like to see - there is plenty of room for improvement. Discussion and (especially) contributions are welcome!

## Release Notes
- 4.0
  - New: `zeetweak.py`
      * Screenshot data capture and rendering to new images with matplotlib
      * Arbitrary signal generator waveforms
      * Buffer dump capture (via secret debug mode)
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

## Files
- `zeetweak.py` - Tool for screenshot capture, image/text report generation, arbitrary waveform generation, and buffer dump capture. See below for usage.
  - Requirements: `pip install pyserial numpy pillow matplotlib`
  - `zeetweak.sh` - Helper script if you need/want a Python virtual environment (as on macOS with [Homebrew](https://brew.sh)):
      * `chmod +x zeetweak.sh` and then run with the same arguments as `zeetweak.py`.
      * Required packages will be automatically installed.

- `Zeeweii_DSO3D12` directory:
  - `dso3d12_v3.0.7_III_mod_v4.0.fls` - an example firmware with all mods applied.
  - `images` - viewable files of the original and modified UI images.
  - `mods` - binary files of the original and modified data for use with [FLSTweak](https://github.com/taligentx/FLSTweak), including additional optional mods (different signal generator waveforms, home screen backgrounds, etc).

- `Ghidra` directory:
  - `dso3d12_v3.0.7_ghidra_v0.2.gar` - reverse engineering project for [Ghidra](https://github.com/NationalSecurityAgency/ghidra).
    - This is a very early stage for the runtime firmware and currently includes defined function boundaries, memory addresses (embedded data and peripherals), labels for embedded data (images, strings), many SDK library functions with the SDK data types, and parts of the Zeeweii-specific code. Many labels are up for debate and pending verification.
    - There is a lot of low-hanging fruit at the moment! There are plenty of functions/variables/ram data that are obvious and can be labeled with their correct definition - up to now, my focus has been on the Ghidra C-SKY extension and implementing the SDK library functions, so quite a bit of the Zeeweii-specific code is left to discover. Enjoy the hunt!
    - Usage:
      1. Install the [ghidra_csky_WinnerMicro](https://github.com/taligentx/ghidra_csky_WinnerMicro) extension - I've forked the original extension to add all C-SKY instructions seen in the Zeeweii firmware for complete disassembly and decompilation.
      2. Open the firmware project in Ghidra using File > Restore Project.
      3. Double-click the firmware image to launch CodeBrowser and view the disassembly and decompiler output.
      4. Feedback appreciated! Feel free to [post an Issue](https://github.com/taligentx/ZeeTweak/issues) or in the [EEVBlog forum thread](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/).

## Flashing:
### [wm-tools](https://github.com/taligentx/ZeeTweak/issues/3) (Linux/macOS/Windows):
  * A flashing utility by @rssdev10 based on Winner Micro's tool that does not require installing Python or other extras. Note that the Linux and Windows versions are currently untested.

### Winner Micro SDK: (Linux/macOS):
  1. Download and extract the [WM IoT SDK](https://doc.winnermicro.net/download/version/).
  2. Install required packages - from the `wm_iot_sdk` directory:
     ```
     python -m pip install --user -r tools/wm/requirements.txt
     ```
  3. With the DSO3D12 turned off, press and hold the power button - the scope will enter a boot loop and enable the scope's serial port to allow for flashing. Keep the power button pressed until flashing is complete.
  4. Check the name of the serial port - on macOS, use the `tty.wchusbserial` device if two ports are detected:
     ```
     % ls /dev/tty*
     /dev/tty.Bluetooth-Incoming-Port
     /dev/tty.usbserial-1410  
     /dev/tty.wchusbserial1410
     ```
  5. From the `wm_iot_sdk/tools/wm/` directory, run `flash.py` with the serial port and firmware:
     ```
     % python3 flash.py --port /dev/tty.wchusbserial1410 --image dso3d12_v3.0.7_III_mod.fls 
     connecting serial...
     serial connected
     trying reset device...
     wait serial sync...
     serial sync success
     trying baudrate 2000000...
     start download image...
     download dso3d12_v3.0.7_III_mod.fls...
     0% [##############################] 100%
     flash device complete
     ```
  6. Done! Release the power button.

### WM Upgrade Tools (Windows):
  1. Download [Upgrade Tools](http://www.isme.fun/?log=blog&id=34).
  2. Change the language to English from the top left menu (third option).
  3. Set "Chip" to `W80X` and set the image to the firmware .fls file.
  4. Press and hold the scope power button to enable the serial port until flashing is complete.
  5. Select the new COM port, click "Open Serial", and then "Download" to flash.
  6. Done! Release the power button.
  ![Flashing_DSO3D12_Upgrade_Tools](https://github.com/user-attachments/assets/0cf60add-3fdf-4c25-b316-f78c7475e515)


## Screenshots Capture and Rendering 
`screenshot_viewer_mod` is a code patch combining two features:
  - Screenshot count repositioning - moves the image count to the upper right of the display, replacing the battery level display. The original firmware placed the count in the graticule, obscuring cursor measurements data and any waveforms below.
    - Caveat: This replaces the total screenshot count (`1` instead of `1/63`). The extra code space has been repurposed for...

  - Screenshot data transfer - the scope will now transfer the waveform data and scope state/settings via serial when an image is viewed. Note that this is the data only - the scope uses the data to regenerate the displayed image and doesn't save the original screen as a bitmap image, etc.
    - After capture, `zeetweak.py` will process and render a new image using the waveform data using matplotlib, and also generate a text report with the available data and measurements, including measurements that weren't originally part of the screenshot.
    - Caveat: Some data (like cursor measurements and math) is freshly calculated by the scope when the screenshot is viewed instead of being stored. The script currently doesn't handle this - it's likely more useful to render the data in something like PyQtGraph for fully interactive cursors/math/inversion etc. The cursor positions, however, are stored and will be displayed in the image.
    - If you prefer not to have the scope send this data, use the `screenshot_viewer_mod_count_reposition_only.bin` mod file instead.
  ### Usage
  1. Launch `zeetweak.py` with the scope's serial port:
     ```
     % python3 zeetweak.py /dev/tty.usbserial-1410
     Waiting for /dev/tty.usbserial-1410... (Ctrl+C to cancel)
     ```
  2. Power on the scope (it may reset off when the serial port is initialized).
  3. Once the scope is connected, open the screenshot browser and open a saved waveform - the data will be transferred and processed automatically:
     ```
     Connected, open saved waveforms to trigger capture:
     Saved data:  Zeeweii_Screenshot_20251216_202613.bin
     Saved text:  Zeeweii_Screenshot_20251216_202613.txt
     Saved image: Zeeweii_Screenshot_20251216_202613.png
     ```
  ### Options
  `zeetweak.py [-h] [-o OUTPUT] [--color1 COLOR1] [--color2 COLOR2] [--meas MEAS] [--trigline] [--title TITLE] [--datetime] [-w WIDTH] [--debug] source`
  * `source` - Specify the serial port of the scope, a filename (to re-process a previously saved .bin file), or a directory containing multiple saved .bin files to batch process.
  * `-o OUTPUT` - Specify a filename prefix for the output. If the source is a single file, this will be the entire filename.
  * `--color1, --color2` - Specify new channel 1 and channel 2 colors: `--color1="yellow" --color2="#ff00ff"`
  * `--meas` - Specify the measurement labels to display in the image (the text output will always show all measurements). By default, the tool will use the measurements displayed in the original screenshot.
    * You can retroactively display all measurements, or select:
      * `--meas="all"`
      * `--meas="Freq,PkPk,Avg,RMS,Amp,+Duty,+T,-T,T,Max,Min,Top,Base,-Duty"`
  * `--trigline` - Display a dashed line at the trigger line
  * `--title TITLE` - Add a custom title to the image and text report.
  * `--datetime` - Add the current date and time to custom titles and filenames when processing single files or directories. Timestamp is always added to serial captured files.
  * `-w WIDTH` - Specify a width in pixels (default: `1650` for 150dpi)
  * `--debug` - Adds extra debugging information during serial capture, including all scope state/settings data in the text report and a diff between sequential images at the console output to help identify additional scope data.

## Arbitrary Waveform Patterns
`waveform_pattern_mod` - most signal generator waveforms are calculated, but the Sinc function (pattern `7`) is actually stored as hardcoded data. This makes it possible to replace it with other waveforms that fit in 256 bytes.
  - Quirk: Possibly due to a compiler optimization, the starting sample (1 byte) is hardcoded into the firmware and the remaining 255 bytes are normal data. I've patched the starting sample to be `0x80` (the centerline).
  - `zeetweak.py` can automatically convert images to waveforms, optionally scale to full dynamic range (0-255), adjust the waveform to align with the hardcoded starting sample, and produce the correctly sized mod data to flash.

To generate a new waveform:
  1. Create a 256x256 image (bmp, png, etc) with a black background and white waveform. The script will resize larger images and pick the bright pixels to use as waveform data.
  2. Run: `zeetweak.py --waveform my_waveform.png` (add `--scale` if needed)
  3. Use the output `waveform_pattern_mod.bin` file with [FLSTweak](https://github.com/taligentx/FLSTweak) to generate a new flash file.
  4. Flash the firmware and select the Sinc waveform in the signal generator to see your waveform!

A few included examples:

mod_staircase / mod_am:

![Waveform-Staircase-AM](https://github.com/user-attachments/assets/46732837-9e73-4f8b-af5a-4d5d773bd9d1)

mod_ecg / mod_heart:

![Waveform-ECG-Heart](https://github.com/user-attachments/assets/15cea14a-acb0-49ca-991e-71e58c209694)

## Buffer Capture via Secret Dump Mode
Reverse engineering the firmware revealed a function that reads out the FPGA sample buffer (up to 60k samples). This allows capturing higher resolution data that may be usable with other tools to analyze the data. To capture the data:
  1. Launch `zeetweak.py` with the scope's serial port:
     ```
     % python3 zeetweak.py /dev/tty.usbserial-1410
     Waiting for /dev/tty.usbserial-1410... (Ctrl+C to cancel)
     ```
  2. Power on the scope (it may reset off when the serial port is initialized).
  3. Acquire the signal(s), then press `Stop` to freeze the sample buffer.
  4. Press `Menu`, then `Stop` so that the channel 1 measurements menu is open.
  5. Long-press `Save` - this kicks off the debug dump:
     ```
     Connected, open saved waveforms to trigger capture:
     Receiving data...
     Saved debug dump: Zeeweii_Debug_20251216_180138.bin (270024 bytes)
     Extracted CH1: Zeeweii_Debug_20251216_180138-ch1.bin (60000 samples)
     ```
     2 channels:
     ```
     Receiving data...
     Saved debug dump: Zeeweii_Debug_20251216_145708.bin (285042 bytes)
     Extracted CH1: Zeeweii_Debug_20251216_145708-ch1.bin (30000 samples)
     Extracted CH2: Zeeweii_Debug_20251216_145708-ch2.bin (30000 samples)
     ```
  6. I recommend also taking a screenshot of the stopped waveform and transferring it - the buffer dump does not include any scope state/settings data (v/div, timebase, etc).

Notes:
  - At full 60k sample depth, it can take up to 20s to transfer the data. At the fastest ranges (5ns, etc), the debug function switches to a fast mode with interpolation and sends 300 samples.
  - The original debug dump converts the data to ASCII and prints it with spaces, line endings, etc. `zeetweak.py` extracts the data for each channel and saves as normal binary.
  - It should be possible to modify the firmware to directly send hex data and also include the scope state/settings data, on the todo list.

## Home Screen Images
The home screen (accessed by pressing the power button once) is simply a full-color image (320x240 16bpp), which opens up the possibility to use any photo or image. I've included a few different options as an example of customizing this UI.

Original -> Mod:

![Home](https://github.com/user-attachments/assets/0b468aa4-55ff-4fe8-83e5-3cf91fa71cf3)

mod_mono / mod_texture:

![Home-Mono-Texture](https://github.com/user-attachments/assets/144d42ff-838a-4f93-ac3c-b2b99ef49a93)

mod_smoke / mod_webb:

![Home-Smoke-Webb](https://github.com/user-attachments/assets/d0f2669c-4645-4731-81f6-66ec38950ae1)

## Fonts, Images and Labels
- `font_large, font_small` - fonts covering ASCII characters 32-126 as 1-bit data.
  - [ImageMagick](https://imagemagick.org) can convert the raw data to a series of images:
      - `$ magick -depth 1 -size 8x13 gray:font_small_ref.bin font_small_ref.png`
      - `$ magick -depth 1 -size 16x16 gray:font_large_ref.bin font_large_ref.png`
  - Thanks to [@timschuerewegen](https://www.eevblog.com/forum/testgear/new-2ch-pocket-dsosg-sigpeak-dso2512g/msg5124096/#msg5124096) for developing the fonts (originally for the DSO2512G) and permitting their addition to this repo! Check out the Discord channel for a detailed discussion of Zeeweii firmware and reverse engineering work for the DSO2512G.

- `image_XXXXXX` - images are either monochrome 1-bit per pixel or color 16-bits per pixel (RGB565 format); filenames are the offset of the data in the firmware file.
  - 1bpp images:
    - Viewable as PNG files in the `images` directory
    - Convert raw data to image (must specify the size): `$ magick -depth 1 -size 67x198 gray:image_368172_ref.bin image_368172_ref.png`
    - Convert image to raw data: `$ magick image.png -depth 1 gray:image.bin`
  - 16bpp images:
    - Viewable as BMP files in `images`
  - Thanks to [@Dmitur](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/msg5789049/#msg5789049) on the EEVBlog forums for locating and documenting these resources, and for permitting their addition to this repo! See the post for additional info.
- `label_calib` - fixes typos for DMM calibration text
- `label_measurements` - alters the measurements labels and matches the labels in `image_364864_mod.bin`
- `label_normal` - fixes typo for the "Normal" trigger message

## Screenshots
Original -> Mod:

![Menu-1-Meas](https://github.com/user-attachments/assets/6470a733-dfbe-421f-bc9b-fdd3036129a0)

![Menu-2-Trig](https://github.com/user-attachments/assets/5c6eea42-4e2f-42f1-bfda-f3129afa0cac)

![Menu-3-Disp](https://github.com/user-attachments/assets/d7b78822-b35d-4301-950a-b6bfdcefd4bd)

![Menu-4-Set](https://github.com/user-attachments/assets/b4b66e35-e599-4e91-8ec5-d87bba995cb7)

![Channel-Math](https://github.com/user-attachments/assets/f40aac02-9486-4718-a540-cb88ceda014b)

![DMM](https://github.com/user-attachments/assets/b55dcb04-fa1a-4637-8a89-d933af716a81)

![DMM-Side-Menu](https://github.com/user-attachments/assets/f1d3ab39-7a5a-45a7-a2dd-bff42f9526fb)

![Custom](https://github.com/user-attachments/assets/c44d073f-3eee-49fe-9613-00ff49df1b4e)

## Resources
- Firmware: Available through [Zeeweii's official support page](http://www.zeeweii.com/support.html)
- Discussion thread: [EEVBlog forums](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/) Another DSO+DMM - Zeeweii DSO3D12, claimed 120MHz/250MSps (june 2023)
