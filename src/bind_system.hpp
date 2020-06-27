#pragma once

#include <cstdlib>

namespace SystemBinder {
    class System {
        public:
            explicit System() {}

            std::string GetEnv(std::string env_var) {
                return std::string(getenv( env_var.c_str() ));
            }

            void SetEnv(std::string env_var, std::string env_value) {
#if defined(_WIN32)
                _putenv_s(env_var.c_str(), env_value.c_str());
#else
                setenv(env_var.c_str(), env_value.c_str(), true);
#endif
            }

            /**
             * Inspect method defines class meta information (methods, properties etc..)
             * You can define `inspect` method inline or specialize `duk::Inspect` for your class
             */
            template <class Inspector>
            static void inspect(Inspector &i)
            {
                i.construct(&std::make_shared<System>);
                i.method("env", &System::GetEnv);
                i.method("setEnv", &System::SetEnv);
            }
    };
}

