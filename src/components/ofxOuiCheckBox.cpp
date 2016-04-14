/*
 * ofxOuiCheckBox.cpp
 *
 * Checkbox component (well... a button with an icon)
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

#include "ofxOuiCheckBox.hpp"

ofxOui::CheckBox::CheckBox(int x_, int y_, int width_, int height_)
    : ofxOui::Button(x_, y_, width_, height_) {
    type_ = ofxOui::Type::CheckBox;
    toggle = true;
    icon.load("check.png");
    icon.alignment = ofxOui::Anchor::MiddleLeft;
}

ofxOui::CheckBox::~CheckBox() {}

void ofxOui::CheckBox::drawIcon() {
    ofSetColor(font.color);
    ofNoFill();
    ofSetLineWidth(4);
    ofDrawRectRounded(icon.rect.x, icon.rect.y, icon.rect.width,
                      icon.rect.height, icon.rect.width / 4);
    if (active) ofxOui::Button::drawIcon();
}
