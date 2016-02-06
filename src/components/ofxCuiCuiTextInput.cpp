/*
 * ofxCuiCuiTextInput.cpp
 *
 * Text Input Element (single-line text I guess...)
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

#include "ofxCuiCuiTextInput.hpp"

ofxCuiCui::TextInput::TextInput(int x_, int y_, int width_, int height_)
    : ofxCuiCui::Component(x_, y_, width_, height_),
      erase_on_next_input_(false) {
    type_ = ofxCuiCui::Type::TextInput;
    ofAddListener(ofEvents().mouseMoved, this,
                  &ofxCuiCui::TextInput::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxCuiCui::TextInput::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxCuiCui::TextInput::mouseReleased);
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxCuiCui::TextInput::mouseDragged);
    ofAddListener(ofEvents().keyPressed, this,
                  &ofxCuiCui::TextInput::keyPressed);
}

ofxCuiCui::TextInput::~TextInput() {
    ofRemoveListener(ofEvents().mouseMoved, this,
                     &ofxCuiCui::TextInput::mouseMoved);
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxCuiCui::TextInput::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxCuiCui::TextInput::mouseReleased);
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxCuiCui::TextInput::mouseDragged);
    ofRemoveListener(ofEvents().keyPressed, this,
                     &ofxCuiCui::TextInput::keyPressed);
}

void ofxCuiCui::TextInput::drawLabel() {
    if (active) {
        ofSetColor(ofColor::white, 70);
        ofDrawRectangle(font.rect.x - 10, font.rect.y - 10,
                        font.rect.width + 20, font.rect.height + 20);
    }
    font.draw();
}

void ofxCuiCui::TextInput::mouseMoved(ofMouseEventArgs &e) {
    if (disabled) return;
    hover_ = inside(e.x, e.y);
}

void ofxCuiCui::TextInput::mouseDragged(ofMouseEventArgs &e) {
    if (disabled) return;
    hover_ = inside(e.x, e.y);
}

void ofxCuiCui::TextInput::mousePressed(ofMouseEventArgs &e) {
    if (disabled) return;
    if (inside(e.x, e.y) && e.button == 0) {
        active = true;
        erase_on_next_input_ = true;
    } else if (active) {
        labelOff = labelOn;
        active = false;
        ofxCuiCui::TextInput::TextInputEvent event =
            ofxCuiCui::TextInput::TextInputEvent(this, labelOn);
        if (text_input_event_callback_ != nullptr) {
            text_input_event_callback_(event);
        }
    }
}

void ofxCuiCui::TextInput::mouseReleased(ofMouseEventArgs &e) {
    if (disabled) return;
}

void ofxCuiCui::TextInput::keyPressed(ofKeyEventArgs &e) {
    if (disabled) return;
    if (!active) return;
    if (e.key == OF_KEY_BACKSPACE || e.key == OF_KEY_DEL) {
        labelOn.pop_back();
        if (erase_on_next_input_) labelOn = "";
    } else if (e.key == OF_KEY_RETURN || e.key == OF_KEY_TAB) {
        labelOff = labelOn;
        active = false;
        ofxCuiCui::TextInput::TextInputEvent event =
            ofxCuiCui::TextInput::TextInputEvent(this, labelOn);
        if (text_input_event_callback_ != nullptr) {
            text_input_event_callback_(event);
        }
    } else if (e.key >= 32) {
        if (erase_on_next_input_) labelOn = "";
        labelOn += static_cast<char>(e.key);
    }
    erase_on_next_input_ = false;
}

ofxCuiCui::TextInput::TextInputEvent::TextInputEvent(TextInput *sender_,
                                                     string text_)
    : sender(sender_), text(text_) {}
