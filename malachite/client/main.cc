/*
 * SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "malachite/client/window.hh"
#include "malachite/common/log.hh"
#include "malachite/common/scope.hh"

#include <glm/ext/vector_uint2_sized.hpp>

#include <stdexcept>

#include "config.h"

constexpr glm::u32vec2 WINDOW_SIZE = {1024, 780};

auto launch_window()
{
	mal::init_windowing();
	auto _guard = mal::OnExit([&](){ mal::cleanup_windowing(); });
	auto window = mal::Window(WINDOW_SIZE, BINARY_NAME);
	while (!window.should_close()) {
		window.poll();
	}
}

// We noexcept(false) here because technically main is supposed to be noexcept
// and clang-tidy does not like it otherwise. I would rather it core
// dump and get a stack trace in development than catch all exceptions even
// though that is *technially* undefined behavior.
auto main() noexcept(false) -> int
{
	auto log = mal::Logger("startup::main");
	try {
		log.i("Engine Information: {} {}", ENGINE_NAME, ENGINE_VERSION_USER);
		launch_window();
	} catch (std::runtime_error &e) {
		log.e("FATAL: {}", e.what());

	}
	return 0;
}
