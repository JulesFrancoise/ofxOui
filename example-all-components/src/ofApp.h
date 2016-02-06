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
#include "ofxCuiCui.hpp"

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
    ofxCuiCui::Group gui;

    shared_ptr<ofxCuiCui::Numbox> numbox;
    shared_ptr<ofxCuiCui::Slider> slider1;
    shared_ptr<ofxCuiCui::Slider> slider2;
    shared_ptr<ofxCuiCui::MultiSlider> multislider_color;
    shared_ptr<ofxCuiCui::Bpf> bpf;

    void onNumboxEvent(ofxCuiCui::Numbox::ValueEvent& e);
    void onSliderEvent(ofxCuiCui::Slider::ValueEvent& e);
    void onTextInputEvent(ofxCuiCui::TextInput::TextInputEvent& e);
    void onMultiSliderEvent(ofxCuiCui::MultiSlider::ValueEvent& e);
    void onDropDownEvent(ofxCuiCui::DropDown::SelectEvent& e);
};
