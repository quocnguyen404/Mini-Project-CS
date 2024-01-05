#include "main/example_glfw_opengl2/Header/ui.h"

namespace UI
{
    void textAlign(const char* text, float alignment)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(text).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;
        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Text(text);
    }

    bool buttonAlign(const char* label, float alignment)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Button(label);
    }

    void showMainWindow(bool& p_open)
    {

        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

        //Main body
        if (!ImGui::Begin("BKEncyclopedia"), p_open)
        {
            textAlign("BKEncyclopedia", 0.5f);

            ImGui::End();
            return;
        }
    }

    void showMessageWindow(bool& p_open, std::vector<std::string> mess)
    {
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

        if (!ImGui::Begin("Message Window"), p_open)
        {
            textAlign("Message", 0.5f);

            for (std::string& m : mess)
                textAlign(m.c_str(), 0.5f);


            ImGui::End();
            return;
        }
    }
}
