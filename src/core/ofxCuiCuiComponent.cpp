/*
 * ofxCuiCuiComponent.cpp
 *
 * UI Component Base Class
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

#include "ofxCuiCuiComponent.hpp"

ofxCuiCui::Component::Component(float x_, float y_, float width_, float height_)
    : x(x_), y(y_), width(width_), height(height_) {}

ofxCuiCui::Component::~Component() {}

void ofxCuiCui::Component::update() {
    hover_ = inside(ofGetMouseX(), ofGetMouseY());
    font.text = active ? labelOn : labelOff;
    font.x = x;
    font.y = y;
    font.width = width;
    font.height = height;
    font.update();
    icon.x = x;
    icon.y = y;
    icon.width = width;
    icon.height = height;
    icon.update();
    if (disabled) {
        current_background_color_ = style.background_color_disabled;
        current_frame_color_ = style.frame_color_disabled;
        font.color = style.font_color_disabled;
        icon.color = style.font_color_disabled;
    } else {
        if (active) {
            if (hover_) {
                current_background_color_ = style.background_color_on_hover;
                current_frame_color_ = style.frame_color_on_hover;
                font.color = style.font_color_on_hover;
                icon.color = style.font_color_on_hover;
            } else {
                current_background_color_ = style.background_color_on;
                current_frame_color_ = style.frame_color_on;
                font.color = style.font_color_on;
                icon.color = style.font_color_on;
            }
        } else {
            if (hover_) {
                current_background_color_ = style.background_color_off_hover;
                current_frame_color_ = style.frame_color_off_hover;
                font.color = style.font_color_off_hover;
                icon.color = style.font_color_off_hover;
            } else {
                current_background_color_ = style.background_color_off;
                current_frame_color_ = style.frame_color_off;
                font.color = style.font_color_off;
                icon.color = style.font_color_off;
            }
        }
    }
}

void ofxCuiCui::Component::draw() {
    drawBackground();
    drawFrame();
    drawIcon();
    drawLabel();
}

void ofxCuiCui::Component::drawBackground() {
    ofFill();
    ofSetLineWidth(0);
    ofSetColor(current_background_color_);
    if (shape == ofxCuiCui::Shape::Rectangle) {
        ofDrawRectangle(x, y, width, height);
    } else if (shape == ofxCuiCui::Shape::RectRounded) {
        ofDrawRectRounded(x, y, width, height, ofxCuiCui::Globals::getRetina()
                                                   ? style.roundness * 2.
                                                   : style.roundness);
    } else if (shape == ofxCuiCui::Shape::Circle) {
        ofDrawCircle(x + width / 2, y + height / 2, min(width, height) / 2);
    }
}

void ofxCuiCui::Component::drawFrame() {
    if (style.frame_width <= 0) return;
    ofNoFill();
    ofSetLineWidth(ofxCuiCui::Globals::getRetina() ? style.frame_width * 2.
                                                   : style.frame_width);
    ofSetColor(current_frame_color_);
    if (shape == ofxCuiCui::Shape::Rectangle) {
        ofDrawRectangle(x, y, width, height);
    } else if (shape == ofxCuiCui::Shape::RectRounded) {
        ofDrawRectRounded(x, y, width, height, style.roundness);
    } else if (shape == ofxCuiCui::Shape::Circle) {
        ofDrawCircle(x + width / 2, y + height / 2, min(width, height) / 2);
    }
}

void ofxCuiCui::Component::drawIcon() { icon.draw(); }

void ofxCuiCui::Component::drawLabel() { font.draw(); }

bool ofxCuiCui::Component::inside(float x_, float y_) const {
    if (shape == ofxCuiCui::Shape::Rectangle ||
        shape == ofxCuiCui::Shape::RectRounded) {
        return (x_ >= x) && (x_ <= x + width) && (y_ >= y) &&
               (y_ <= y + height);
    } else if (shape == ofxCuiCui::Shape::Circle) {
        float circleX = x + width / 2;
        float circleY = y + height / 2;
        float circleR = min(width, height) / 2;
        return std::sqrt((x_ - circleX) * (x_ - circleX) +
                         (y_ - circleY) * (y_ - circleY)) < circleR;
    } else {
        return false;
    }
}
