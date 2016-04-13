/*
 * ofxCuiCuiGroup.cpp
 *
 * UI Component Group with grid layout
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

#include "ofxCuiCuiGroup.hpp"

ofxCuiCui::Group::Group(int x_, int y_, int width_, int height_)
    : x(x_),
      y(y_),
      width(width_),
      height(height_),
      padding(ofxCuiCui::Globals::getRetina() ? 10 : 5),
      backgroundColor(ofColor::white, 0),
      frameColor(ofColor::lightGray),
      frame_width(4),
      max_component_height(0),
      max_component_width(0) {}

ofxCuiCui::Group::~Group() {}

void ofxCuiCui::Group::setup() {
    int numRows(1), numCols(1);
    for (auto &c : components) {
        numRows = (c.first[0] + c.first[2] > numRows) ? c.first[0] + c.first[2]
                                                      : numRows;
        numCols = (c.first[1] + c.first[3] > numCols) ? c.first[1] + c.first[3]
                                                      : numCols;
    }
    int rowHeight = (height - (numRows + 1) * padding) / numRows;
    if (max_component_height > 0 && rowHeight > max_component_height) {
        rowHeight = max_component_height;
    }
    int colWidth = (width - (numCols + 1) * padding) / numCols;
    if (max_component_width > 0 && colWidth > max_component_width) {
        colWidth = max_component_width;
    }

    float offset_x(x + padding);
    float offset_y(y + padding);

    if (alignment == ofxCuiCui::Anchor::TopCenter ||
        alignment == ofxCuiCui::Anchor::MiddleCenter ||
        alignment == ofxCuiCui::Anchor::BottomCenter) {
        if (numCols % 2)
            offset_x = x + width / 2 - colWidth / 2 -
                       numCols / 2 * (padding + colWidth);
        else
            offset_x = x + width / 2 + padding / 2 -
                       numCols / 2 * (padding + colWidth);
    }

    if (alignment == ofxCuiCui::Anchor::TopRight ||
        alignment == ofxCuiCui::Anchor::MiddleRight ||
        alignment == ofxCuiCui::Anchor::BottomRight) {
        offset_x = x + width - numCols * (padding + colWidth);
    }

    if (alignment == ofxCuiCui::Anchor::MiddleLeft ||
        alignment == ofxCuiCui::Anchor::MiddleCenter ||
        alignment == ofxCuiCui::Anchor::MiddleRight) {
        if (numRows % 2)
            offset_y = y + height / 2 - rowHeight / 2 -
                       numRows / 2 * (padding + rowHeight);
        else
            offset_y = y + height / 2 + padding / 2 -
                       numRows / 2 * (padding + rowHeight);
    }

    if (alignment == ofxCuiCui::Anchor::BottomLeft ||
        alignment == ofxCuiCui::Anchor::BottomCenter ||
        alignment == ofxCuiCui::Anchor::BottomRight) {
        offset_y = y + height - numRows * (padding + rowHeight);
    }

    for (auto &component : components) {
        if (!component.second) continue;

        component.second->x =
            offset_x + component.first[1] * (padding + colWidth);
        component.second->y =
            offset_y + component.first[0] * (padding + rowHeight);
        component.second->width =
            (colWidth + padding) * component.first[3] - padding;
        component.second->height =
            (rowHeight + padding) * component.first[2] - padding;
    }
}

void ofxCuiCui::Group::update() {
    for (auto &c : components) {
        if (c.second) c.second->update();
    }
}

void ofxCuiCui::Group::draw() {
    ofFill();
    ofSetColor(backgroundColor);
    ofDrawRectangle(x, y, width, height);
    if (frame_width > 0) {
        ofNoFill();
        ofSetLineWidth(frame_width);
        ofSetColor(frameColor);
        ofDrawRectangle(x, y, width, height);
    }
    for (auto &c : components) {
        if (c.second && c.second->type() != ofxCuiCui::Type::DropDown) {
            c.second->draw();
        }
    }
    for (auto &c : components) {
        if (c.second && c.second->type() == ofxCuiCui::Type::DropDown) {
            c.second->draw();
        }
    }
}

bool ofxCuiCui::Group::inside(int x_, int y_) {
    return (x_ >= x) && (x_ <= x + width) && (y_ >= y) && (y_ <= y + height);
}

bool ofxCuiCui::Group::addComponent(shared_ptr<ofxCuiCui::Component> component,
                                    int row, int col, int rowSpan,
                                    int colSpan) {
    vector<int> coordinates({row, col, rowSpan, colSpan});
    for (auto &c : components) {
        if (row >= c.first[0] && row < c.first[0] + c.first[2] &&
            col >= c.first[1] && col < c.first[1] + c.first[3]) {
            return false;
        }
    }
    components.insert(std::pair<vector<int>, shared_ptr<ofxCuiCui::Component>>(
        coordinates, component));
    setup();
    return true;
}

shared_ptr<ofxCuiCui::Component> ofxCuiCui::Group::getComponent(int row,
                                                                int col) {
    for (auto &c : components) {
        if (row == c.first[0] && col == c.first[1] && c.second) {
            return c.second;
        }
    }
    return nullptr;
}

shared_ptr<ofxCuiCui::Component> ofxCuiCui::Group::getComponentByLabel(
    string label) {
    for (auto &c : components) {
        if (c.second && c.second->labelOff == label) {
            return c.second;
        }
    }
    return nullptr;
}

vector<shared_ptr<ofxCuiCui::Component>> ofxCuiCui::Group::getComponents() {
    vector<shared_ptr<ofxCuiCui::Component>> comp_vec;
    comp_vec.reserve(components.size());
    for (auto &c : components) {
        comp_vec.push_back(c.second);
    }
    return comp_vec;
}

bool ofxCuiCui::Group::removeComponent(
    shared_ptr<ofxCuiCui::Component> component) {
    int buttonIndex(0);
    for (auto &c : components) {
        if (component == c.second) {
            components.erase(c.first);
            setup();
            return true;
        }
        buttonIndex++;
    }
    return false;
}

bool ofxCuiCui::Group::removeComponent(int row, int col) {
    for (auto &c : components) {
        if (row == c.first[0] && col == c.first[1]) {
            components.erase(c.first);
            setup();
            return true;
        }
    }
    return false;
}

void ofxCuiCui::Group::clear() {
    components.clear();
    setup();
}

void ofxCuiCui::Group::disable() {
    for (auto &c : components) {
        c.second->disabled = true;
    }
}

void ofxCuiCui::Group::enable() {
    for (auto &c : components) {
        c.second->disabled = false;
    }
}
