/*
 * SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include "malachite/common/core.hh"

#include <stdexcept>
#include <utility>

#include <glm/ext/vector_uint2_sized.hpp>

struct GLFWwindow;

namespace mal {

struct GLFWError : public std::runtime_error {
	GLFWError(int code, const char *txt) : runtime_error(txt), m_code(code) {}
	int m_code;
};

/// Sets up the global state required to open windows
void init_windowing();

/// Cleans up the global state required to open windows
void cleanup_windowing() noexcept;

/// Represents a window of the underlying window system.
class Window : private NoCopy {
public:
	Window(glm::u32vec2 size, const char *title);
	~Window();

	Window(Window &&rhs) noexcept
		: _handle(rhs._handle)
	{
		if (&rhs != this) {
			rhs._handle = nullptr;
		}
		set_callback_ptr();
	}

	auto operator=(Window &&rhs) noexcept -> Window &
	{
		auto n = Window(std::move(rhs));
		std::swap(*this, n);
		return *this;
	}

	/// Check if the window is expected to close
        [[nodiscard]] auto should_close() const noexcept -> bool;

	/// Set whether or not the window is expected to close
	void set_close(bool val = true) const noexcept;

	/// Poll for events from glfw
	void poll() const noexcept;

	/// Get the current size of the window
	[[nodiscard]] auto size() const noexcept -> glm::u32vec2;

private:
	void set_callback_ptr() noexcept;

	GLFWwindow *_handle = nullptr;
};

} // namespace mal
