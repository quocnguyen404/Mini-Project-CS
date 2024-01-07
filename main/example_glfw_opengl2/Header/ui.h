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
#include <vector>

namespace UI
{
    void textAlign(const char* text, float alignment);
    bool buttonAlign(const char* label, float alignment);
}
