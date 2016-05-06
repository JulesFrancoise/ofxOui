/*
 * ofxOuiGraph.cpp
 *
 * Graph view area
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

#include "ofxOuiGraph.hpp"

void ofxOui::Graph::Ruler::update() {
    float base = pow(10., floor(log10(max - min)) - 1.);
    int num_units = (max - min) / base;
    while (num_units > 10) {
        base *= 2.;
        num_units = (max - min) / base;
    }
    float next_unit;
    next_unit = 0.1 * base * int(ceil(min / (0.1 * base)));
    num_units = (max - min) / (0.1 * base);
    ticks_minor.resize(num_units);
    for (int i = 0; i < num_units; i++) {
        if (layout == Layout::Horizontal)
            ticks_minor[i] =
                x + width * (next_unit + i * 0.1 * base - min) / (max - min);
        else
            ticks_minor[i] =
                y + height * (next_unit + i * 0.1 * base - min) / (max - min);
    }
    next_unit = base * int(ceil(min / base));
    num_units = (max - min) / base;
    ticks_major.resize(num_units);
    ticks_labels.resize(num_units);
    for (int i = 0; i < num_units; i++) {
        if (layout == Layout::Horizontal) {
            ticks_major[i] =
                x + width * (next_unit + i * base - min) / (max - min);
            ticks_labels[i].x = ticks_major[i];
            ticks_labels[i].y = y + height;
            ticks_labels[i].width = base;
            ticks_labels[i].height = height;
        } else {
            ticks_major[i] =
                y + height * (next_unit + i * base - min) / (max - min);
            ticks_labels[i].x = x;
            ticks_labels[i].y = ticks_major[i];
            ticks_labels[i].width = width;
            ticks_labels[i].height = base;
            ticks_labels[i].alignment = ofxOui::Anchor::BottomRight;
        }
        ticks_labels[i].setFontSize(8);
        ticks_labels[i].padding = 0.;
        std::ostringstream out;
        out << std::setprecision(std::max(0, -int(floor(log10(base)))))
            << next_unit + i * base;
        ticks_labels[i].text = out.str();
        ticks_labels[i].update();
    }
}

void ofxOui::Graph::Ruler::draw() {
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawRectangle(x, y, width, height);
    ofSetColor(ofColor::black);
    if (layout == Layout::Horizontal) {
        ofSetLineWidth(1);
        for (auto& absissa : ticks_minor)
            ofDrawLine(absissa, y, absissa, y + 0.4 * height);
        ofSetLineWidth(2);
        for (auto& absissa : ticks_major)
            ofDrawLine(absissa, y, absissa, y + 0.8 * height);
    } else {
        ofSetLineWidth(1);
        for (auto& ordinate : ticks_minor)
            ofDrawLine(x, ordinate, x + 0.4 * width, ordinate);
        ofSetLineWidth(2);
        for (auto& ordinate : ticks_major)
            ofDrawLine(x, ordinate, x + 0.8 * width, ordinate);
    }
    for (auto& label : ticks_labels) label.draw();
}

ofxOui::Graph::Graph() {
    ofAddListener(ofEvents().mouseScrolled, this,
                  &ofxOui::Graph::mouseScrolled);
}

ofxOui::Graph::~Graph() {
    ofRemoveListener(ofEvents().mouseScrolled, this,
                     &ofxOui::Graph::mouseScrolled);
}

void ofxOui::Graph::drawRuler() {
    if (horizontal_ruler.first) {
        horizontal_ruler.second.x = view.x;
        horizontal_ruler.second.y = view.y;
        horizontal_ruler.second.width = view.width;
        horizontal_ruler.second.height = view.height / 40.;
        horizontal_ruler.second.min = graph_area.x_min;
        horizontal_ruler.second.max = graph_area.x_max;
        horizontal_ruler.second.update();
        horizontal_ruler.second.draw();
    }
    if (vertical_ruler.first) {
        vertical_ruler.second.x = view.x;
        vertical_ruler.second.y = view.y;
        vertical_ruler.second.width = view.width / 40;
        vertical_ruler.second.height = view.height;
        vertical_ruler.second.min = graph_area.y_min;
        vertical_ruler.second.max = graph_area.y_max;
        vertical_ruler.second.update();
        vertical_ruler.second.draw();
    }
}

void ofxOui::Graph::setupViewport() {
    if (viewport_valid) return;
    // keep a copy of your viewport and transform matrices for later
    ofPushView();

    // tell OpenGL to change your viewport. note that your transform matrices
    // will now need setting up
    ofViewport(view);

    // setup transform matrices for normal oF-style usage, i.e.
    //  0,0=left,top
    //  ofGetViewportWidth(),ofGetViewportHeight()=right,bottom
    ofSetupScreen();
    ofScale(view.width / (graph_area.x_max - graph_area.x_min),
            view.height / (graph_area.y_max - graph_area.y_min));
    ofTranslate(-graph_area.x_min, -graph_area.y_min);

    viewport_valid = true;
}

void ofxOui::Graph::restoreViewport() {
    // restore the old viewport (now full view and oF coords)
    ofPopView();
    viewport_valid = false;
}

bool ofxOui::Graph::insideViewArea(ofVec2f const& pointAsPixels) const {
    return ((pointAsPixels.x >= view.x) &&
            (pointAsPixels.x <= view.x + view.width) &&
            (pointAsPixels.y >= view.y) &&
            (pointAsPixels.y <= view.y + view.height));
}

bool ofxOui::Graph::insideGraphArea(ofVec2f const& pointAsCoord) const {
    return ((pointAsCoord.x >= graph_area.x_min) &&
            (pointAsCoord.x <= graph_area.x_max) &&
            (pointAsCoord.y >= graph_area.y_min) &&
            (pointAsCoord.y <= graph_area.y_max));
}

ofVec2f ofxOui::Graph::coord2pix(ofVec2f const& pointAsCoord) const {
    ofVec2f pointAsPixels;
    pointAsPixels.x = view.x +
                      view.width * (pointAsCoord.x - graph_area.x_min) /
                          (graph_area.x_max - graph_area.x_min);
    pointAsPixels.y = view.y +
                      view.height * (pointAsCoord.y - graph_area.y_min) /
                          (graph_area.y_max - graph_area.y_min);
    return pointAsPixels;
}

ofVec2f ofxOui::Graph::pix2coord(ofVec2f const& pointAsPixels) const {
    ofVec2f pointAsCoord;
    pointAsCoord.x = graph_area.x_min +
                     float(graph_area.x_max - graph_area.x_min) *
                         (float(pointAsPixels.x - view.x) / float(view.width));
    pointAsCoord.y = graph_area.y_min +
                     float(graph_area.y_max - graph_area.y_min) *
                         (float(pointAsPixels.y - view.y) / float(view.height));
    return pointAsCoord;
}

ofVec2f ofxOui::Graph::scale2view(ofVec2f const& scaleAsCoord) const {
    return ofVec2f(
        scaleAsCoord.x * view.width / (graph_area.x_max - graph_area.x_min),
        scaleAsCoord.y * view.height / (graph_area.y_max - graph_area.y_min));
}

ofVec2f ofxOui::Graph::scale2graph(ofVec2f const& scaleAsPixels) const {
    return ofVec2f(
        scaleAsPixels.x * (graph_area.x_max - graph_area.x_min) / view.width,
        scaleAsPixels.y * (graph_area.y_max - graph_area.y_min) / view.height);
}

void ofxOui::Graph::mouseScrolled(ofMouseEventArgs& e) {
    // int x, int y, float scrollX, float scrollY
    if (insideViewArea(ofVec2f(e.x, e.y))) {
        if (ofGetKeyPressed(OF_KEY_SUPER)) {
            if (iso_zoom && !ofGetKeyPressed(OF_KEY_SHIFT)) {
                float translateX =
                    0.01 * e.scrollY * (graph_area.x_max - graph_area.x_min);
                float translateY =
                    0.01 * e.scrollY * (graph_area.y_max - graph_area.y_min);
                graph_area.x_min += translateX * (e.x - view.x) / view.width;
                graph_area.x_max -=
                    translateX * (1. - (e.x - view.x) / view.width);
                graph_area.y_min += translateY * (e.y - view.y) / view.height;
                graph_area.y_max -=
                    translateY * (1. - (e.y - view.y) / view.height);
            } else {
                if (std::abs(e.scrollX) > std::abs(e.scrollY)) {
                    float translateX = -0.01 * e.scrollX *
                                       (graph_area.x_max - graph_area.x_min);
                    graph_area.x_min -= translateX;
                    graph_area.x_max += translateX;
                } else {
                    float translateY = -0.01 * e.scrollY *
                                       (graph_area.y_max - graph_area.y_min);
                    graph_area.y_min -= translateY;
                    graph_area.y_max += translateY;
                }
            }
        } else {
            if (std::abs(e.scrollX) > std::abs(e.scrollY)) {
                float translateX =
                    -0.01 * e.scrollX * (graph_area.x_max - graph_area.x_min);
                graph_area.x_min += translateX;
                graph_area.x_max += translateX;
            } else {
                float translateY =
                    -0.01 * e.scrollY * (graph_area.y_max - graph_area.y_min);
                graph_area.y_min += translateY;
                graph_area.y_max += translateY;
            }
        }
        if (bounds_changed_event_callback_) {
            ofxOui::Graph::BoundsChangedEvent event(this);
            bounds_changed_event_callback_(event);
        }
    }
}

ofxOui::Graph::BoundsChangedEvent::BoundsChangedEvent(ofxOui::Graph* sender_)
    : sender(sender_) {}
