<h1 align="center">
AUTD3: Airborne Ultrasound Tactile Display 3
</h1>

<div align="center">

[![Crate.io version](https://img.shields.io/crates/v/autd3)](https://crates.io/crates/autd3)
[![C++](https://img.shields.io/github/v/release/shinolab/autd3-cpp?label=C%2B%2B)](https://github.com/shinolab/autd3-cpp/releases/latest)
[![NuGet stable version](https://img.shields.io/nuget/v/autd3sharp)](https://nuget.org/packages/AUTD3Sharp)
[![autd3-unity](https://img.shields.io/npm/v/com.shinolab.autd3?label=autd3-unity)](https://www.npmjs.com/package/com.shinolab.autd3)
[![PyPI version](https://img.shields.io/pypi/v/pyautd3)](https://pypi.org/project/pyautd3/)

</div>

<p align="center">
Airborne Ultrasound Tactile Display (AUTD) is a midair haptic device that can remotely produce tactile sensation on a human skin surface without wearing devices.
Please see <a href="https://hapislab.org/en/airborne-ultrasound-tactile-display">our laboratory homepage</a> for more details on AUTD.
This repository contains a client library to drive AUTD version 3 devices.
This cross-platform library supports Windows, macOS, and Linux (including Single Board Computer such as Raspberry Pi).
</p>

> [!WARNING]  
> From v17.0.0, the software is completely incompatible with v2.x and v3.x firmware.
> Before using this library, write the latest firmware in `firmware`. For more information, please see [autd3-firmwre](https://github.com/shinolab/autd3-firmware).

## Document

* [日本語/Japanese](https://shinolab.github.io/autd3-doc/jp)
* [English](https://shinolab.github.io/autd3-doc/en)

## Repositories

The autd3 projects are divided into separate repositories.

- Software
  - [Rust](https://github.com/shinolab/autd3-rs)
  - [C API](https://github.com/shinolab/autd3-capi)
  - [C++](https://github.com/shinolab/autd3-cpp)
  - [AUTD3Sharp/autd3-unity](https://github.com/shinolab/AUTD3Sharp)
  - [pyautd3](https://github.com/shinolab/pyautd3)
- [firmware](https://github.com/shinolab/autd3-firmware)
- [AUTD Server](https://github.com/shinolab/autd3-server)
- [Document](https://github.com/shinolab/autd3-doc)

## Citing

* If you use this SDK in your research, please consider including the following citation in your publications:

   * [S. Suzuki, S. Inoue, M. Fujiwara, Y. Makino, and H. Shinoda, "AUTD3: Scalable Airborne Ultrasound Tactile Display," in IEEE Transactions on Haptics, DOI: 10.1109/TOH.2021.3069976.](https://ieeexplore.ieee.org/document/9392322)
   * S. Inoue, Y. Makino and H. Shinoda "Scalable Architecture for Airborne Ultrasound Tactile Display," Asia Haptics 2016

# Author

Shun Suzuki, 2023
