/*
 * ofxCuiCuiSlider.cpp
 *
 * Slider (inherits Numbox)
 *
 * This code has been authored by Jules Fran√ßoise <jfrancoi@sfu.ca>
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

#include "ofxCuiCuiSlider.hpp"

ofxCuiCui::Slider::Slider(int x_, int y_, int width_, int height_)
    : layout(Layout::Horizontal), origin(Origin::Lower) {
    type_ = ofxCuiCui::Type::Slider;
    min = 0.;
    max = 1.;
}

ofxCuiCui::Slider::~Slider() {}

void ofxCuiCui::Slider::update() {
    ofxCuiCui::Numbox::update();
    slider_rect_.x = x + font.padding;
    slider_rect_.y = font.rect.y + font.rect.height + font.padding;
    slider_rect_.width = width - 2 * font.padding;
    slider_rect_.height = height - font.rect.height - 3 * font.padding;
}

void ofxCuiCui::Slider::drawLabel() {
    ofxCuiCui::Component::drawLabel();
    ofSetLineWidth(3);
    ofNoFill();
    ofSetColor(current_frame_color_);
    ofDrawRectangle(slider_rect_.x, slider_rect_.y, slider_rect_.width,
                    slider_rect_.height);
    ofFill();
    ofSetColor(current_frame_color_, 150);
    if (layout == Layout::Horizontal) {
        if (origin == Origin::Lower || (origin == Origin::Zero && min >= 0.)) {
            ofDrawRectangle(slider_rect_.x, slider_rect_.y,
                            ((value - min) / (max - min)) * slider_rect_.width,
                            slider_rect_.height);
        } else if (origin == Origin::Upper ||
                   (origin == Origin::Zero && max <= 0.)) {
            float w = (1. - (value - min) / (max - min)) * slider_rect_.width;
            ofDrawRectangle(slider_rect_.x + slider_rect_.width, slider_rect_.y,
                            -w, slider_rect_.height);
        } else {
            ofDrawRectangle(
                slider_rect_.x - slider_rect_.width * min / (max - min),
                slider_rect_.y, (value / (max - min)) * slider_rect_.width,
                slider_rect_.height);
        }
    } else {
        if (origin == Origin::Lower || (origin == Origin::Zero && min >= 0.)) {
            float h = ((value - min) / (max - min)) * slider_rect_.height;
            ofDrawRectangle(slider_rect_.x,
                            slider_rect_.y + slider_rect_.height - h,
                            slider_rect_.width, h);
        } else if (origin == Origin::Upper ||
                   (origin == Origin::Zero && max <= 0.)) {
            ofDrawRectangle(
                slider_rect_.x, slider_rect_.y, slider_rect_.width,
                (1. - (value - min) / (max - min)) * slider_rect_.height);
        } else {
            ofDrawRectangle(
                slider_rect_.x,
                slider_rect_.y + slider_rect_.height * max / (max - min),
                slider_rect_.width,
                (-value / (max - min)) * slider_rect_.height);
        }
    }
    value_text_.draw();
}

void ofxCuiCui::Slider::mousePressed(ofMouseEventArgs &e) {
    if (disabled) return;
    if (inside(e.x, e.y) && e.button == 0) {
        active = true;
        user_input_ = "";
        if (slider_rect_.inside(e.x, e.y)) {
            dragging_ = true;
            if (layout == Layout::Horizontal)
                value = ((e.x - slider_rect_.x) / slider_rect_.width) *
                            (max - min) +
                        min;
            else
                value = (1. - (e.y - slider_rect_.y) / slider_rect_.height) *
                            (max - min) +
                        min;
            clipValue();
            ofxCuiCui::Numbox::ValueEvent event =
                ofxCuiCui::Numbox::ValueEvent(this, value);
            if (numbox_event_callback_ != nullptr) {
                numbox_event_callback_(event);
            }
        }
    } else {
        active = false;
    }
}

void ofxCuiCui::Slider::mouseDragged(ofMouseEventArgs &e) {
    if (disabled || !active || !dragging_) return;
    if (layout == Layout::Horizontal)
        value =
            ((e.x - slider_rect_.x) / slider_rect_.width) * (max - min) + min;
    else
        value =
            (1. - (e.y - slider_rect_.y) / slider_rect_.height) * (max - min) +
            min;
    clipValue();
    ofxCuiCui::Numbox::ValueEvent event =
        ofxCuiCui::Numbox::ValueEvent(this, value);
    if (numbox_event_callback_ != nullptr) {
        numbox_event_callback_(event);
    }
}
