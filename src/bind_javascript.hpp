#pragma once

#include "bind_filesystem.hpp"

namespace JavascriptBinder {

    class Javascript {

    private:
        duk::Context* m_ctx;
        std::shared_ptr<FileSystemBinder::Directory> m_directory;

    public:
        explicit Javascript() {}

        // called from CPP only
        void Initialize(duk::Context* ctx) {
            m_ctx = ctx;
            m_ctx->getGlobal("Directory", m_directory);
            assert(m_directory);
        }

        int Include(std::string filename) {
            if (m_ctx) {
                std::string script = m_directory->ReadTextFile(filename);
                m_ctx->evalStringNoRes(script.c_str());
            }
            return 0;
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template <class Inspector>
        static void inspect(Inspector &i)
        {
            i.construct(&std::make_shared<Javascript>);
            i.method("include", &Javascript::Include);
        }

    };

}