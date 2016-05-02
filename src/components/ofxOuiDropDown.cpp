/*
 * ofxOuiDropDown.cpp
 *
 * Dropdown Menu
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

#include "ofxOuiDropDown.hpp"

ofxOui::DropDown::DropDown(int x_, int y_, int width_, int height_)
    : ofxOui::Component(x_, y_, width_, height_), mouse_moved_(false) {
    type_ = ofxOui::Type::DropDown;
    shape = ofxOui::Shape::Rectangle;
    icon.load("caret-down.png");
    icon.alignment = ofxOui::Anchor::MiddleRight;
    ofAddListener(ofEvents().mouseMoved, this, &ofxOui::DropDown::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxOui::DropDown::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxOui::DropDown::mouseReleased);
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxOui::DropDown::mouseDragged);
}

ofxOui::DropDown::~DropDown() {
    ofRemoveListener(ofEvents().mouseMoved, this,
                     &ofxOui::DropDown::mouseMoved);
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxOui::DropDown::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxOui::DropDown::mouseReleased);
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxOui::DropDown::mouseDragged);
    if (blocking_component == this) blocking_component = nullptr;
}

void ofxOui::DropDown::update() {
    ofxOui::Component::update();
    if (clear_buttons_) {
        sub_buttons_.clear();
        clear_buttons_ = false;
    }
    if (active) {
        for (auto &gui : sub_buttons_) {
            gui->update();
        }
    }
}

void ofxOui::DropDown::draw() {
    ofxOui::Component::draw();
    if (active) {
        for (auto &gui : sub_buttons_) {
            gui->draw();
        }
    }
}

void ofxOui::DropDown::mouseMoved(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    mouse_moved_ = true;
}

void ofxOui::DropDown::mouseDragged(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    mouse_moved_ = !inside(e.x, e.y);
}

void ofxOui::DropDown::mousePressed(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (items.empty()) return;
    if (inside(e.x, e.y) && e.button == 0) {
        active = !active;
        mouse_moved_ = false;
    }
    if (active) {
        blocking_component = this;
        createSubGui();
    }
}

void ofxOui::DropDown::mouseReleased(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (!active || e.button != 0) return;
    for (auto &gui : sub_buttons_) {
        if (gui->inside(e.x, e.y)) {
            mouse_moved_ = true;
            labelOn = labelOff = gui->labelOff;
            ofxOui::DropDown::SelectEvent event =
                ofxOui::DropDown::SelectEvent(this, labelOn);
            if (select_event_callback_ != nullptr) {
                select_event_callback_(event);
            }
            break;
        }
    }
    if (mouse_moved_) {
        active = false;
        clear_buttons_ = true;
        blocking_component = nullptr;
    }
}

void ofxOui::DropDown::createSubGui() {
    sub_buttons_.clear();
    for (int i = 0; i < items.size(); i++) {
        sub_buttons_.push_back(make_shared<ofxOui::Button>(
            x, y + 5 + (i + 1) * height, width, height));
        sub_buttons_[i]->shape = ofxOui::Shape::Rectangle;
        sub_buttons_[i]->width = width;
        sub_buttons_[i]->height = height;
        sub_buttons_[i]->style = style;
        sub_buttons_[i]->labelOff = items[i];
        sub_buttons_[i]->labelOn = items[i];
    }
}

ofxOui::DropDown::SelectEvent::SelectEvent(DropDown *sender_, string text_)
    : sender(sender_), text(text_) {}
