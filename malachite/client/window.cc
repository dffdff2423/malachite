/*
 * SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "malachite/client/window.hh"
#include "malachite/common/log.hh"

#include <GLFW/glfw3.h>
#include <glm/ext/vector_uint2_sized.hpp>

#include "config.h"

namespace mal {

static
void glfw_error_callback(int code, const char *description)
{
	(void)code;
	auto log = Logger("mal::glfw_error_callback");
	log.e("{}", description);;
}

static
void glfw_framebuffer_size_callback(GLFWwindow *win, int wid, int height)
{
	(void)win;
	(void)wid;
	(void)height;
	auto log = Logger("mal::glfw_framebuffer_size_callback");
	log.e("resize unimplemented({}, {})", wid, height);
}

static
void glfw_key_callback(GLFWwindow *_win, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	auto *win = static_cast<Window *>(glfwGetWindowUserPointer(_win));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		win->set_close();
}

void init_windowing()
{
	glfwSetErrorCallback(glfw_error_callback);

	if (glfwInit() == GLFW_FALSE) {
		const char *txt = nullptr;
		int err = glfwGetError(&txt);
		throw GLFWError(err, txt);
	}
}

void cleanup_windowing() noexcept
{
	glfwTerminate(); // NOTE: we ignore errors here
}

Window::Window(glm::u32vec2 size, const char *title)
{
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	glfwWindowHintString(GLFW_X11_CLASS_NAME, ENGINE_NAME);

	_handle = glfwCreateWindow((int)size.x, (int)size.y, title, nullptr, nullptr);
	if (_handle == nullptr) {
		const char *desc = nullptr;
		int code = glfwGetError(&desc);
		throw GLFWError(code, desc);
	}

	set_callback_ptr();
	glfwSetFramebufferSizeCallback(_handle, glfw_framebuffer_size_callback);
	glfwSetKeyCallback(_handle, glfw_key_callback);
}

Window::~Window()
{
	if (_handle == nullptr)
		return;
	glfwDestroyWindow(_handle);
}

auto Window::should_close() const noexcept -> bool
{
	return glfwWindowShouldClose(_handle) != 0;
}

void Window::set_close(bool val) const noexcept
{
	glfwSetWindowShouldClose(_handle, (int)val);
}

void Window::poll() const noexcept
{
	glfwPollEvents();
}

auto Window::size() const noexcept -> glm::u32vec2
{
	int w = 0;
	int h = 0;
	glfwGetWindowSize(_handle, &w, &h);
	return {w, h};
}

void Window::set_callback_ptr() noexcept
{
	glfwSetWindowUserPointer(_handle, this);
}

} // namespace mal
