/*
 * ofxCuiCuiGraph.cpp
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

#include "ofxCuiCuiGraph.hpp"

ofxCuiCui::Graph::Graph() {
    ofAddListener(ofEvents().mouseScrolled, this,
                  &ofxCuiCui::Graph::mouseScrolled);
}

ofxCuiCui::Graph::~Graph() {
    ofRemoveListener(ofEvents().mouseScrolled, this,
                     &ofxCuiCui::Graph::mouseScrolled);
}

bool ofxCuiCui::Graph::insideViewArea(ofVec2f const& pointAsPixels) const {
    return ((pointAsPixels.x >= view_area.x) &&
            (pointAsPixels.x <= view_area.x + view_area.width) &&
            (pointAsPixels.y >= view_area.y) &&
            (pointAsPixels.y <= view_area.y + view_area.height));
}

bool ofxCuiCui::Graph::insideGraphArea(ofVec2f const& pointAsCoord) const {
    return ((pointAsCoord.x >= graph_area.x_min) &&
            (pointAsCoord.x <= graph_area.x_max) &&
            (pointAsCoord.y >= graph_area.y_min) &&
            (pointAsCoord.y <= graph_area.y_max));
}

ofVec2f ofxCuiCui::Graph::coord2pix(ofVec2f const& pointAsCoord) const {
    ofVec2f pointAsPixels;
    pointAsPixels.x = view_area.x +
                      view_area.width * (pointAsCoord.x - graph_area.x_min) /
                          (graph_area.x_max - graph_area.x_min);
    pointAsPixels.y = view_area.y +
                      view_area.height * (pointAsCoord.y - graph_area.y_min) /
                          (graph_area.y_max - graph_area.y_min);
    return pointAsPixels;
}

ofVec2f ofxCuiCui::Graph::pix2coord(ofVec2f const& pointAsPixels) const {
    ofVec2f pointAsCoord;
    pointAsCoord.x =
        graph_area.x_min +
        float(graph_area.x_max - graph_area.x_min) *
            (float(pointAsPixels.x - view_area.x) / float(view_area.width));
    pointAsCoord.y =
        graph_area.y_min +
        float(graph_area.y_max - graph_area.y_min) *
            (float(pointAsPixels.y - view_area.y) / float(view_area.height));
    return pointAsCoord;
}

ofVec2f ofxCuiCui::Graph::scale2view(ofVec2f const& scaleAsCoord) const {
    return ofVec2f(scaleAsCoord.x * view_area.width /
                       (graph_area.x_max - graph_area.x_min),
                   scaleAsCoord.y * view_area.height /
                       (graph_area.y_max - graph_area.y_min));
}

ofVec2f ofxCuiCui::Graph::scale2graph(ofVec2f const& scaleAsPixels) const {
    return ofVec2f(scaleAsPixels.x * (graph_area.x_max - graph_area.x_min) /
                       view_area.width,
                   scaleAsPixels.y * (graph_area.y_max - graph_area.y_min) /
                       view_area.height);
}

void ofxCuiCui::Graph::mouseScrolled(ofMouseEventArgs& e) {
    // int x, int y, float scrollX, float scrollY
    if (insideViewArea(ofVec2f(e.x, e.y))) {
        if (ofGetKeyPressed(OF_KEY_SUPER)) {
            float translateX =
                0.01 * e.scrollY * (graph_area.x_max - graph_area.x_min);
            float translateY =
                0.01 * e.scrollY * (graph_area.y_max - graph_area.y_min);
            graph_area.x_min +=
                translateX * (e.x - view_area.x) / view_area.width;
            graph_area.x_max -=
                translateX * (1. - (e.x - view_area.x) / view_area.width);
            graph_area.y_min +=
                translateY * (e.y - view_area.y) / view_area.height;
            graph_area.y_max -=
                translateY * (1. - (e.y - view_area.y) / view_area.height);
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
            ofxCuiCui::Graph::BoundsChangedEvent event(this);
            bounds_changed_event_callback_(event);
        }
    }
}

ofxCuiCui::Graph::BoundsChangedEvent::BoundsChangedEvent(
    ofxCuiCui::Graph* sender_)
    : sender(sender_) {}
