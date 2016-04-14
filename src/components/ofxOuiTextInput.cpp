/*
 * ofxOuiTextInput.cpp
 *
 * Text Input Element (single-line text I guess...)
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

#include "ofxOuiTextInput.hpp"

ofxOui::TextInput::TextInput(int x_, int y_, int width_, int height_)
    : ofxOui::Component(x_, y_, width_, height_),
      erase_on_next_input_(false) {
    type_ = ofxOui::Type::TextInput;
    ofAddListener(ofEvents().mouseMoved, this,
                  &ofxOui::TextInput::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxOui::TextInput::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxOui::TextInput::mouseReleased);
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxOui::TextInput::mouseDragged);
    ofAddListener(ofEvents().keyPressed, this,
                  &ofxOui::TextInput::keyPressed);
}

ofxOui::TextInput::~TextInput() {
    ofRemoveListener(ofEvents().mouseMoved, this,
                     &ofxOui::TextInput::mouseMoved);
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxOui::TextInput::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxOui::TextInput::mouseReleased);
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxOui::TextInput::mouseDragged);
    ofRemoveListener(ofEvents().keyPressed, this,
                     &ofxOui::TextInput::keyPressed);
}

void ofxOui::TextInput::drawLabel() {
    if (active) {
        ofSetColor(ofColor::white, 70);
        ofDrawRectangle(font.rect.x - 10, font.rect.y - 10,
                        font.rect.width + 20, font.rect.height + 20);
    }
    font.draw();
}

void ofxOui::TextInput::mouseMoved(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    hover_ = inside(e.x, e.y);
}

void ofxOui::TextInput::mouseDragged(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    hover_ = inside(e.x, e.y);
}

void ofxOui::TextInput::mousePressed(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (inside(e.x, e.y) && e.button == 0) {
        active = true;
        erase_on_next_input_ = true;
    } else if (active) {
        labelOff = labelOn;
        active = false;
        ofxOui::TextInput::TextInputEvent event =
            ofxOui::TextInput::TextInputEvent(this, labelOn);
        if (text_input_event_callback_ != nullptr) {
            text_input_event_callback_(event);
        }
    }
}

void ofxOui::TextInput::mouseReleased(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
}

void ofxOui::TextInput::keyPressed(ofKeyEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (!active) return;
    if (e.key == OF_KEY_BACKSPACE || e.key == OF_KEY_DEL) {
        labelOn.pop_back();
        if (erase_on_next_input_) labelOn = "";
    } else if (e.key == OF_KEY_RETURN || e.key == OF_KEY_TAB) {
        labelOff = labelOn;
        active = false;
        ofxOui::TextInput::TextInputEvent event =
            ofxOui::TextInput::TextInputEvent(this, labelOn);
        if (text_input_event_callback_ != nullptr) {
            text_input_event_callback_(event);
        }
    } else if (e.key >= 32) {
        if (erase_on_next_input_) labelOn = "";
        labelOn += static_cast<char>(e.key);
    }
    erase_on_next_input_ = false;
}

ofxOui::TextInput::TextInputEvent::TextInputEvent(TextInput *sender_,
                                                     string text_)
    : sender(sender_), text(text_) {}
