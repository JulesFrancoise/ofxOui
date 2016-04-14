/*
 * ofApp.hpp
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

#pragma once

#include "ofMain.h"
#include "ofxOui.hpp"

class ofApp : public ofBaseApp {
  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

  protected:
    ofxOui::Group gui;

    shared_ptr<ofxOui::Numbox> numbox;
    shared_ptr<ofxOui::Slider> slider1;
    shared_ptr<ofxOui::Slider> slider2;
    shared_ptr<ofxOui::MultiSlider> multislider_color;
    shared_ptr<ofxOui::Bpf> bpf;

    void onNumboxEvent(ofxOui::Numbox::ValueEvent& e);
    void onSliderEvent(ofxOui::Slider::ValueEvent& e);
    void onTextInputEvent(ofxOui::TextInput::TextInputEvent& e);
    void onMultiSliderEvent(ofxOui::MultiSlider::ValueEvent& e);
    void onDropDownEvent(ofxOui::DropDown::SelectEvent& e);
};
