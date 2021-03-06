#pragma once

//Related header(class.h, class.cpp)

//C system headers
#include <stdio.h>

//C++ standard library headers
#include <string>

//other libraries' headers
#define FMT_HEADER_ONLY
#include <fmt/core.h>

//your project's headers.


namespace hack {

	std::string vFormat(fmt::string_view format_str, fmt::format_args args);

	template<typename ... Args>
	std::string Format(const std::string& formatString, const Args& ... args) {
		fmt::format_arg_store<fmt::format_context, Args...> as{ args... };
		return hack::vFormat(formatString, as);
	}

	template<typename... Args>
	void Log(const std::string& format, const Args&... args) {

		std::string str = hack::Format(format, args...) + "\n";
		printf("%s", str.c_str());

	}

}