/*
 * ofxCuiCuiMatrix.cpp
 *
 * Button Matrix (supports both button -single-button activation- and toggle
 * -multi-button activation-)
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

#include "ofxCuiCuiMatrix.hpp"

ofxCuiCui::Matrix::Matrix(int x_, int y_, int width_, int height_)
    : ofxCuiCui::Component(x_, y_, width_, height_),
      rows(1),
      cols(1),
      padding(3),
      toggle(false),
      draw_grid(true),
      button_shape(ofxCuiCui::Shape::Rectangle),
      click_event_callback_(nullptr) {
    buttons = {{}};
    font.alignment = ofxCuiCui::Anchor::TopCenter;
    type_ = ofxCuiCui::Type::Matrix;
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxCuiCui::Matrix::mouseDragged);
}

ofxCuiCui::Matrix::~Matrix() {
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxCuiCui::Matrix::mouseDragged);
}

void ofxCuiCui::Matrix::setup() {
    ofxCuiCui::Component::update();
    if (shape == ofxCuiCui::Shape::Circle) {
        float radius = min(width, height) / 2.;
        grid_rect_.y = y + height / 2. + padding - M_SQRT1_2 * radius;
        grid_rect_.x = x + width / 2. + padding - M_SQRT1_2 * radius;
        grid_rect_.width = width - 2. * (grid_rect_.x - x);
        grid_rect_.height = height - 2. * (grid_rect_.y - y);
    } else {
        grid_rect_.x = x + padding;
        grid_rect_.y = font.rect.y + font.rect.height + font.padding + padding;
        grid_rect_.width = width - 2 * padding;
        grid_rect_.height =
            height - font.rect.height - 2 * font.padding - 2 * padding;
    }
    button_width_ = (grid_rect_.width - (cols - 1) * padding) / cols;
    button_height_ = (grid_rect_.height - (rows - 1) * padding) / rows;
    vector<vector<ofxCuiCui::Button>> oldButtons(std::move(buttons));
    buttons.resize(rows);
    for (int row = 0; row < rows; row++) {
        buttons[row].resize(cols);
        for (int col = 0; col < cols; col++) {
            buttons[row][col].x =
                grid_rect_.x + col * (button_width_ + padding);
            buttons[row][col].y =
                grid_rect_.y + row * (button_height_ + padding);
            buttons[row][col].width = button_width_;
            buttons[row][col].height = button_height_;
            buttons[row][col].toggle = true;
            buttons[row][col].style = style;
            buttons[row][col].shape = button_shape;
            buttons[row][col].onClick(this,
                                      &::ofxCuiCui::Matrix::onButtonClick);
        }
    }
}

void ofxCuiCui::Matrix::update() {
    if (rows != buttons.size() || cols != buttons[0].size()) {
        setup();
    } else {
        ofxCuiCui::Component::update();
    }
    current_background_color_ = style.background_color_off;
    for (auto &buttonRow : buttons) {
        for (auto &button : buttonRow) {
            button.update();
        }
    }
}

void ofxCuiCui::Matrix::draw() {
    ofxCuiCui::Component::draw();
    ofFill();
    ofSetColor(current_frame_color_);
    if (draw_grid) {
        for (int row = (shape == ofxCuiCui::Shape::Circle) ? 0 : 1;
             row < rows + (shape == ofxCuiCui::Shape::Circle) ? 1 : 0; row++) {
            ofDrawLine(
                grid_rect_.x,
                grid_rect_.y + row * (button_height_ + padding) - padding,
                grid_rect_.x + grid_rect_.width,
                grid_rect_.y + row * (button_height_ + padding) - padding);
        }
        for (int col = (shape == ofxCuiCui::Shape::Circle) ? 0 : 1;
             col < cols + (shape == ofxCuiCui::Shape::Circle) ? 1 : 0; col++) {
            ofDrawLine(grid_rect_.x + col * (button_width_ + padding) - padding,
                       grid_rect_.y,
                       grid_rect_.x + col * (button_width_ + padding) - padding,
                       grid_rect_.y + grid_rect_.height);
        }
    }
    for (auto &buttonRow : buttons) {
        for (auto &button : buttonRow) {
            button.draw();
        }
    }
}

void ofxCuiCui::Matrix::mouseDragged(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (!inside(e.x, e.y)) return;
    for (auto &buttonRow : buttons) {
        for (auto &button : buttonRow) {
            if (&button != selected_button_ && button.inside(e.x, e.y)) {
                button.active = !button.active;
                selected_button_ = &button;
                ofxCuiCui::Button::ClickEvent event(&button, button.active);
                onButtonClick(event);
            }
        }
    }
}

void ofxCuiCui::Matrix::onButtonClick(ofxCuiCui::Button::ClickEvent &e) {
    selected_button_ = e.sender;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (e.sender == &buttons[row][col]) {
                buttons[row][col].active = toggle ? e.value : true;
                ClickEvent event(this, row, col, toggle ? e.value : true);
                if (click_event_callback_) {
                    click_event_callback_(event);
                }
            } else {
                if (!toggle) buttons[row][col].active = false;
            }
        }
    }
}

ofxCuiCui::Matrix::ClickEvent::ClickEvent(ofxCuiCui::Matrix *sender_, int row_,
                                          int col_, bool value_)
    : sender(sender_), row(row_), col(col_), value(value_) {}
