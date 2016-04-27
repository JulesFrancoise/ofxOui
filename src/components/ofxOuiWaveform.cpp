/*
 * ofxOuiWaveform.cpp
 *
 * Simplex waveform component
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

#include "ofxOuiWaveform.hpp"

ofxOui::Waveform::Waveform(int x_, int y_, int width_, int height_)
    : ofxOui::Component(x_, y_, width_, height_),
      graph(make_shared<ofxOui::Graph>()) {
    type_ = ofxOui::Type::Waveform;
    shape = ofxOui::Shape::Rectangle;
    font.alignment = ofxOui::Anchor::TopCenter;
}

ofxOui::Waveform::~Waveform() {}

void ofxOui::Waveform::update() {
    ofxOui::Component::update();
    graph->view.x = x + font.padding;
    graph->view.y = font.rect.y + font.rect.height + font.padding;
    graph->view.width = width - 2 * font.padding;
    graph->view.height = height - font.rect.height - 3 * font.padding;
}

void ofxOui::Waveform::clipBounds() {
    graph->graph_area.x_min = 0;
    graph->graph_area.x_max = size;
}

void ofxOui::Waveform::drawLabel() {
    ofxOui::Component::drawLabel();
    ofSetLineWidth(3);
    ofNoFill();
    ofSetColor(current_frame_color_);
    ofDrawRectangle(graph->view.x, graph->view.y, graph->view.width,
                    graph->view.height);
    ofFill();

    if (size <= 0) return;
    for (auto &c : channels_colors) {
        ofSetColor(c.second);
        ofBeginShape();
        if (appearance == Appearance::FillBottom) {
            ofVertex(graph->view.x, graph->view.y + graph->view.height);
        } else if (appearance == Appearance::FillTop) {
            ofVertex(graph->view.x, graph->view.y);
        } else if (appearance == Appearance::FillZero) {
            ofVertex(graph->view.x, graph->view.y + graph->view.height / 2);
        }
        for (int i = 0; i < size; i++) {
            ofVec2f pix = graph->coord2pix(
                {static_cast<float>(i), values[i * dimension + c.first]});
            if (appearance == Appearance::Lines) {
                ofNoFill();
            }
            ofVertex(pix.x, pix.y);
        }
        if (appearance == Appearance::FillBottom) {
            ofVertex(graph->view.x + graph->view.width,
                     graph->view.y + graph->view.height);
        } else if (appearance == Appearance::FillTop) {
            ofVertex(graph->view.x + graph->view.width, graph->view.y);
        } else if (appearance == Appearance::FillZero) {
            ofVertex(graph->view.x + graph->view.width,
                     graph->view.y + graph->view.height / 2);
        }
        ofEndShape();
    }
}
