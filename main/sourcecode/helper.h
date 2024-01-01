#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>
#include <string>

using std::string;


namespace Helper
{



    void TextAlign(const char* text, float alignment);
    bool ButtonAlign(const char* label, float alignment);
    void ShowMainWindow(bool& p_open);
    void ShowCreateClass(bool& p_open);
    void ShowAddStudent(bool& p_open);

}
