/*
 * ofxCuiCuiBpf.cpp
 *
 * Breakpoint function component
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

#include "ofxCuiCuiBpf.hpp"

ofxCuiCui::Bpf::Bpf(int x_, int y_, int width_, int height_)
    : ofxCuiCui::Component(x_, y_, width_, height_) {
    type_ = ofxCuiCui::Type::Bpf;
    shape = ofxCuiCui::Shape::Rectangle;
    font.alignment = ofxCuiCui::Anchor::TopCenter;
    ofAddListener(ofEvents().mousePressed, this, &ofxCuiCui::Bpf::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxCuiCui::Bpf::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxCuiCui::Bpf::mouseReleased);
}

ofxCuiCui::Bpf::~Bpf() {
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxCuiCui::Bpf::mousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxCuiCui::Bpf::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxCuiCui::Bpf::mouseReleased);
}

void ofxCuiCui::Bpf::update() {
    ofxCuiCui::Component::update();
    graph.view_area.x = x + font.padding;
    graph.view_area.y = font.rect.y + font.rect.height + font.padding;
    graph.view_area.width = width - 2 * font.padding;
    graph.view_area.height = height - font.rect.height - 3 * font.padding;
}

void ofxCuiCui::Bpf::clipBounds() {
    if (values.empty()) return;
    graph.graph_area.x_min = values[0].x;
    graph.graph_area.x_max = values[0].x;
    graph.graph_area.y_min = values[0].y;
    graph.graph_area.y_max = values[0].y;
    for (auto &value : values) {
        if (value.x < graph.graph_area.x_min) graph.graph_area.x_min = value.x;
        if (value.x > graph.graph_area.x_max) graph.graph_area.x_max = value.x;
        if (value.y < graph.graph_area.y_min) graph.graph_area.y_min = value.y;
        if (value.y > graph.graph_area.y_max) graph.graph_area.y_max = value.y;
    }
}

void ofxCuiCui::Bpf::drawLabel() {
    ofxCuiCui::Component::drawLabel();
    ofSetLineWidth(3);
    ofNoFill();
    ofSetColor(current_frame_color_);
    ofDrawRectangle(graph.view_area.x, graph.view_area.y, graph.view_area.width,
                    graph.view_area.height);
    ofFill();
    ofSetColor(current_frame_color_, 150);

    ofBeginShape();
    if (appearance == Appearance::FillBottom) {
        ofVertex(graph.coord2pix(values[0]).x,
                 graph.view_area.y + graph.view_area.height);
    } else if (appearance == Appearance::FillTop) {
        ofVertex(graph.coord2pix(values[0]).x, graph.view_area.y);
    } else if (appearance == Appearance::FillZero) {
        ofVertex(graph.coord2pix(values[0]).x,
                 graph.view_area.y + graph.view_area.height / 2);
    }
    for (auto &value : values) {
        ofVec2f pix = graph.coord2pix(value);
        if (point_radius > 0) {
            ofFill();
            ofDrawCircle(pix.x, pix.y, point_radius);
        }
        if (appearance == Appearance::Lines) {
            ofNoFill();
        }
        ofVertex(pix.x, pix.y);
    }
    if (appearance == Appearance::FillBottom) {
        ofVertex(graph.coord2pix(values[values.size() - 1]).x,
                 graph.view_area.y + graph.view_area.height);
    } else if (appearance == Appearance::FillTop) {
        ofVertex(graph.coord2pix(values[values.size() - 1]).x,
                 graph.view_area.y);
    } else if (appearance == Appearance::FillZero) {
        ofVertex(graph.coord2pix(values[values.size() - 1]).x,
                 graph.view_area.y + graph.view_area.height / 2);
    }
    ofEndShape();
}

void ofxCuiCui::Bpf::mousePressed(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    bool dbl_click = (ofGetElapsedTimef() - time_mouse_pressed_) < 0.4;
    time_mouse_pressed_ = ofGetElapsedTimef();
    point_selected_ = -1;
    ofVec2f viewPoint(e.x, e.y);
    ofVec2f graphPoint(graph.pix2coord(viewPoint));
    if (disabled || values.empty() || !graph.insideViewArea(viewPoint)) return;
    {
        int i = 0;
        for (auto &value : values) {
            ofVec2f pix = graph.coord2pix(value);
            if (sqrt((e.x - pix.x) * (e.x - pix.x) +
                     (e.y - pix.y) * (e.y - pix.y)) < 1. * point_radius) {
                point_selected_ = i;
                break;
            }
            i++;
        }
    }
    if (dbl_click) {
        if (point_selected_ < 0) {
            vector<ofVec2f>::iterator it = values.begin();
            int i = 0;
            while (it != values.end()) {
                ofVec2f pix = graph.coord2pix(*it);
                if (i > 0 && e.x < pix.x && e.x >= values[i - 1].x) {
                    break;
                }
                it++;
                i++;
            }
            values.insert(it, graphPoint);
            point_selected_ = i;
        } else {
            vector<ofVec2f>::iterator it = values.begin();
            for (int i = 0; i < point_selected_; i++) it++;
            values.erase(it);
        }
    } else {
        if (point_selected_ >= 0) values[point_selected_] = graphPoint;
    }
}

void ofxCuiCui::Bpf::mouseDragged(ofMouseEventArgs &e) {
    if (disabled || (blocking_component && blocking_component != this)) return;
    if (values.empty() || point_selected_ < 0) return;
    ofVec2f graphPoint(graph.pix2coord(ofVec2f(e.x, e.y)));
    if (point_selected_ > 0)
        graphPoint.x = max(graphPoint.x, values[point_selected_ - 1].x);
    else
        graphPoint.x = max(graphPoint.x, graph.graph_area.x_min);
    if (point_selected_ < values.size() - 1)
        graphPoint.x = min(graphPoint.x, values[point_selected_ + 1].x);
    else
        graphPoint.x = min(graphPoint.x, graph.graph_area.x_max);
    graphPoint.y = max(graphPoint.y, graph.graph_area.y_min);
    graphPoint.y = min(graphPoint.y, graph.graph_area.y_max);
    values[point_selected_] = graphPoint;
}

void ofxCuiCui::Bpf::mouseReleased(ofMouseEventArgs &e) {
    point_selected_ = -1;
}
