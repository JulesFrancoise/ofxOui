/*
 * ofxOuiColormap.cpp
 *
 * Sequential color maps (basic...)
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

#include "ofxOuiColormap.hpp"

map<string, vector<ofColor> > ofxOui::Colormap::fabric_ = {
    {"winter", {ofColor(0, 0, 255), ofColor(0, 255, 127)}},
    {"summer", {ofColor(0, 127, 102), ofColor(255, 255, 102)}},
    {"spring", {ofColor(255, 0, 255), ofColor(255, 255, 0)}},
    {"autumn", {ofColor(255, 0, 0), ofColor(255, 255, 0)}},
    {"bw", {ofColor(0, 0, 0), ofColor(255, 255, 255)}},
};

ofxOui::Colormap::Colormap() {
    values.resize(2);
    setByName("winter");
}

ofxOui::Colormap::~Colormap() {}

bool ofxOui::Colormap::setByName(string name) {
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    auto it = fabric_.find(name);
    if (it != fabric_.end()) {
        base_colors_ = fabric_.at(name);
        current_map_name_ = name;
        generateValues();
        return true;
    }
    return false;
}

void ofxOui::Colormap::setBaseColors(vector<ofColor> colors) {
    if (colors.size() != 2) {
        std::cout << "COLORMAP WARNING: Only 2-sequential colormaps are "
                     "supported at the moment"
                  << endl;
        return;
    }
    base_colors_ = colors;
    current_map_name_ = "custom";
    generateValues();
}

string ofxOui::Colormap::getName() const { return current_map_name_; }

void ofxOui::Colormap::resize(int num_values) {
    num_values = (num_values < 2) ? 2 : num_values;
    values.resize(num_values);
    generateValues();
}

void ofxOui::Colormap::generateValues() {
    int num_values = values.size();
    for (int i = 0; i < num_values; i++) {
        float factor = float(i) / float(num_values - 1);
        values[i] = base_colors_[0] * (1 - factor) + base_colors_[1] * factor;
    }
}
