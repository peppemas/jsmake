#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

#include <duktape-cpp/DuktapeCpp.h>
#include <reproc/run.h>
#include <cstring>

namespace ProcessorBinder {

	class Process {
	    private:
	        std::string m_output;
	        std::string m_error;
		public:
			explicit Process() {}

			int Run(std::string str) 
			{
                std::vector<std::string> tokens;
                std::string current_token;
                bool inside_quotes = false;

                for (char c : str) {
                    if (c == ' ' && !inside_quotes) {
                        if (!current_token.empty()) {
                            tokens.push_back(current_token);
                            current_token.clear();
                        }
                    } else if (c == '\"') {
                        if (inside_quotes) {
                            if (!current_token.empty()) {
                                tokens.push_back(current_token + '\"'); // Include double quotes
                                current_token.clear();
                            }
                            inside_quotes = false;
                        } else {
                            inside_quotes = true;
                            current_token += c;
                        }
                    } else {
                        current_token += c;
                    }
                }

                if (!current_token.empty()) {
                    tokens.push_back(current_token);
                }

                // Create a vector to hold char pointers
                std::vector<char*> args;
                // Convert each std::string to a char* and store in the charPointerVector
                for (const std::string& str : tokens) {
                    char* cstr = new char[str.length() + 1]; // +1 for the null terminator
                    std::strcpy(cstr, str.c_str());
                    args.push_back(cstr);
                }

                /*
                // print the char* vector
                std::cout << "====================" << std::endl;
                for (char* cstr : args) {
                    std::cout << cstr << std::endl;
                }
                std::cout << "====================" << std::endl;
                */

                char* output = nullptr;
                reproc_sink sinkOut = reproc_sink_string(&output);

				int result = reproc_run_ex(&args[0], reproc_options{0} , sinkOut, sinkOut);
				if (result < 0) {
				    m_error = std::string(reproc_strerror(result));
					std::cout << "ERROR (" << result << "): " << m_error << std::endl;
				} else {
                    std::cout << output;
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

