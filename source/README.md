# Zeeweii DSO3D12 firmware build

This is a buildable source for the stock firmware with hooks to add custom code.

## Prerequisites

- Linux x86_64-based system/container
- Stock firmware `dso3d12_v3.0.7_III.fls`: http://www.zeeweii.com/support.html
- C-SKY toolchain
  - Official download (requires creating an account): https://www.xrvm.cn/community/download, search for `csky-elfabiv2-tools-x86_64-minilibc`
  - Mirror download: [csky-elfabiv2-tools-x86_64-minilibc-20250328.tar.gz](https://github.com/Taixin-Semiconductor/XuanTie-CSKY-Toolchains/releases/download/untagged-714ed6e395fc96712ea8/csky-elfabiv2-tools-x86_64-minilibc-20250328.tar.gz)
  - Extract the toolchain:
    ```sh
    $ mkdir csky
    $ cd csky
    $ tar xf /path/to/csky-elfabiv2-tools-x86_64-minilibc-20250328.tar.gz
    ```

## Build
This generates a source from the stock firmware, merges SDK functions, compiles additional code from the `app` directory, and produces a new `ZeeTweak` .fls file in `firmware` to flash to the scope using `zeetweak.py` or other tools.

1. Copy the stock firmware `dso3d12_v3.0.7_III.fls` to the `firmware` directory.
2. Add the toolchain to `PATH`:
    ```sh
    export PATH=/path/to/csky/bin:$PATH
    ```
3. Run `make`


## Code
Additional code goes in `app`, with functional examples.
- The stock firmware uses a bare-metal main superloop (no RTOS with tasks, etc).
- Hooks are setup in scope initialization for `app_init.c` and in the main loop for `app_mainloop.c`.
- Stock functions can be called, a few examples are in `app/inc/zw_api.h`.
- Available resources:
  - Flash: ~72KB, limited by a section of flash used for persistent storage (UUID, calibration, settings, screenshots, etc).
    - There is an additional ~124KB of free flash after the persistent storage, but this is not currently setup for use.
  - SRAM: ~74KB

## Notes
- This source is based on the [Winner Micro W806 SDK v0.6.0](https://www.winnermicro.com/upload/1/editor/1642037102612.rar). The W806 has two other SDKs available:
  - Winner Micro IoT SDK: https://doc.winnermicro.net/download/version/
  - wm-sdk-w806:  https://github.com/IOsetting/wm-sdk-w806
- During `make`, SDK functions override the built-in functions in the stock firmware - added code can use the W806 SDK functions.
