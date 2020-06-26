#pragma once

#include <cstdlib>

namespace SystemBinder {
    class System {
        public:
            explicit System() {}

            std::string GetEnv(std::string env_var) {
                return std::string(getenv( env_var.c_str() ));
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
            }
    };
}

