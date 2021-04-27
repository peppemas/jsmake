#pragma once

#include <linenoise.h>

namespace TerminalBinder {

    class Terminal {
    private:
        char* m_line = 0;

    public:
        explicit Terminal() {}

        void SetMultiline(bool value) {
            linenoiseSetMultiLine(value);
        }

        void PrintKeycodes() {
            linenoisePrintKeyCodes();
        }

        std::string Prompt(std::string prompt) {
            if (m_line != nullptr) linenoiseFree(m_line);
            m_line = linenoise(prompt.c_str());
            return std::string(m_line);
        }

        void HistoryAdd(std::string value) {
            linenoiseHistoryAdd(value.c_str());
        }

        void ClearScreen() {
            linenoiseClearScreen();
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template <class Inspector>
        static void inspect(Inspector &i)
        {
            i.construct(&std::make_shared<Terminal>);
            i.method("multiline", &Terminal::SetMultiline);
            i.method("printKeyCodes", &Terminal::PrintKeycodes);
            i.method("historyAdd", &Terminal::HistoryAdd);
            i.method("prompt", &Terminal::Prompt);
            i.method("clearScreen",&Terminal::ClearScreen);
        }

    };

}
