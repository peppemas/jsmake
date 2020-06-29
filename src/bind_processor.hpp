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
	    private:
	        std::string m_output;
	        std::string m_error;
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

				char* output = NULL;
                reproc_sink sinkOut = reproc_sink_string(&output);

				int result = reproc_run_ex(&args[0], reproc_options{ 0 }, sinkOut, sinkOut);
				if (result < 0) {
				    m_error = std::string(reproc_strerror(result));
					std::cout << "ERROR (" << result << "): " << m_error << std::endl;
				} else {
                    std::cout << output << std::endl;
				}

				if (output) m_output = std::string(output);
                reproc_free(output);

                for(size_t i = 0; i < args.size(); i++)
					delete[] args[i];

				return result;
			}

			std::string GetOutput()
            {
			    return m_output;
            }

            std::string GetError()
            {
			    return m_error;
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
				i.method("getOutput", &Process::GetOutput);
				i.method("getError", &Process::GetError);
		    }

	};

}

