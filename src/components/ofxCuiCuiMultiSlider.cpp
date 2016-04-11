/*
 * ofxCuiCuiMultiSlider.cpp
 *
 * MultiSlider
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

#include "ofxCuiCuiMultiSlider.hpp"

ofxCuiCui::MultiSlider::MultiSlider(int x_, int y_, int width_, int height_)
    : ofxCuiCui::Component(x_, y_, width_, height_) {
    type_ = ofxCuiCui::Type::MultiSlider;
    shape = ofxCuiCui::Shape::Rectangle;
    font.alignment = ofxCuiCui::Anchor::TopCenter;
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxCuiCui::MultiSlider::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxCuiCui::MultiSlider::mouseDragged);
}

ofxCuiCui::MultiSlider::~MultiSlider() {
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxCuiCui::MultiSlider::mousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxCuiCui::MultiSlider::mouseDragged);
}

void ofxCuiCui::MultiSlider::update() {
    ofxCuiCui::Component::update();
    slider_rect_.x = x + font.padding;
    slider_rect_.y = font.rect.y + font.rect.height + font.padding;
    slider_rect_.width = width - 2 * font.padding;
    slider_rect_.height = height - font.rect.height - 3 * font.padding;
}

void ofxCuiCui::MultiSlider::drawLabel() {
    ofxCuiCui::Component::drawLabel();
    ofSetLineWidth(3);
    ofNoFill();
    ofSetColor(current_frame_color_);
    ofDrawRectangle(slider_rect_.x, slider_rect_.y, slider_rect_.width,
                    slider_rect_.height);
    ofFill();
    ofSetColor(current_frame_color_, 150);
    if (layout == Layout::Vertical) {
        float h = slider_rect_.height / values.size();
        if (origin == Origin::Lower || (origin == Origin::Zero && min >= 0.)) {
            for (int i = 0; i < values.size(); i++) {
                ofDrawRectangle(
                    slider_rect_.x, slider_rect_.y + i * h,
                    ((values[i] - min) / (max - min)) * slider_rect_.width, h);
            }
        } else if (origin == Origin::Upper ||
                   (origin == Origin::Zero && max <= 0.)) {
            for (int i = 0; i < values.size(); i++) {
                float w =
                    (1. - (values[i] - min) / (max - min)) * slider_rect_.width;
                ofDrawRectangle(slider_rect_.x + slider_rect_.width,
                                slider_rect_.y + i * h, -w, h);
            }
        } else {
            for (int i = 0; i < values.size(); i++) {
                ofDrawRectangle(
                    slider_rect_.x - slider_rect_.width * min / (max - min),
                    slider_rect_.y + i * h,
                    (values[i] / (max - min)) * slider_rect_.width, h);
            }
        }
    } else {
        float w = slider_rect_.width / values.size();
        if (origin == Origin::Lower || (origin == Origin::Zero && min >= 0.)) {
            for (int i = 0; i < values.size(); i++) {
                float h =
                    ((values[i] - min) / (max - min)) * slider_rect_.height;
                ofDrawRectangle(slider_rect_.x + i * w,
                                slider_rect_.y + slider_rect_.height - h, w, h);
            }
        } else if (origin == Origin::Upper ||
                   (origin == Origin::Zero && max <= 0.)) {
            for (int i = 0; i < values.size(); i++) {
                ofDrawRectangle(slider_rect_.x + i * w, slider_rect_.y, w,
                                (1. - (values[i] - min) / (max - min)) *
                                    slider_rect_.height);
            }
        } else {
            for (int i = 0; i < values.size(); i++) {
                ofDrawRectangle(
                    slider_rect_.x + i * w,
                    slider_rect_.y + slider_rect_.height * max / (max - min), w,
                    (-values[i] / (max - min)) * slider_rect_.height);
            }
        }
    }
}

void ofxCuiCui::MultiSlider::clipValues() {
    for (auto &value : values) {
        value = (value > max) ? max : (value < min) ? min : value;
    }
}

void ofxCuiCui::MultiSlider::mousePressed(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (values.empty()) return;
    if (inside(e.x, e.y) && e.button == 0) {
        active = true;
        if (slider_rect_.inside(e.x, e.y)) {
            dragging_ = true;
            int slider_index;
            if (layout == Layout::Vertical) {
                slider_index = values.size() * (e.y - slider_rect_.y) /
                               slider_rect_.height;
                values[slider_index] =
                    ((e.x - slider_rect_.x) / slider_rect_.width) *
                        (max - min) +
                    min;
            } else {
                slider_index =
                    values.size() * (e.x - slider_rect_.x) / slider_rect_.width;
                values[slider_index] =
                    (1. - (e.y - slider_rect_.y) / slider_rect_.height) *
                        (max - min) +
                    min;
            }
            clipValues();
            ofxCuiCui::MultiSlider::ValueEvent event =
                ofxCuiCui::MultiSlider::ValueEvent(this, slider_index,
                                                   values[slider_index]);
            if (multislider_event_callback_ != nullptr) {
                multislider_event_callback_(event);
            }
        }
    } else {
        active = false;
    }
    previous_position_ = {e.x, e.y};
}

void ofxCuiCui::MultiSlider::mouseDragged(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (!active || !dragging_ || values.empty()) return;
    if (layout == Layout::Vertical) {
        int previous_slider_index = values.size() *
                                    (previous_position_.y - slider_rect_.y) /
                                    slider_rect_.height;
        int slider_index =
            values.size() * (e.y - slider_rect_.y) / slider_rect_.height;
        if (previous_slider_index == slider_index) {
            values[slider_index] =
                ((e.x - slider_rect_.x) / slider_rect_.width) * (max - min) +
                min;
            if (multislider_event_callback_ != nullptr) {
                ofxCuiCui::MultiSlider::ValueEvent event =
                    ofxCuiCui::MultiSlider::ValueEvent(this, slider_index,
                                                       values[slider_index]);
                multislider_event_callback_(event);
            }
        } else if (previous_slider_index < slider_index) {
            for (int i = previous_slider_index + 1; i < slider_index + 1; i++) {
                float alpha = float(i - previous_slider_index) /
                              float(slider_index - previous_slider_index);
                values[i] =
                    (((1 - alpha) * (previous_position_.x - slider_rect_.x) +
                      alpha * (e.x - slider_rect_.x)) /
                     slider_rect_.width) *
                        (max - min) +
                    min;
                if (multislider_event_callback_ != nullptr) {
                    ofxCuiCui::MultiSlider::ValueEvent event =
                        ofxCuiCui::MultiSlider::ValueEvent(this, i, values[i]);
                    multislider_event_callback_(event);
                }
            }
        } else {
            for (int i = previous_slider_index - 1; i >= slider_index; i--) {
                float alpha = float(i - previous_slider_index) /
                              float(slider_index - previous_slider_index);
                values[i] =
                    (((1 - alpha) * (previous_position_.x - slider_rect_.x) +
                      alpha * (e.x - slider_rect_.x)) /
                     slider_rect_.width) *
                        (max - min) +
                    min;
                if (multislider_event_callback_ != nullptr) {
                    ofxCuiCui::MultiSlider::ValueEvent event =
                        ofxCuiCui::MultiSlider::ValueEvent(this, i, values[i]);
                    multislider_event_callback_(event);
                }
            }
        }
    } else {
        int previous_slider_index = values.size() *
                                    (previous_position_.x - slider_rect_.x) /
                                    slider_rect_.width;
        int slider_index =
            values.size() * (e.x - slider_rect_.x) / slider_rect_.width;
        if (previous_slider_index == slider_index) {
            values[slider_index] =
                (1. - (e.y - slider_rect_.y) / slider_rect_.height) *
                    (max - min) +
                min;
            if (multislider_event_callback_ != nullptr) {
                ofxCuiCui::MultiSlider::ValueEvent event =
                    ofxCuiCui::MultiSlider::ValueEvent(this, slider_index,
                                                       values[slider_index]);
                multislider_event_callback_(event);
            }
        } else if (previous_slider_index < slider_index) {
            for (int i = previous_slider_index + 1; i < slider_index + 1; i++) {
                float alpha = float(i - previous_slider_index) /
                              float(slider_index - previous_slider_index);
                values[i] =
                    (1. -
                     ((1 - alpha) * (previous_position_.y - slider_rect_.y) +
                      alpha * (e.y - slider_rect_.y)) /
                         slider_rect_.height) *
                        (max - min) +
                    min;
                if (multislider_event_callback_ != nullptr) {
                    ofxCuiCui::MultiSlider::ValueEvent event =
                        ofxCuiCui::MultiSlider::ValueEvent(this, i, values[i]);
                    multislider_event_callback_(event);
                }
            }
        } else {
            for (int i = previous_slider_index - 1; i >= slider_index; i--) {
                float alpha = float(i - previous_slider_index) /
                              float(slider_index - previous_slider_index);
                values[i] =
                    (1. -
                     ((1 - alpha) * (previous_position_.y - slider_rect_.y) +
                      alpha * (e.y - slider_rect_.y)) /
                         slider_rect_.height) *
                        (max - min) +
                    min;
                if (multislider_event_callback_ != nullptr) {
                    ofxCuiCui::MultiSlider::ValueEvent event =
                        ofxCuiCui::MultiSlider::ValueEvent(this, i, values[i]);
                    multislider_event_callback_(event);
                }
            }
        }
    }
    clipValues();
    previous_position_ = {e.x, e.y};
}

ofxCuiCui::MultiSlider::ValueEvent::ValueEvent(MultiSlider *sender_, int index_,
                                               float value_)
    : sender(sender_), index(index_), value(value_) {}
