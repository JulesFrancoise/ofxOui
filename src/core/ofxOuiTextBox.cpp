/*
 * ofxOuiTextBox.cpp
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

#include "ofxOuiTextBox.hpp"

#pragma mark -
#pragma mark ofxOuiText
ofxOui::TextBox::TextBox()
    : font_path_(ofxOui::Globals::getDefaultFontPath()),
      font_size_(ofxOui::Globals::getDefaultFontSize()),
      line_height_(ofxOui::Globals::getDefaultLineHeight()) {
    adjustFont_();
}

ofxOui::TextBox::~TextBox() { ofxOui::Globals::releaseFont(this); }

void ofxOui::TextBox::update() {
    if (text.empty()) {
        rect.x = x;
        rect.y = y;
        rect.width = 0;
        rect.height = 0;
    } else {
        rect = base_Font_->getStringBoundingBox(text, x, y);
        y_diff_ = y - rect.y;
        if (alignment == ofxOui::Anchor::TopLeft) {
            rect.x = x + padding;
            rect.y = y + padding;
        } else if (alignment == ofxOui::Anchor::TopCenter) {
            rect.x = x + width / 2 - rect.width / 2;
            rect.y = y + padding;
        } else if (alignment == ofxOui::Anchor::TopRight) {
            rect.x = x + width - padding - rect.width;
            rect.y = y + padding;
        } else if (alignment == ofxOui::Anchor::MiddleLeft) {
            rect.x = x + padding;
            rect.y = y + height / 2 - rect.height / 2;
        } else if (alignment == ofxOui::Anchor::MiddleCenter) {
            rect.x = x + width / 2 - rect.width / 2;
            rect.y = y + height / 2 - rect.height / 2;
        } else if (alignment == ofxOui::Anchor::MiddleRight) {
            rect.x = x + width - padding - rect.width;
            rect.y = y + height / 2 - rect.height / 2;
        } else if (alignment == ofxOui::Anchor::BottomLeft) {
            rect.x = x + padding;
            rect.y = y + height - padding - rect.height;
        } else if (alignment == ofxOui::Anchor::BottomCenter) {
            rect.x = x + width / 2 - rect.width / 2;
            rect.y = y + height - padding - rect.height;
        } else {  // (alignment == ofxOui::Anchor::BottomRight)
            rect.x = x + width - padding - rect.width;
            rect.y = y + height - padding - rect.height;
        }
    }
}

void ofxOui::TextBox::draw() {
    if (text.empty()) return;
    ofSetColor(color);
    base_Font_->drawString(text, rect.x, rect.y + y_diff_);
}

string ofxOui::TextBox::getFontPath() const { return font_path_; }

void ofxOui::TextBox::setFontPath(string path) {
    font_path_ = path;
    adjustFont_();
}

float ofxOui::TextBox::getFontSize() const { return font_size_; }

void ofxOui::TextBox::setFontSize(float size) {
    font_size_ = size;
    adjustFont_();
}

float ofxOui::TextBox::getLetterSpacing() const { return letter_spacing_; }

void ofxOui::TextBox::setLetterSpacing(float letter_spacing) {
    letter_spacing_ = letter_spacing;
    adjustFont_();
}

float ofxOui::TextBox::getLineHeight() const { return line_height_; }

void ofxOui::TextBox::setLineHeight(float line_height) {
    line_height_ = line_height;
    adjustFont_();
}

void ofxOui::TextBox::adjustFont_() {
    base_Font_ = ofxOui::Globals::requestFont(this, font_path_, font_size_,
                                              line_height_, letter_spacing_);
}

int ofxOui::TextBox::getCharacterIndex(int x_, int y_) const {
    if (x_ < rect.x || x_ > rect.x + rect.width || y_ < rect.y ||
        y_ > rect.y + rect.height)
        return -1;
    string tmpText;
    for (int characterPressedIndex = 0; characterPressedIndex < text.size();
         characterPressedIndex++) {
        tmpText += text[characterPressedIndex];
        ofRectangle tmpRect(base_Font_->getStringBoundingBox(
            tmpText, rect.x, rect.y + rect.height));
        if (x_ <= tmpRect.x + tmpRect.width) return characterPressedIndex;
    }
}

int ofxOui::TextBox::getCursorIndex(int x_, int y_) const {
    if (x_ < rect.x || x_ > rect.x + rect.width || y_ < rect.y ||
        y_ > rect.y + rect.height)
        return -1;
    string tmpText;
    for (int cursorPressedIndex = 0; cursorPressedIndex < text.size();
         cursorPressedIndex++) {
        tmpText += text[cursorPressedIndex];
        ofRectangle tmpRect(base_Font_->getStringBoundingBox(
            tmpText, rect.x, rect.y + rect.height));
        if (x_ <= tmpRect.x + tmpRect.width / 2) return cursorPressedIndex;
    }
    return text.size();
}
