#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

#include <duktape-cpp/DuktapeCpp.h>
#include <reproc/run.h>

namespace ProcessorBinder {

	class Process {
		public:
			explicit Process() {}

			int Run(std::string str) 
			{
				std::vector<char *> args;
				std::istringstream iss(str);

				std::string token;
				while(iss >> token) {
				  char *arg = new char[token.size() + 1];
				  copy(token.begin(), token.end(), arg);
				  arg[token.size()] = '\0';
				  args.push_back(arg);
				}
				args.push_back(0);

				int result = reproc_run(&args[0], reproc_options{ 0 });
				if (result < 0) {
					std::cout << "ERROR: (" << result << ") " << reproc_strerror(result) << std::endl;
				}

				for(size_t i = 0; i < args.size(); i++)
					delete[] args[i];

				return result;
			}

		    /**
		     * Inspect method defines class meta information (methods, properties etc..)
		     * You can define `inspect` method inline or specialize `duk::Inspect` for your class
		     */
		    template <class Inspector>
		    static void inspect(Inspector &i) 
		    {
		        i.construct(&std::make_shared<Process>);
				i.method("run", &Process::Run);
		    }

	};

}

