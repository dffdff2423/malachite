/*
 * SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <cstdint>

namespace mal {

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

// NOLINTBEGIN

class NoCopy {
public:
	NoCopy() = default;
	NoCopy(const NoCopy& other) = delete;
	auto operator=(const NoCopy& other) -> NoCopy & = delete;
};

class NoMove {
public:
	NoMove() = default;
	NoMove(NoMove &&rhs) noexcept;
	auto operator=(NoMove &&rhs) noexcept -> NoMove &;
};

// NOLINTEND

constexpr u8 VK_REQ_VERSION_MAJ = 1;
constexpr u8 VK_REQ_VERSION_MIN = 3;

namespace units {
	constexpr u32 KB = 1024;
	constexpr u32 MB = KB*1024;
}

} // namespace mal
