# ZeeTweak
ZeeTweak is an overhaul of the UI for the [Zeeweii DSO3D12 oscilloscope](http://www.zeeweii.com/productinfo/dso3d12.html), including replacement fonts, most UI elements, and various fixes.

![Zeeweii_DSO3D12_mod_v3.0](https://github.com/user-attachments/assets/5f8174e5-4002-4812-8711-748cdb3ddec5)

## Notes
- To customize the firmware, place the desired mod files in a directory and use [FLSTweak](https://github.com/taligentx/FLSTweak) to generate a new firmware file. See Flashing below to apply the firmware.
- The mods in this repo cover resources that are directly stored in the firmware (not part of the compiled code). It will take reverse engineering of the code to functionally change the UI, so the replacements here are a starting point for further work.
- UI preferences are highly subjective - post an [Issue](https://github.com/taligentx/ZeeTweak/issues) or [Pull Request](https://github.com/taligentx/ZeeTweak/pulls) for what you'd like to see, there is plenty of room for improvement. Discussion and (especially) contributions are welcome!

## Release Notes
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
The `Zeeweii_DSO3D12` directory contains:

 - `dso3d12_v3.0.6_III_mod_v3.0.fls` - an example firmware with all mods applied.
 - `images` - viewable files of the original and modified UI images.
 - `mods` - binary files of the original and modified data for use with [FLSTweak](https://github.com/taligentx/FLSTweak).

## Mods
The `mods` directory contains:

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
  - Thanks to [@Dmitur](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/msg5789049/#msg5789049) on the EEVBlog forums for locating and documenting these resources! See the post for additional info and mods (currently not part of this repo).
- `label_calib` - fixes typos for DMM calibration text
- `label_measurements` - alters the measurements labels and matches the labels in `image_364864_mod.bin`
- `label_normal` - fixes typo for the "Normal" trigger message

## Flashing
Linux/macOS:
  1. Download and extract the [WM IoT SDK](https://doc.winnermicro.net/download/version/).
  2. Install required packages - from the `wm_iot_sdk` directory:
     ```
     python -m pip install --user -r tools/wm/requirements.txt
     ```
  3. With the DSO3D12 turned off, press and hold the power button - the scope will enter a boot loop and enable the scope's serial port to allow for flashing. Keep the power button pressed until flashing is complete.
  4. Check the name of the serial port - on macOS, use the `tty.wchusbserial` device:
     ```
     % ls /dev/tty*
     /dev/tty.Bluetooth-Incoming-Port
     /dev/tty.usbserial-1410  
     /dev/tty.wchusbserial1410
     ```
  5. From the `wm_iot_sdk/tools/wm/` directory, run `flash.py` with the serial port and firmware:
     ```
     % python3 flash.py --port /dev/tty.wchusbserial1410 --image dso3d12_v3.0.6_III_mod.fls 
     connecting serial...
     serial connected
     trying reset device...
     wait serial sync...
     serial sync success
     trying baudrate 2000000...
     start download image...
     download dso3d12_v3.0.6_III_mod.fls...
     0% [##############################] 100%
     flash device complete
     ```
  6. Done! Release the power button.

Windows:
  1. Download [Upgrade Tools](http://www.isme.fun/?log=blog&id=34).
  2. Change the language to English from the top left menu (third option).
  3. Set "Chip" to `W80X` and set the image to the firmware .fls file.
  4. Press and hold the scope power button to enable the serial port until flashing is complete.
  5. Select the new COM port, click "Open Serial", and then "Download" to flash.
  6. Done! Release the power button.
  ![Flashing_DSO3D12_Upgrade_Tools](https://github.com/user-attachments/assets/0cf60add-3fdf-4c25-b316-f78c7475e515)

## Home
The home screen (accessed by pressing the power button once) is a 320x240 16bpp image in `image_153880`, which opens up the possibilities for modification. I've included a few different options as an example of customizing this UI.

Original -> Mod:

![Home](https://github.com/user-attachments/assets/aea4cd70-0786-4990-813c-eb9828177fd5)

mod_mono / mod_texture:

![Home-Mono-Texture](https://github.com/user-attachments/assets/9e934119-73a9-4ede-993d-640feb40c9da)

mod_smoke / mod_webb:

![Home-Smoke-Webb](https://github.com/user-attachments/assets/0c310e26-948b-42a3-a996-31d69ff58b53)

## Screenshots
Original -> Mod:

![Menu-1-Meas](https://github.com/user-attachments/assets/6470a733-dfbe-421f-bc9b-fdd3036129a0)

![Menu-2-Trig](https://github.com/user-attachments/assets/5c6eea42-4e2f-42f1-bfda-f3129afa0cac)

![Menu-3-Disp](https://github.com/user-attachments/assets/eabf23c9-7c53-4028-abdc-5331b000cc64)

![Menu-4-Set](https://github.com/user-attachments/assets/b4b66e35-e599-4e91-8ec5-d87bba995cb7)

![DMM](https://github.com/user-attachments/assets/b55dcb04-fa1a-4637-8a89-d933af716a81)

![Custom](https://github.com/user-attachments/assets/c44d073f-3eee-49fe-9613-00ff49df1b4e)

## Resources
- Firmware: Available through [Zeeweii's official support page](http://www.zeeweii.com/support.html)
- Discussion thread: [EEVBlog forums](https://www.eevblog.com/forum/testgear/another-dsodmm-zeeweii-dso3d12-claimed-120mhz250msps/) Another DSO+DMM - Zeeweii DSO3D12, claimed 120MHz/250MSps (june 2023)
