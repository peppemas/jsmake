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
			explicit Log() = default;

			inline void Blank() { std::cout << std::endl; }
			inline void Info(std::string str) { std::cout << str << std::endl; }
			inline void Warning(std::string str) { std::cout << termcolor::yellow << str << termcolor::reset << std::endl; }
			inline void Error(std::string str) { std::cout << termcolor::red << str << termcolor::reset << std::endl; }
			inline void Bold(std::string str) { std::cout << termcolor::bold << termcolor::white << str << termcolor::reset << std::endl; }
			inline void Red(std::string str) { std::cout << termcolor::red << str << termcolor::reset; }
            inline void Grey(std::string str) { std::cout << termcolor::grey << str << termcolor::reset; }
            inline void Green(std::string str) { std::cout << termcolor::green << str << termcolor::reset; }
            inline void Yellow(std::string str) { std::cout << termcolor::yellow << str << termcolor::reset; }
            inline void Blue(std::string str) { std::cout << termcolor::blue << str << termcolor::reset; }
            inline void Magenta(std::string str) { std::cout << termcolor::magenta << str << termcolor::reset; }
            inline void Cyan(std::string str) { std::cout << termcolor::cyan << str << termcolor::reset; }
            inline void White(std::string str) { std::cout << termcolor::white << str << termcolor::reset; }
            inline void OnCyan(std::string str) { std::cout << termcolor::on_cyan << str << termcolor::reset; }
            inline void OnGrey(std::string str) { std::cout << termcolor::on_grey << str << termcolor::reset; }
            inline void OnBlue(std::string str) { std::cout << termcolor::on_blue << str << termcolor::reset; }
            inline void OnGreen(std::string str) { std::cout << termcolor::on_green << str << termcolor::reset; }
            inline void OnRed(std::string str) { std::cout << termcolor::on_red << str << termcolor::reset; }

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
		        i.method("red", &Log::Red);
                i.method("grey", &Log::Grey);
                i.method("green", &Log::Green);
                i.method("yellow", &Log::Yellow);
                i.method("blue", &Log::Blue);
                i.method("magenta", &Log::Magenta);
                i.method("cyan", &Log::Cyan);
                i.method("white", &Log::White);
                i.method("oncyan", &Log::OnCyan);
                i.method("ongrey", &Log::OnGrey);
                i.method("onblue", &Log::OnBlue);
                i.method("ongreen", &Log::OnGreen);
                i.method("onred", &Log::OnRed);
		    }

		private:
			std::stringstream ss;	// ansi string stream
	};

}

