/*
 * ofxCuiCuiDropDown.cpp
 *
 * Dropdown Menu
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

#include "ofxCuiCuiDropDown.hpp"

ofxCuiCui::DropDown::DropDown(int x_, int y_, int width_, int height_)
    : ofxCuiCui::Component(x_, y_, width_, height_), mouse_moved_(false) {
    type_ = ofxCuiCui::Type::DropDown;
    shape = ofxCuiCui::Shape::Rectangle;
    icon.load("caret-down.png");
    icon.alignment = ofxCuiCui::Anchor::MiddleRight;
    ofAddListener(ofEvents().mouseMoved, this,
                  &ofxCuiCui::DropDown::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxCuiCui::DropDown::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxCuiCui::DropDown::mouseReleased);
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxCuiCui::DropDown::mouseDragged);
}

ofxCuiCui::DropDown::~DropDown() {
    ofRemoveListener(ofEvents().mouseMoved, this,
                     &ofxCuiCui::DropDown::mouseMoved);
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxCuiCui::DropDown::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxCuiCui::DropDown::mouseReleased);
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxCuiCui::DropDown::mouseDragged);
}

void ofxCuiCui::DropDown::update() {
    ofxCuiCui::Component::update();
    if (active) {
        for (auto &gui : sub_buttons_) {
            gui->update();
        }
    }
}

void ofxCuiCui::DropDown::draw() {
    ofxCuiCui::Component::draw();
    if (active) {
        for (auto &gui : sub_buttons_) {
            gui->draw();
        }
    }
}

void ofxCuiCui::DropDown::mouseMoved(ofMouseEventArgs &e) {
    if (disabled) return;
    mouse_moved_ = true;
}

void ofxCuiCui::DropDown::mouseDragged(ofMouseEventArgs &e) {
    if (disabled) return;
    mouse_moved_ = !inside(e.x, e.y);
}

void ofxCuiCui::DropDown::mousePressed(ofMouseEventArgs &e) {
    if (disabled) return;
    if (inside(e.x, e.y) && e.button == 0) {
        active = !active;
        mouse_moved_ = false;
    }
    if (active) {
        createSubGui();
    }
}

void ofxCuiCui::DropDown::mouseReleased(ofMouseEventArgs &e) {
    if (disabled) return;
    if (!active || e.button != 0) return;
    for (auto &gui : sub_buttons_) {
        if (gui->inside(e.x, e.y)) {
            labelOn = labelOff = gui->labelOff;
            ofxCuiCui::DropDown::SelectEvent event =
                ofxCuiCui::DropDown::SelectEvent(this, labelOn);
            if (select_event_callback_ != nullptr) {
                select_event_callback_(event);
            }
            break;
        }
    }
    if (mouse_moved_) {
        active = false;
    }
}

void ofxCuiCui::DropDown::createSubGui() {
    for (auto &gui : sub_buttons_) {
        delete gui;
    }
    sub_buttons_.clear();
    for (int i = 0; i < items.size(); i++) {
        sub_buttons_.push_back(
            new ofxCuiCui::Button(x, y + 5 + (i + 1) * height, width, height));
        sub_buttons_[i]->shape = ofxCuiCui::Shape::Rectangle;
        sub_buttons_[i]->width = width;
        sub_buttons_[i]->height = height;
        sub_buttons_[i]->style = style;
        sub_buttons_[i]->labelOff = items[i];
        sub_buttons_[i]->labelOn = items[i];
    }
}

ofxCuiCui::DropDown::SelectEvent::SelectEvent(DropDown *sender_, string text_)
    : sender(sender_), text(text_) {}
