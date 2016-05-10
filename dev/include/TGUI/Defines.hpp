/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_DEFINES_HPP
#define TGUI_DEFINES_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include <TGUI/Config.hpp>
#include <TGUI/Borders.hpp>

#include <TGUI/TextureManager.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_OUTPUT
    #define TGUI_OUTPUT(x)   sf::err() << x << std::endl;
#endif

#define TGUI_MINIMUM(x, y)   (x < y) ? x : y

#define TGUI_MAXIMUM(x, y)   (x > y) ? x : y

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    std::string to_string(T value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    enum WidgetPhase
    {
        WidgetPhase_Hover     = 1,
        WidgetPhase_MouseDown = 2,
        WidgetPhase_Focused   = 4,
        WidgetPhase_Selected  = 8
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief A list of all widget types.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum WidgetTypes
    {
        Type_Unknown,
        Type_ClickableWidget,
        Type_Picture,
        Type_Button,
        Type_Checkbox,
        Type_RadioButton,
        Type_Label,
        Type_EditBox,
        Type_ListBox,
        Type_ComboBox,
        Type_Slider,
        Type_Scrollbar,
        Type_LoadingBar,
        Type_TextBox,
        Type_SpriteSheet,
        Type_AnimatedPicture,
        Type_SpinButton,
        Type_Slider2d,
        Type_Tab,
        Type_MenuBar,
        Type_ChatBox,
        Type_Knob,
        Type_Panel,
        Type_ChildWindow,
        Type_Grid,
        Type_MessageBox
    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief While tab key usage is enabled (default), pressing tab will focus another widget.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void enableTabKeyUsage();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief When disabling the tab key usage, pressing tab will no longer focus another widget.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void disableTabKeyUsage();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Set a new resource path.
    ///
    /// This pathname is placed in front of every filename that is used to load a resource.
    ///
    /// \param path  New resource path
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void setResourcePath(const std::string& path);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Return the resource path.
    ///
    /// This pathname is placed in front of every filename that is used to load a resource.
    ///
    /// \return The current resource path
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API const std::string& getResourcePath();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /// \internal The texture manager will not just load the textures, but will also make sure that the textures are only loaded once.
    extern TGUI_API TextureManager TGUI_TextureManager;

    /// \internal The internal clipboard that widgets use
    class Clipboard;
    extern TGUI_API Clipboard TGUI_Clipboard;

    /// \internal When disabling the tab key usage, pressing tab will no longer focus another widget.
    extern TGUI_API bool TGUI_TabKeyUsageEnabled;

    /// \internal The resource path is added in front of every filename that is used to load a resource.
    extern TGUI_API std::string TGUI_ResourcePath;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Get a sf::Color from a string. The string must look like: "(r, g, b)" or "(r, g, b, a)".
    // When this function fails then it will return black.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API sf::Color extractColor(std::string string);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // This function does exactly the opposite of extractColor.
    // The returned string will be "(r,g,b)" when a=255 or "(r,g,b,a)" when a<255.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API std::string convertColorToString(const sf::Color& color);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Get a sf::Vector2f from a string. The string must look like: "(x, y)".
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool extractVector2f(std::string string, sf::Vector2f& vector);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Get a sf::Vector2u from a string. The string must look like: "(x, y)".
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool extractVector2u(std::string string, sf::Vector2u& vector);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Get a tgui::Borders from a string. The string must look like: "(left, top, right, bottom)".
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool extractBorders(std::string string, Borders& borders);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Converts a string containing e.g. newlines and tabs into a compact string.
    // The original string can be obtained by callig the decodeString on the resulting string.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void encodeString(const std::string& origString, std::string& encodedString);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Converts an encoded string back into the original string.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void decodeString(const std::string& encodedString, std::string& decodedString);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Turns a list of strings into a string. Use the decodeList function to get the list back.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void encodeList(const std::vector<sf::String>& list, std::string& encodedString);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Turns a list of strings into a string. Use the decodeList function to get the list back.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API void decodeList(const std::string& encodedString, std::vector<sf::String>& list);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \internal
    // Converts a string to lowercase.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string toLower(std::string str);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_DEFINES_HPP

