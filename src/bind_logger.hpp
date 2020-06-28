#pragma once

#include <memory>

#if defined(__CYGWIN__)
#   undef __STRICT_ANSI__
#   include <iostream>
#   include <sstream>
#   define __STRICT_ANSI__
#else
#   include <iostream>
#   include <sstream>
#endif

#include <duktape-cpp/DuktapeCpp.h>
#include <termcolor/termcolor.hpp>

namespace LoggerBinder {

	class Log {
		public:
			explicit Log() {}

			inline void Blank() { std::cout << std::endl; }
			inline void Info(std::string str) { std::cout << str << std::endl; }
			inline void Warning(std::string str) { std::cout << termcolor::yellow << str << termcolor::reset << std::endl; }
			inline void Error(std::string str) { std::cout << termcolor::red << str << termcolor::reset << std::endl; }
			inline void Bold(std::string str) { std::cout << termcolor::bold << termcolor::white << str << termcolor::reset << std::endl; }

		    /**
		     * Inspect method defines class meta information (methods, properties etc..)
		     * You can define `inspect` method inline or specialize `duk::Inspect` for your class
		     */
		    template <class Inspector>
		    static void inspect(Inspector &i) 
		    {
		        i.construct(&std::make_shared<Log>);
		        i.method("blank", &Log::Blank);
		        i.method("info", &Log::Info);
		        i.method("warn", &Log::Warning); 
		        i.method("error", &Log::Error); 
		        i.method("bold", &Log::Bold); 
		    }

		private:
			std::stringstream ss;	// ansi string stream
	};

}

