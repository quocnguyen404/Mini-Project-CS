#include "helper.h"

namespace Helper
{


    void TextAlign(const char* text, float alignment)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(text).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;
        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Text(text);
    }

    bool ButtonAlign(const char* label, float alignment)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Button(label);
    }

    void ShowMainWindow(bool& p_open)
    {
        static bool show_create_class = false;
        static bool show_add_student = false;

        if (show_create_class) ShowCreateClass(show_create_class);
        if (show_add_student) ShowAddStudent(show_add_student);

        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

        //Main body
        if (!ImGui::Begin("Student Manager"), p_open)
        {
            TextAlign("Student manager", 0.5f);

            if (ButtonAlign("Create class", 0))
                show_create_class = true;


            ImGui::End();
            return;
        }
    }


    void ShowCreateClass(bool& p_open)
    {
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

        if (!ImGui::Begin("Create class"), p_open)
        {



            ImGui::End();
            return;
        }

    }

    void ShowAddStudent(bool& p_open)
    {

    }
}
