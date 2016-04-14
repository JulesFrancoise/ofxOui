/*
 * ofxOuiButton.cpp
 *
 * Button component (with toggle mode)
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

#include "ofxOuiButton.hpp"

ofxOui::Button::Button(int x_, int y_, int width_, int height_)
    : ofxOui::Component(x_, y_, width_, height_),
      toggle(false),
      click_event_callback_(nullptr) {
    type_ = ofxOui::Type::Button;
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxOui::Button::mousePressed);
}

ofxOui::Button::~Button() {
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxOui::Button::mousePressed);
}

void ofxOui::Button::update() {
    ofxOui::Component::update();
    if (!toggle && !ofGetMousePressed()) {
        if (num_frames_on_ > 0)
            num_frames_on_--;
        else
            active = false;
    }
}

void ofxOui::Button::mousePressed(ofMouseEventArgs& e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (inside(e.x, e.y) && e.button == 0) {
        if (toggle) {
            active = !active;
        } else {
            active = true;
            num_frames_on_ = 5;
        }
        if (click_event_callback_ != nullptr) {
            ofxOui::Button::ClickEvent event(this, active);
            click_event_callback_(event);
        }
    }
}

ofxOui::Button::ClickEvent::ClickEvent(ofxOui::Button* sender_,
                                          bool value_)
    : sender(sender_), value(value_) {}
