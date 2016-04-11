/*
 * ofxCuiCuiTextBox.hpp
 *
 * Text Box (Wrapper around ofTrueTypeFont)
 *
 * This code has been authored by Jules Francoise <jfrancoi@sfu.ca>
 * during his postdoc contract at Simon Fraser University (MovingStories
 * project).
 * See:
 *    http://julesfrancoise.com/
 *    http://movingstories.ca/
 *
 * Copyright (C) 2016 Jules Francoise.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef ofxCuiCuiText_hpp
#define ofxCuiCuiText_hpp

#include "ofxCuiCuiCommon.hpp"

namespace ofxCuiCui {

/**
 @ingroup core
 @brief Text box font wrapper
 */
class TextBox {
  public:
    /**
     @brief Default Constructor
     */
    TextBox();

    /**
     @brief Destructor
     */
    virtual ~TextBox();

    /**
     @brief OF-like update function: updates the position of the icon
     */
    virtual void update();

    /**
     @brief OF-like draw function: draws the text box
     */
    virtual void draw();

    /**
     @brief get the path to the font path
     @return the path to the font path
     */
    virtual string getFontPath() const;

    /**
     @brief set the path to the font path
     @param path the path to the font path
     */
    virtual void setFontPath(string path);

    /**
     @brief get the font size
     @return the font size
     */
    virtual float getFontSize() const;

    /**
     @brief set the font size
     @param size the font size
     */
    virtual void setFontSize(float size);

    /**
     @brief get the letter spacing
     @return the letter spacing
     */
    virtual float getLetterSpacing() const;

    /**
     @brief set the letter spacing
     @param letter_spacing the letter spacing
     */
    virtual void setLetterSpacing(float letter_spacing);

    /**
     @brief get the line height
     @return the line height
     */
    virtual float getLineHeight() const;

    /**
     @brief set the line height
     @param line_height the line height
     */
    virtual void setLineHeight(float line_height);

    /**
     @brief get the index of the character at a given mouse position
     @param x_ x mouse position
     @param y_ y mouse position
     @return character index
     */
    virtual int getCharacterIndex(int x_, int y_) const;

    /**
     @brief get the index of the cursor (inter-character) at a given mouse
     position
     @param x_ x mouse position
     @param y_ y mouse position
     @return character index
     */
    virtual int getCursorIndex(int x_, int y_) const;

    /**
     @brief label
     */
    string text = "";

    /**
     @brief x position (of the containing box)
     */
    int x = 0;

    /**
     @brief y position (of the containing box)
     */
    int y = 0;

    /**
     @brief width (of the containing box)
     */
    int width = 100;

    /**
     @brief height (of the containing box)
     */
    int height = 100;

    /**
     @brief padding (within the containing box)
     */
    int padding = 10;

    /**
     @brief Alignment
     */
    Anchor alignment = ofxCuiCui::Anchor::MiddleCenter;

    /**
     @brief Color (in case of a binary icon)
     */
    ofColor color = ofColor::black;

    /**
     @brief Actual rectangle where the text is drawn
     */
    ofRectangle rect;

  protected:
    virtual void adjustFont_();

    ofTrueTypeFont* base_Font_;
    string font_path_;
    float font_size_;
    float line_height_;
    float letter_spacing_ = 1.;
    int y_diff_;
};
}

#endif
