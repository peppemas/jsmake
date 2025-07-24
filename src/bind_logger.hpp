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

		void Info(const std::string& str) { std::cout << str << std::endl; }
		void Warning(const std::string& str) { std::cout << termcolor::yellow << str << termcolor::reset << std::endl; }
		void Error(const std::string& str) { std::cout << termcolor::red << str << termcolor::reset << std::endl; }
		void Bold(const std::string& str) { std::cout << termcolor::bold << termcolor::white << str << termcolor::reset << std::endl; }
		void Blank() { std::cout << std::endl; }
		void Red(const std::string& str) { std::cout << termcolor::red << str << termcolor::reset; }
		void Grey(const std::string& str) { std::cout << termcolor::grey << str << termcolor::reset; }
		void Green(const std::string& str) { std::cout << termcolor::green << str << termcolor::reset; }
		void Yellow(const std::string& str) { std::cout << termcolor::yellow << str << termcolor::reset; }
		void Blue(const std::string& str) { std::cout << termcolor::blue << str << termcolor::reset; }
		void Magenta(const std::string& str) { std::cout << termcolor::magenta << str << termcolor::reset; }
		void Cyan(const std::string& str) { std::cout << termcolor::cyan << str << termcolor::reset; }
		void White(const std::string& str) { std::cout << termcolor::white << str << termcolor::reset; }
		void OnCyan(const std::string& str) { std::cout << termcolor::on_cyan << str << termcolor::reset; }
		void OnGrey(const std::string& str) { std::cout << termcolor::on_grey << str << termcolor::reset; }
		void OnBlue(const std::string& str) { std::cout << termcolor::on_blue << str << termcolor::reset; }
		void OnGreen(const std::string& str) { std::cout << termcolor::on_green << str << termcolor::reset; }
		void OnRed(const std::string& str) { std::cout << termcolor::on_red << str << termcolor::reset; }

		/**
			Inspect method defines class meta information (methods, properties etc..)
			You can define `inspect` method inline or specialize `duk::Inspect` for your class
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
			i.method("onCyan", &Log::OnCyan);
			i.method("onGrey", &Log::OnGrey);
			i.method("onBlue", &Log::OnBlue);
			i.method("onGreen", &Log::OnGreen);
			i.method("onRed", &Log::OnRed);
		}

	private:
		std::stringstream ss;	// ansi string stream
	};


}

