//Related header(class.h, class.cpp)
#include "logger.h"

//C system headers

//C++ standard library headers

//other libraries' headers

//your project's headers.


namespace hack {

	std::string vformat(fmt::string_view format_str, fmt::format_args args)
	{
		return fmt::vformat(format_str, args);
	}

}


