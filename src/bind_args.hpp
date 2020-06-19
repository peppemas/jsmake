#include <argparse.h>

namespace ArgsEngine {

    class Args {
    private:
        std::vector<const char *> args;
        struct argparse argparse;

    public:
        explicit Args() {}

        void SetCommandLine(const char *cmdline) {
            std::cout << "Set Command Line " << cmdline << std::endl;

            std::string cmd(cmdline);
            std::istringstream iss(cmd);

            std::string token;
            while (iss >> token) {
                char *arg = new char[token.size() + 1];
                copy(token.begin(), token.end(), arg);
                arg[token.size()] = '\0';
                args.push_back(arg);
            }
            args.push_back(0);

            std::cout << "argc " << args.size() << std::endl;
            for (size_t i = 0; i < args.size(); i++) std::cout << args[i] << std::endl;
        }

        void AddOption(char optShort, std::string optLong, std::string description)
        {
            /*
            argparse_option option;
            argparse_js_option jsOption;

            option.type = ARGPARSE_OPT_STRING;
            option.value = (void *) jsOption.value;
            option.short_name = optShort;
            option.long_name = optLong.c_str();
            option.help = description.c_str();
            jsOption.option = option;

            options.push_back(jsOption);
            */
        }

        void Parse() {
            /*
            std::vector<argparse_option *> tmpOptions;
            for (size_t i = 0; i < options.size(); i++) tmpOptions.push_back(options[i].option);

            argparse_init(&argparse, tmpOptions[0], 0, 0);
            argparse_parse(&argparse, (int)args.size(), &args[0]);
             */
        }

        void GetOption(char optShort, std::string optLong, std::string description)
        {
            const char *option_value;
            struct argparse_option options[] = {
                    OPT_STRING(optShort, optLong.c_str(), &option_value, description.c_str(), NULL, 0, 0),
                    OPT_END()
            };
            argparse_init(&argparse, options, 0, 0);
            argparse_parse(&argparse, (int)args.size(), &args[0]);
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template<class Inspector>
        static void inspect(Inspector &i) {
            i.construct(&std::make_shared<Args>);
        }
    };

}