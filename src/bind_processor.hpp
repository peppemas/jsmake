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
	        char* m_output = 0;
	        char* m_error = 0;
		public:
			explicit Process() {}

			int Run(std::string str) 
			{
			    if (m_output) free(m_output);
			    if (m_error) free(m_error);

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

                reproc_sink sinkOut = reproc_sink_string(&m_output);
                reproc_sink sinkErr = reproc_sink_string(&m_error); // TODO: seems to not work...

				int result = reproc_run_ex(&args[0], reproc_options{ 0 }, sinkOut, sinkErr);
				if (result < 0) {
					m_error = const_cast<char *>(reproc_strerror(result));
					std::cout << "ERROR (" << result << "): " << m_error << std::endl;
				} else {
                    std::cout << m_output << std::endl;
				}

                for(size_t i = 0; i < args.size(); i++)
					delete[] args[i];

				return result;
			}

			std::string GetOutput()
            {
			    if (m_output != nullptr)
			        return std::string(m_output);

			    return 0;
            }

            std::string GetError()
            {
			    if (m_error != nullptr)
			        return std::string(m_error);

			    return 0;
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

