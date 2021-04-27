//
// Created by giuse on 4/27/2021.
//

#ifndef JSMAKE_BIND_FTXUI_HPP
#define JSMAKE_BIND_FTXUI_HPP

namespace FTXUIBinder {

    class UI {
    public:
        explicit UI() = default;

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template<class Inspector>
        static void inspect(Inspector &i) {
            i.construct(&std::make_shared < UI > );
        }

    private:

    };

}

#endif //JSMAKE_BIND_FTXUI_HPP
