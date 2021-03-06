// File: gain.hpp
// Project: stm
// Created Date: 11/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 29/06/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include <vector>

#include "autd3/core/interface.hpp"
#include "autd3/driver/cpu/operation.hpp"
#include "stm.hpp"

namespace autd3::core {

#pragma warning(push)
#pragma warning(disable : 26813)

/**
 * @brief GainSTM provides a function to display Gain sequentially and periodically.
 * @details GainSTM uses a timer on the FPGA to ensure that Gain is precisely timed.
 * GainSTM currently has the following three limitations.
 * 1. The maximum number of gains is driver::GAIN_STM_BUF_SIZE_MAX.
 */
struct GainSTM final : public STM {
  explicit GainSTM(const Geometry& geometry) : STM(), _geometry(geometry), _sent(0), _next_duty(false), _mode(driver::GainSTMMode::PhaseDutyFull) {}

  /**
   * @brief Add gain
   * @param[in] gain gain
   */
  template <typename G, std::enable_if_t<std::is_base_of_v<Gain, G>, nullptr_t> = nullptr>
  void add(G& gain) {
    if (_gains.size() + 1 > driver::GAIN_STM_BUF_SIZE_MAX) throw std::runtime_error("GainSTM out of buffer");

    gain.build(_geometry);

    _gains.emplace_back(gain.drives());
  }

  driver::GainSTMMode& mode() noexcept { return _mode; }

  size_t size() const override { return _gains.size(); }

  void init() override { _sent = 0; }

  void pack(const Geometry& geometry, driver::TxDatagram& tx) override {
    geometry.mode()->pack_stm_gain_header(tx);

    if (is_finished()) return;

    geometry.mode()->pack_stm_gain_body(_sent, _next_duty, _freq_div, _gains, _mode, tx);
  }

  [[nodiscard]] bool is_finished() const override { return _sent >= _gains.size() + 1; }

 private:
  const Geometry& _geometry;
  std::vector<std::vector<driver::Drive>> _gains;
  size_t _sent;
  bool _next_duty;
  driver::GainSTMMode _mode;
};

#pragma warning(pop)

}  // namespace autd3::core
