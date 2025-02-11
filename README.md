<h1 align="center">
AUTD3: Airborne Ultrasound Tactile Display 3
</h1>

<div align="center">

[![Crate.io version](https://img.shields.io/crates/v/autd3)](https://crates.io/crates/autd3)
[![C++](https://img.shields.io/github/v/release/shinolab/autd3-cpp?label=C%2B%2B)](https://github.com/shinolab/autd3-cpp/releases/latest)
[![NuGet stable version](https://img.shields.io/nuget/vpre/autd3sharp)](https://nuget.org/packages/AUTD3Sharp)
[![autd3-unity](https://img.shields.io/github/v/tag/shinolab/AUTD3Sharp?include_prereleases&filter=upm%2F*&label=autd3-unity)](https://github.com/shinolab/AUTD3Sharp/tree/upm/latest)
[![PyPI version](https://img.shields.io/pypi/v/pyautd3)](https://pypi.org/project/pyautd3/)
[![Dart/Flutter](https://img.shields.io/github/v/tag/shinolab/autd3-dart?label=Dart%2FFlutter)](https://github.com/shinolab/autd3-dart)

</div>
<div align="center">

[![release](https://img.shields.io/github/v/release/shinolab/autd3-server?label=AUTD3%20Server)](https://github.com/shinolab/autd3-server/releases/latest)
[![AUTD3 app](https://img.shields.io/github/v/tag/shinolab/autd3-app?label=app)](https://github.com/shinolab/autd3-app)

</div>

</div>
<div align="center">

[![release](https://img.shields.io/github/v/release/shinolab/autd3-firmware?label=firmware)](https://github.com/shinolab/autd3-firmware/releases/latest)

</div>

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
    - [autd3](https://github.com/shinolab/autd3-rs)
    - Extra
      - [autd3-emulator](https://github.com/shinolab/autd3-emulator)
      - [autd3-link-soem](https://github.com/shinolab/autd3-link-soem)
      - [autd3-link-ethercrab](https://github.com/shinolab/autd3-link-ethercrab) (experimental)
      - [autd3-backend-cuda](https://github.com/shinolab/autd3-backend-cuda)
      - [autd3-backend-arrayfire](https://github.com/shinolab/autd3-backend-arrayfire)
    - C API
      - [autd3-capi](https://github.com/shinolab/autd3-capi)
      - [autd3-capi-emulator](https://github.com/shinolab/autd3-capi-emulator)
      - [autd3-capi-link-soem](https://github.com/shinolab/autd3-capi-link-soem)
  - C++
    - [autd3-cpp](https://github.com/shinolab/autd3-cpp)
    - [autd3-cpp-link-soem](https://github.com/shinolab/autd3-cpp-link-soem)
  - C#/Unity
    - [AUTD3Sharp](https://github.com/shinolab/AUTD3Sharp)
    - [AUTD3Sharp.Link.SOEM](https://github.com/shinolab/AUTD3Sharp.Link.SOEM)
  - Python
    - [pyautd3](https://github.com/shinolab/pyautd3)
    - [pyautd3_emulator](https://github.com/shinolab/pyautd3_emulator)
    - [pyautd3_link_soem](https://github.com/shinolab/pyautd3_link_soem)
  - Dart/Flutter
    - [autd3-dart](https://github.com/shinolab/autd3-dart) (only supports lightweight mode)
- Applications
  - [AUTD3 Server](https://github.com/shinolab/autd3-server)
    - [autd3-simulator](https://github.com/shinolab/autd3-simulator)
    - [SOEMAUTDServer](https://github.com/shinolab/SOEMAUTDServer)
    - [TwinCATAUTDServer](https://github.com/shinolab/TwinCATAUTDServer)
  - [AUTD3 app](https://github.com/shinolab/autd3-app) - a simple flutter app for smartphone
- [Firmware](https://github.com/shinolab/autd3-firmware)
- [Document](https://github.com/shinolab/autd3-doc)

## Citing

* If you use this SDK in your research, please consider including the following citation in your publications:

   * [S. Suzuki, S. Inoue, M. Fujiwara, Y. Makino, and H. Shinoda, "AUTD3: Scalable Airborne Ultrasound Tactile Display," in IEEE Transactions on Haptics, DOI: 10.1109/TOH.2021.3069976.](https://ieeexplore.ieee.org/document/9392322)
   * S. Inoue, Y. Makino and H. Shinoda "Scalable Architecture for Airborne Ultrasound Tactile Display," Asia Haptics 2016

# Author

Shun Suzuki, 2023-2025
