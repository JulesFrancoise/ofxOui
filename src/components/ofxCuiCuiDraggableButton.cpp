/*
 * ofxCuiCuiDraggableButton.cpp
 *
 * Draggable button
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

#include "ofxCuiCuiDraggableButton.hpp"

ofxCuiCui::DraggableButton::DraggableButton(int x_, int y_, int width_,
                                            int height_)
    : ofxCuiCui::Button(x_, y_, width_, height_),
      dragging_(false),
      mouse_offset_(0, 0),
      reference_position_(x_, y_),
      mouse_pressed_inside_(false) {
    type_ = ofxCuiCui::Type::DraggableButton;
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxCuiCui::DraggableButton::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxCuiCui::DraggableButton::mouseReleased);
}

ofxCuiCui::DraggableButton::~DraggableButton() {
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxCuiCui::DraggableButton::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxCuiCui::DraggableButton::mouseReleased);
}

void ofxCuiCui::DraggableButton::mousePressed(ofMouseEventArgs &e) {
    if (disabled) return;
    ofxCuiCui::Button::mousePressed(e);
    mouse_pressed_inside_ = inside(e.x, e.y);
    if (mouse_pressed_inside_) {
        mouse_offset_.x = x - e.x;
        mouse_offset_.y = y - e.y;
    }
}

void ofxCuiCui::DraggableButton::mouseDragged(ofMouseEventArgs &e) {
    if (disabled) return;
    active = active || mouse_pressed_inside_;
    dragging_ = active && (dragging_ || (!dragging_ && inside(e.x, e.y)));
    if (dragging_) {
        x = e.x + mouse_offset_.x;
        y = e.y + mouse_offset_.y;
    }
}

void ofxCuiCui::DraggableButton::mouseReleased(ofMouseEventArgs &e) {
    if (disabled) return;
    if (dragging_) {
        DropEvent event(this, e.x, e.y);
        if (drop_event_callback_ != nullptr) {
            drop_event_callback_(event);
        }
        x = reference_position_.x;
        y = reference_position_.y;
        active = false;
        dragging_ = false;
    }
}

void ofxCuiCui::DraggableButton::setReferencePosition() {
    reference_position_.x = x;
    reference_position_.y = y;
}

ofxCuiCui::DraggableButton::DropEvent::DropEvent(
    ofxCuiCui::DraggableButton *sender_, int x_, int y_)
    : sender(sender_), x(x_), y(y_) {}
