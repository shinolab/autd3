// File: point.hpp
// Project: stm
// Created Date: 11/05/2022
// Author: Shun Suzuki
// -----
// Last Modified: 28/06/2022
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2022 Shun Suzuki. All rights reserved.
//

#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "autd3/core/interface.hpp"
#include "autd3/driver/cpu/operation.hpp"
#include "stm.hpp"

namespace autd3::core {

/**
 * @brief Controll point and duty shift used in PointSTM
 */
struct Point {
  /**
   * @brief Controll point
   */
  Vector3 point;
  /**
   * @brief duty shift. The duty ratio will be (50% >> duty_shift).
   */
  uint8_t shift;

  explicit Point(Vector3 point, const uint8_t shift = 0) : point(std::move(point)), shift(shift) {}
  ~Point() = default;
  Point(const Point& v) noexcept {
    point = v.point;
    shift = v.shift;
  }
  Point& operator=(const Point& obj) {
    point = obj.point;
    shift = obj.shift;
    return *this;
  }
  Point(Point&& obj) = default;
  Point& operator=(Point&& obj) = default;
};

/**
 * @brief PointSTM provides a function to display the focus sequentially and periodically.
 * @details PointSTM uses a timer on the FPGA to ensure that the focus is precisely timed.
 * PointSTM currently has the following three limitations.
 * 1. The maximum number of control points is driver::POINT_STM_BUF_SIZE_MAX.
 * 2. Only a single focus can be displayed at a certain moment.
 */
struct PointSTM final : public STM {
  using value_type = Point;

  PointSTM() : STM(), _sent(0) {}

  /**
   * @brief Add control point
   * @param[in] point control point
   * @param[in] duty_shift duty shift. The duty ratio will be (50% >> duty_shift).
   */
  void add(const Vector3& point, uint8_t duty_shift = 0) {
    if (_points.size() + 1 > driver::POINT_STM_BUF_SIZE_MAX) throw std::runtime_error("PointSTM out of buffer");
    _points.emplace_back(point, duty_shift);
  }

  void push_back(const value_type& v) {
    if (_points.size() + 1 > driver::POINT_STM_BUF_SIZE_MAX) throw std::runtime_error("PointSTM out of buffer");
    _points.emplace_back(v);
  }

  size_t size() const override { return _points.size(); }
  void init() override { _sent = 0; }
  void pack(const Geometry& geometry, driver::TxDatagram& tx) override {
    point_stm_header(tx);

    if (is_finished()) return;

    const auto is_first_frame = _sent == 0;
    const auto max_size = is_first_frame ? driver::POINT_STM_HEAD_DATA_SIZE : driver::POINT_STM_BODY_DATA_SIZE;

    const auto send_size = std::min(_points.size() - _sent, max_size);
    const auto is_last_frame = _sent + send_size == _points.size();

    std::vector<std::vector<driver::STMFocus>> points;
    std::transform(geometry.begin(), geometry.end(), std::back_inserter(points), [this, send_size](const Geometry::Device& dev) {
      std::vector<driver::STMFocus> lp;
      const auto src = _points.data() + _sent;
      std::transform(src, src + send_size, std::back_inserter(lp), [&dev](const auto& p) {
        const auto local = dev.to_local_position(p.point);
        return driver::STMFocus(local.x(), local.y(), local.z(), p.shift);
      });
      return lp;
    });

    driver::point_stm_body(points, is_first_frame, this->_freq_div, geometry.sound_speed, is_last_frame, tx);

    _sent += send_size;
  }

  [[nodiscard]] bool is_finished() const override { return _sent == _points.size(); }

 private:
  std::vector<Point> _points;
  size_t _sent;
};

}  // namespace autd3::core
