﻿// File: emulator.cpp
// Project: emulator
// Created Date: 16/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 28/06/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#include "autd3/link/emulator.hpp"

#if WIN32
#include <WS2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "autd3/core/interface.hpp"
#include "autd3/core/link.hpp"

namespace autd3::link {

class EmulatorImpl final : public core::Link {
 public:
  explicit EmulatorImpl(const uint16_t port, const core::Geometry& geometry)
      : Link(), _is_open(false), _port(port), _geometry_datagram(init_geometry_datagram(geometry)) {}
  ~EmulatorImpl() override = default;
  EmulatorImpl(const EmulatorImpl& v) noexcept = delete;
  EmulatorImpl& operator=(const EmulatorImpl& obj) = delete;
  EmulatorImpl(EmulatorImpl&& obj) = delete;
  EmulatorImpl& operator=(EmulatorImpl&& obj) = delete;

  void open() override {
    if (is_open()) return;

#if WIN32
#pragma warning(push)
#pragma warning(disable : 6031)
    WSAData wsa_data{};
    WSAStartup(MAKEWORD(2, 0), &wsa_data);
#pragma warning(pop)
#endif

    _socket = socket(AF_INET, SOCK_DGRAM, 0);
#if WIN32
    if (_socket == INVALID_SOCKET)
#else
    if (_socket < 0)
#endif
      throw std::runtime_error("cannot connect to emulator");

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
#if WIN32
    const auto ip_addr("127.0.0.1");
    inet_pton(AF_INET, ip_addr, &_addr.sin_addr.S_un.S_addr);
#else
    _addr.sin_addr.s_addr = inet_addr("127.0.0.1");
#endif

    _is_open = true;
    send(_geometry_datagram);
  }

  void close() override {
    if (!is_open()) return;
#if WIN32
    closesocket(_socket);
    WSACleanup();
#else
    ::close(_socket);
#endif
    _is_open = false;
  }

  bool send(const driver::TxDatagram& tx) override {
    _last_msg_id = tx.header().msg_id;
    if (sendto(_socket, reinterpret_cast<const char*>(tx.data().data()), static_cast<int>(tx.effective_size()), 0,
               reinterpret_cast<sockaddr*>(&_addr), sizeof _addr) == -1)
      throw std::runtime_error("failed to send data");
    return true;
  }
  bool receive(driver::RxDatagram& rx) override {
    for_each(rx.begin(), rx.end(), [this](auto& msg) { msg.msg_id = this->_last_msg_id; });

    const auto set = [&rx](const uint8_t value) { for_each(rx.begin(), rx.end(), [value](auto& msg) { msg.ack = value; }); };

    switch (_last_msg_id) {
      case driver::MSG_CLEAR:
        break;
      case driver::MSG_RD_CPU_VERSION:
      case driver::MSG_RD_FPGA_VERSION:
      case driver::MSG_RD_FPGA_FUNCTION:
        set(0xFF);
        break;
      default:
        break;
    }
    return true;
  }
  bool is_open() override { return _is_open; }

 private:
  bool _is_open;
  uint16_t _port;
#if WIN32
  SOCKET _socket = {};
#else
  int _socket = 0;
#endif
  sockaddr_in _addr = {};

  uint8_t _last_msg_id = 0;
  driver::TxDatagram _geometry_datagram;

  static driver::TxDatagram init_geometry_datagram(const core::Geometry& geometry) {
    driver::TxDatagram buf(geometry.num_devices());

    auto& uh = buf.header();
    uh.msg_id = driver::MSG_EMU_GEOMETRY_SET;
    uh.fpga_flag = driver::FPGAControlFlags::NONE;
    uh.cpu_flag = driver::CPUControlFlags::NONE;
    uh.size = 0;

    for (size_t i = 0; i < geometry.num_devices(); i++) {
      auto* const cursor = reinterpret_cast<float*>(buf.bodies()[i].data);
      auto& tr = geometry[i][0];
      auto origin = tr.position().cast<float>();
      auto right = tr.x_direction().cast<float>();
      auto up = tr.y_direction().cast<float>();
      cursor[0] = origin.x();
      cursor[1] = origin.y();
      cursor[2] = origin.z();
      cursor[3] = right.x();
      cursor[4] = right.y();
      cursor[5] = right.z();
      cursor[6] = up.x();
      cursor[7] = up.y();
      cursor[8] = up.z();
    }

    return buf;
  }
};
core::LinkPtr Emulator::build() {
  core::LinkPtr link = std::make_unique<EmulatorImpl>(_port, _geometry);
  return link;
}

}  // namespace autd3::link
