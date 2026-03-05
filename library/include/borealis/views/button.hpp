/*
    Copyright 2019-2021 natinusala
    Copyright 2019 p-sam

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <borealis/core/bind.hpp>
#include <borealis/core/box.hpp>
#include <borealis/views/label.hpp>

namespace brls
{

// Style and colors of different buttons styles
// Border color entries can be empty if thickness is 0
// Highlight padding can be empty
// Background color entries can be empty
// Border thickness can be empty
// The rest is mandatory
typedef struct ButtonStyle
{
    // Regular values
    ShadowType shadowType;
    bool hideHighlightBackground;

    // Style entries
    std::string highlightPadding;
    std::string borderThickness;

    // Theme entries
    std::string enabledBackgroundColor;
    std::string enabledLabelColor;
    std::string enabledBorderColor;

    std::string disabledBackgroundColor;
    std::string disabledLabelColor;
    std::string disabledBorderColor;
} ButtonStyle;

// primary action button (different background color than default, to catch the eye)
inline const ButtonStyle BUTTONSTYLE_PRIMARY = {
    ShadowType::GENERIC, // shadowType
    true, // hideHighlightBackground

    "brls/button/primary_highlight_padding", // highlightPadding
    "", // borderThickness

    "brls/button/primary_enabled_background", // enabledBackgroundColor
    "brls/button/primary_enabled_text", // enabledLabelColor
    "", // enabledBorderColor

    "brls/button/primary_disabled_background", // disabledBackgroundColor
    "brls/button/primary_disabled_text", // disabledLabelColor
    "", // disabledBorderColor
};

// between primary and default - text color is different, background color is the same
inline const ButtonStyle BUTTONSTYLE_HIGHLIGHT = {
    ShadowType::GENERIC, // shadowType
    true, // hideHighlightBackground

    "", // highlightPadding
    "", // borderThickness

    "brls/button/default_enabled_background", // enabledBackgroundColor
    "brls/button/highlight_enabled_text", // enabledLabelColor
    "", // enabledBorderColor

    "brls/button/default_disabled_background", // disabledBackgroundColor
    "brls/button/highlight_disabled_text", // disabledLabelColor
    "", // disabledBorderColor
};

// default, plain button
inline const ButtonStyle BUTTONSTYLE_DEFAULT = {
    ShadowType::GENERIC, // shadowType
    true, // hideHighlightBackground

    "", // highlightPadding
    "", // borderThickness

    "brls/button/default_enabled_background", // enabledBackgroundColor
    "brls/button/default_enabled_text", // enabledLabelColor
    "", // enabledBorderColor

    "brls/button/default_disabled_background", // disabledBackgroundColor
    "brls/button/default_disabled_text", // disabledLabelColor
    "", // disabledBorderColor
};

// text and a border
inline const ButtonStyle BUTTONSTYLE_BORDERED = {
    ShadowType::NONE, // shadowType
    false, // hideHighlightBackground

    "", // highlightPadding
    "brls/button/border_thickness", // borderThickness

    "", // enabledBackgroundColor
    "brls/button/default_enabled_text", // enabledLabelColor
    "brls/button/enabled_border_color", // enabledBorderColor

    "", // disabledBackgroundColor
    "brls/button/default_disabled_text", // disabledLabelColor
    "brls/button/disabled_border_color", // disabledBorderColor
};

// only text
inline const ButtonStyle BUTTONSTYLE_BORDERLESS = {
    ShadowType::NONE, // shadowType
    false, // hideHighlightBackground

    "", // highlightPadding
    "", // borderThickness

    "", // enabledBackgroundColor
    "brls/button/default_enabled_text", // enabledLabelColor
    "", // enabledBorderColor

    "", // disabledBackgroundColor
    "brls/button/default_disabled_text", // disabledLabelColor
    "", // disabledBorderColor
};

enum class ButtonState
{
    ENABLED = 0, // the user can select and click on the button
    DISABLED, // the user can select but not click on the button (greyed out)
};

// A button
class Button : public Box
{
  public:
    Button();

    void onFocusGained() override;
    void onFocusLost() override;

    static View* create();

    /**
     * Sets the style of the button. can be a pointer to one of the
     * BUTTONSTYLE constants or any other user created style.
     */
    void setStyle(const ButtonStyle* style);

    /**
     * Sets the state of the button.
     */
    void setState(ButtonState state);

    /**
     * Sets the text of the button. 
     */
    void setText(std::string text);

    /**
     * Sets the font sise of the button.
     */
    void setFontSize(float value);

    /**
     * Override style text color of the button.
     */
    void setTextColor(NVGcolor color);

    /**
     * Returns the text of the button
     */
    std::string getText();

  private:
    const ButtonStyle* style = &BUTTONSTYLE_DEFAULT;
    ButtonState state        = ButtonState::ENABLED;

    NVGcolor textColor;
    bool textColorOverritten = false;

    void applyStyle();

    BRLS_BIND(Label, label, "brls/button/label");
};

} // namespace brls
