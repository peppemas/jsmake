
#include <imtui/imtui.h>
#include <imtui/imtui-impl-text.h>
#include <imgui.h>

namespace GUIBinder {

    class GUI {
    private:
        ImTui::TScreen * g_screen = nullptr;
        bool demo = true;
        int nframes = 0;
        float fval = 1.23f;

    public:
        explicit GUI() {}

        void Init()
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            g_screen = new ImTui::TScreen();
            ImGui::GetIO().KeyMap[ImGuiKey_Tab]         = 9;
            ImGui::GetIO().KeyMap[ImGuiKey_LeftArrow]   = 37;
            ImGui::GetIO().KeyMap[ImGuiKey_RightArrow]  = 39;
            ImGui::GetIO().KeyMap[ImGuiKey_UpArrow]     = 38;
            ImGui::GetIO().KeyMap[ImGuiKey_DownArrow]   = 40;
            ImGui::GetIO().KeyMap[ImGuiKey_PageUp]      = 33;
            ImGui::GetIO().KeyMap[ImGuiKey_PageDown]    = 34;
            ImGui::GetIO().KeyMap[ImGuiKey_Home]        = 36;
            ImGui::GetIO().KeyMap[ImGuiKey_End]         = 35;
            ImGui::GetIO().KeyMap[ImGuiKey_Insert]      = 45;
            ImGui::GetIO().KeyMap[ImGuiKey_Delete]      = 46;
            ImGui::GetIO().KeyMap[ImGuiKey_Backspace]   = 8;
            ImGui::GetIO().KeyMap[ImGuiKey_Space]       = 32;
            ImGui::GetIO().KeyMap[ImGuiKey_Enter]       = 13;
            ImGui::GetIO().KeyMap[ImGuiKey_Escape]      = 27;
            ImGui::GetIO().KeyMap[ImGuiKey_KeyPadEnter] = 13;
            ImGui::GetIO().KeyMap[ImGuiKey_A]           = 1;
            ImGui::GetIO().KeyMap[ImGuiKey_C]           = 2;
            ImGui::GetIO().KeyMap[ImGuiKey_V]           = 2;
            ImGui::GetIO().KeyMap[ImGuiKey_X]           = 3;
            ImGui::GetIO().KeyMap[ImGuiKey_Y]           = 4;
            ImGui::GetIO().KeyMap[ImGuiKey_Z]           = 5;

            ImGui::GetIO().DisplaySize.x = 80;
            ImGui::GetIO().DisplaySize.y = 25;

            ImTui_ImplText_Init();
        }

        void NewFrame()
        {
            ImTui_ImplText_NewFrame();
            ImGui::NewFrame();
        }

        void Render()
        {
            if (g_screen) {
                ImGui::Render();
                ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), g_screen);
            }
        }

        void Shutdown()
        {
            ImTui_ImplText_Shutdown();
            if (g_screen) {
                delete g_screen;
            }
            g_screen = nullptr;
            //TODO ImTui_ImplNcurses_Shutdown();
        }

        void Test() {
            ImGui::SetNextWindowPos(ImVec2(4, 2), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(50.0, 10.0), ImGuiCond_Once);
            ImGui::Begin("Hello, world!");
            ImGui::Text("NFrames = %d", nframes++);
            ImGui::Text("Mouse Pos : x = %g, y = %g", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
            ImGui::Text("Time per frame %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Float:");
            ImGui::SameLine();
            ImGui::SliderFloat("##float", &fval, 0.0f, 10.0f);
            ImGui::End();
        }

        /**
         * Inspect method defines class meta information (methods, properties etc..)
         * You can define `inspect` method inline or specialize `duk::Inspect` for your class
         */
        template<class Inspector>
        static void inspect(Inspector &i) {
            i.construct(&std::make_shared<GUI>);
            i.method("init", &GUI::Init);
            i.method("newFrame",&GUI::NewFrame);
            i.method("render",&GUI::Render);
            i.method("shutdown",&GUI::Shutdown);

            i.method("test",&GUI::Test);
        }
    };

}
