/*
 * ofxCuiCuiButton.cpp
 *
 * Button component (with toggle mode)
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

#include "ofxCuiCuiButton.hpp"

ofxCuiCui::Button::Button(int x_, int y_, int width_, int height_)
    : ofxCuiCui::Component(x_, y_, width_, height_),
      toggle(false),
      click_event_callback_(nullptr) {
    type_ = ofxCuiCui::Type::Button;
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxCuiCui::Button::mousePressed);
}

ofxCuiCui::Button::~Button() {
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxCuiCui::Button::mousePressed);
}

void ofxCuiCui::Button::update() {
    ofxCuiCui::Component::update();
    if (!toggle && !ofGetMousePressed()) {
        if (num_frames_on_ > 0)
            num_frames_on_--;
        else
            active = false;
    }
}

void ofxCuiCui::Button::mousePressed(ofMouseEventArgs& e) {
    if (disabled) return;
    if (inside(e.x, e.y) && e.button == 0) {
        if (toggle) {
            active = !active;
        } else {
            active = true;
            num_frames_on_ = 5;
        }
        if (click_event_callback_ != nullptr) {
            ofxCuiCui::Button::ClickEvent event =
                ofxCuiCui::Button::ClickEvent(this, active);
            click_event_callback_(event);
        }
    }
}

ofxCuiCui::Button::ClickEvent::ClickEvent(ofxCuiCui::Button* sender_,
                                          bool value_)
    : sender(sender_), value(value_) {}
