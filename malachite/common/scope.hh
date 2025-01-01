/*
 * SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include "malachite/common/core.hh"

#include <functional>
#include <utility>

namespace mal {

/// Very simple class that calls the given lambda in it's destructor
class OnExit : mal::NoCopy, mal::NoMove {
public:
	template<typename Callable>
	OnExit(Callable &&lambda) noexcept: _lambda(std::forward<Callable>(lambda)) {}
	~OnExit() { _lambda(); }

private:
	std::function<void()> _lambda;
};

} // namespace mal
