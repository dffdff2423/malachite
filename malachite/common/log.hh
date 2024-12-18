/*
 * SPDX-FileCopyrightText: 2024 dffdff2423 <dffdff2423@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#pragma once

#include <stdio.h>
#include <format>
#include <string_view>

#ifdef __unix__
#include <unistd.h>
#endif

#include "malachite/common/core.hh"

namespace mal {

enum class LogLevel : u8 {
	Debug, Info, Warn, Error,
};

constexpr LogLevel MIN_LOG_LEVEL = LogLevel::Debug;

/// Do not use, create a Logger instead
template<class... Args>
auto _log(LogLevel level, std::string_view location,
	std::format_string<Args...> fmt, Args&&... args)
{
	const char *level_txt = nullptr;
	switch (level) {
	case LogLevel::Debug:
		level_txt = "DEBUG";
		break;
	case LogLevel::Info:
		level_txt = "INFO ";
		break;
	case LogLevel::Warn:
		level_txt = "WARN ";
		break;
	case LogLevel::Error:
		level_txt = "ERROR";
		break;
	}
	const char *ansi_code = "";
#	ifdef __unix__
	constexpr const char *ANSI_DEFAULT = "\x1b[39m";
	int fd = fileno(stderr);
	if (fd >= 0 && isatty(fd)) {
		switch (level) {
		case LogLevel::Debug:
			ansi_code = "\x1b[34m";
			break;
		case LogLevel::Info:
			ansi_code = "\x1b[32m";
			break;
		case LogLevel::Warn:
			ansi_code = "\x1b[33m";
			break;
		case LogLevel::Error:
			ansi_code = "\x1b[31m";
			break;
		}
	}
#	else
	constexpr const char *ANSI_DEFAULT = "";
#	endif // __unix__
	if (level >= MIN_LOG_LEVEL) {
		auto user_string = std::format(fmt, std::forward<Args>(args)...);
		auto log_string = std::format("[{}{}{} {}]: {}\n", ansi_code, level_txt, ANSI_DEFAULT, location, user_string);
		fputs(log_string.c_str(), stderr);
	}
}

class Logger {
private:
	std::string_view _location;

public:
	constexpr Logger(std::string_view location) noexcept : _location{location} {}

	template<class... Args>
	auto d(std::format_string<Args...> fmt, Args&&... args)
	{
		_log(LogLevel::Debug, _location, std::move(fmt), std::forward<Args>(args)...);
	}

	template<class... Args>
	auto i(std::format_string<Args...> fmt, Args&&... args)
	{
		_log(LogLevel::Info, _location, std::move(fmt), std::forward<Args>(args)...);
	}

	template<class... Args>
	auto w(std::format_string<Args...> fmt, Args&&... args)
	{
		_log(LogLevel::Warn, _location, std::move(fmt), std::forward<Args>(args)...);
	}

	template<class... Args>
	auto e(std::format_string<Args...> fmt, Args&&... args)
	{
		_log(LogLevel::Error, _location, std::move(fmt), std::forward<Args>(args)...);
	}
};

} // namespace mal
