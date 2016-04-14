/*
 * ofxOuiDraggableButton.cpp
 *
 * Draggable button
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

#include "ofxOuiDraggableButton.hpp"

ofxOui::DraggableButton::DraggableButton(int x_, int y_, int width_,
                                            int height_)
    : ofxOui::Button(x_, y_, width_, height_),
      dragging_(false),
      mouse_offset_(0, 0),
      reference_position_(x_, y_),
      mouse_pressed_inside_(false) {
    type_ = ofxOui::Type::DraggableButton;
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxOui::DraggableButton::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxOui::DraggableButton::mouseReleased);
}

ofxOui::DraggableButton::~DraggableButton() {
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxOui::DraggableButton::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxOui::DraggableButton::mouseReleased);
}

void ofxOui::DraggableButton::mousePressed(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    ofxOui::Button::mousePressed(e);
    mouse_pressed_inside_ = inside(e.x, e.y);
    if (mouse_pressed_inside_) {
        mouse_offset_.x = x - e.x;
        mouse_offset_.y = y - e.y;
    }
}

void ofxOui::DraggableButton::mouseDragged(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    active = active || mouse_pressed_inside_;
    dragging_ = active && (dragging_ || (!dragging_ && inside(e.x, e.y)));
    if (dragging_) {
        x = e.x + mouse_offset_.x;
        y = e.y + mouse_offset_.y;
    }
}

void ofxOui::DraggableButton::mouseReleased(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
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

void ofxOui::DraggableButton::setReferencePosition() {
    reference_position_.x = x;
    reference_position_.y = y;
}

ofxOui::DraggableButton::DropEvent::DropEvent(
    ofxOui::DraggableButton *sender_, int x_, int y_)
    : sender(sender_), x(x_), y(y_) {}
