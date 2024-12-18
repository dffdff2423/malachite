/*
 * SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "config.h"
#include "malachite/common/log.hh"

#include <stdexcept>

auto launch_window()
{

}

// The noexcept annotation I would rather core-dump than catch some exceptions
// in-order to get a backtrace and clang-tidy did not like it otherwise.
auto main() noexcept(false) -> int
{
	auto log = mal::Logger("startup::main");
	try {
		auto log = mal::Logger("startup::main");
		log.i("Engine Information: {} {}", ENGINE_NAME, ENGINE_VERSION_USER);
	} catch (std::runtime_error &e) {
		log.e("FATAL: {}", e.what());

	}
	return 0;
}
