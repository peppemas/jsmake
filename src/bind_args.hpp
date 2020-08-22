#pragma once

namespace ArgsBinder {

    class Args {
    private:
        std::map<std::string, std::string> args;

    public:
        explicit Args() {}

        void addMap(std::string key, std::string value) {
            args[key] = value;
        }

        void SetCommandLine(const char *cmdline) {
            //std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Set Command Line " << cmdline << std::endl;

            std::string cmd(cmdline);
            std::istringstream iss(cmd);

            std::string token;
            std::string key;
            std::string value;
            bool tokenFound = false;
            while (iss >> token) {
                // check if it's an option (starting with "-")
                if (token.rfind("-",0) == 0) {
                    if (tokenFound) {
                        // we already a token found... so the previous one has no parameters
                        addMap(key, "");
                    }
                    // set the new key
                    key = token;
                    tokenFound = true;
                } else {
                    if (tokenFound) {
                        value = token;
                        addMap(key, value);
                        tokenFound = false;
                    } else {
                        // we have a value with a space between... update value of last key
                        value = args[key] + " " + token;
                        addMap(key, value);
                    }
                }
            }

            /*
            std::cout << "argc " << args.size() << std::endl;
            for (std::map<std::string, std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
                std::cout << "Key: " << it->first << " Value: " << it->second << std::endl;
            }
            */
        }

        std::string GetOption(std::string option)
        {
            std::map<std::string,std::string>::iterator it = args.find(option);
            if (it != args.end())
                return it->second;

            return std::string("");
        }

        bool Exists(std::string option)
        {
            std::map<std::string,std::string>::iterator it = args.find(option);
            if (it != args.end())
                return true;
            return false;
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template<class Inspector>
        static void inspect(Inspector &i) {
            i.construct(&std::make_shared<Args>);
            i.method("get", &Args::GetOption);
            i.method("exists", &Args::Exists);
        }
    };

}