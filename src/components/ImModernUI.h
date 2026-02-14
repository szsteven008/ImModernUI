#pragma once

#include "themes.h"
namespace ImModernUI {
    void Init(float font_size, UIThemeScheme scheme = UIThemeScheme::Light, 
        UIThemeBaseColor base_color = UIThemeBaseColor::Netrual);
    void UnInit();
    
    void ShowImModernUIDemo(bool& open);
}