/*
 * ofxCuiCuiCheckBox.cpp
 *
 * Checkbox component (well... a button with an icon)
 *
 * This code has been authored by Jules Françoise <jfrancoi@sfu.ca>
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

#include "ofxCuiCuiCheckBox.hpp"

ofxCuiCui::CheckBox::CheckBox(int x_, int y_, int width_, int height_)
    : ofxCuiCui::Button(x_, y_, width_, height_) {
    type_ = ofxCuiCui::Type::CheckBox;
    toggle = true;
    icon.load("check.png");
    icon.alignment = ofxCuiCui::Anchor::MiddleLeft;
}

ofxCuiCui::CheckBox::~CheckBox() {}

void ofxCuiCui::CheckBox::drawIcon() {
    ofSetColor(font.color);
    ofNoFill();
    ofSetLineWidth(4);
    ofDrawRectRounded(icon.rect.x, icon.rect.y, icon.rect.width,
                      icon.rect.height, icon.rect.width / 4);
    if (active) ofxCuiCui::Button::drawIcon();
}
