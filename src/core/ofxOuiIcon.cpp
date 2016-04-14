/*
 * ofxOuiIcon.cpp
 *
 * Jui Icon Box (Wrapper around ofImage)
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

#include "ofxOuiIcon.hpp"

ofxOui::Icon::Icon() {}

ofxOui::Icon::~Icon() {}

void ofxOui::Icon::update() {
    if (!icon_.isAllocated()) return;
    float widthRatio = icon_.getWidth() / float(width - 2 * padding);
    float heightRatio = icon_.getHeight() / float(height - 2 * padding);
    if (widthRatio > heightRatio) {
        rect.width = min(width - 2 * padding, int(icon_.getWidth()));
        rect.height = int(rect.width * icon_.getHeight() / icon_.getWidth());
    } else {
        rect.height = min(height - 2 * padding, int(icon_.getHeight()));
        rect.width = int(rect.height * icon_.getWidth() / icon_.getHeight());
    }
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

void ofxOui::Icon::draw() {
    if (!icon_.isAllocated()) return;
    ofSetColor(color);
    icon_.draw(ofPoint(rect.x, rect.y), rect.width, rect.height);
}

void ofxOui::Icon::load(string filename) { icon_.load(filename); }
