<h1 align="center">
AUTD3: Airborne Ultrasound Tactile Display 3
</h1>

<p align="center">
Airborne Ultrasound Tactile Display (AUTD) is a midair haptic device that can remotely produce tactile sensation on a human skin surface without wearing devices.
Please see <a href="https://hapislab.org/en/airborne-ultrasound-tactile-display">our laboratory homepage</a> for more details on AUTD.
This repository contains a client library to drive AUTD version 3 devices.
This cross-platform library supports Windows, macOS, and Linux (including Single Board Computer such as Raspberry Pi).
</p>

## Document

* [日本語/Japanese](https://shinolab.github.io/autd3-doc/jp)
* [English](https://shinolab.github.io/autd3-doc/en)

## Repositories

The autd3 project consists of the following repositories.

- Software libraries
  - Rust
    - [![autd3](https://img.shields.io/crates/v/autd3?label=autd3)](https://github.com/shinolab/autd3-rs)
    - Extra
      - [![autd3-emulator](https://img.shields.io/crates/v/autd3-emulator?label=autd3-emulator)](https://github.com/shinolab/autd3-emulator)
      - [![autd3-link-soem](https://img.shields.io/crates/v/autd3-link-soem?label=autd3-link-soem)](https://github.com/shinolab/autd3-link-soem) (licensed under GPLv3)
    - C API
      - [![autd3-capi](https://img.shields.io/github/v/release/shinolab/autd3-capi?label=autd3-capi)](https://github.com/shinolab/autd3-capi)
      - [![autd3-capi-link-ethercrab](https://img.shields.io/github/v/release/shinolab/autd3-capi-link-ethercrab?label=autd3-capi-link-ethercrab)](https://github.com/s5suzuki/autd3-capi-link-ethercrab)
      - [![autd3-capi-emulator](https://img.shields.io/github/v/release/shinolab/autd3-capi-emulator?label=autd3-capi-emulator)](https://github.com/shinolab/autd3-capi-emulator)
  - C++
    - [![autd3-cpp](https://img.shields.io/github/v/release/shinolab/autd3-cpp?label=autd3-cpp)](https://github.com/shinolab/autd3-cpp)
  - C#/Unity
    - [![AUTD3Sharp](https://img.shields.io/nuget/vpre/AUTD3Sharp?label=AUTD3Sharp)](https://github.com/shinolab/AUTD3Sharp)
  - Python
    - [![pyautd3](https://img.shields.io/pypi/v/pyautd3?label=pyautd3)](https://github.com/shinolab/pyautd3/)
    - [![pyautd3_emulator](https://img.shields.io/pypi/v/pyautd3_emulator?label=pyautd3_emulator)](https://github.com/shinolab/pyautd3_emulator/)
- Applications
  - [![autd3-server](https://img.shields.io/github/v/release/shinolab/autd3-server?label=AUTD3%20Server)](https://github.com/shinolab/autd3-server)  
    - [![autd3-simulator](https://img.shields.io/github/v/release/shinolab/autd3-simulator?label=autd3-simulator)](https://github.com/shinolab/autd3-simulator)  
    - [![TwinCATAUTDServer](https://img.shields.io/github/v/release/shinolab/TwinCATAUTDServer?label=TwinCATAUTDServer)](https://github.com/shinolab/TwinCATAUTDServer)  
- [![autd3-firmware](https://img.shields.io/github/v/release/shinolab/autd3-firmware?label=firmware)](https://github.com/shinolab/autd3-firmware)
- [![autd3-doc](https://img.shields.io/github/v/tag/shinolab/autd3-doc?label=autd3-doc)](https://github.com/shinolab/autd3-doc)

## Citing

* If you use this SDK in your research, please consider including the following citation in your publications:

   * [S. Suzuki, S. Inoue, M. Fujiwara, Y. Makino, and H. Shinoda, "AUTD3: Scalable Airborne Ultrasound Tactile Display," in IEEE Transactions on Haptics, DOI: 10.1109/TOH.2021.3069976.](https://ieeexplore.ieee.org/document/9392322)
   * S. Inoue, Y. Makino and H. Shinoda "Scalable Architecture for Airborne Ultrasound Tactile Display," Asia Haptics 2016

# Author

Shun Suzuki, 2023-2025
