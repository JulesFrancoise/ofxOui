/*
 * ofxCuiCuiStyle.cpp
 *
 * Jui Style Sheets
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

#include "ofxCuiCuiStyle.hpp"

const ofxCuiCui::Style ofxCuiCui::Style::Default({
    ofColor(26, 188, 166, 255),   //  background_color_off
    ofColor(72, 201, 176, 255),   //  background_color_off_hover
    ofColor(22, 160, 133, 255),   //  background_color_on
    ofColor(22, 160, 133, 255),   //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(255, 255, 255, 255),  //  font_color_off
    ofColor(255, 255, 255, 255),  //  font_color_off_hover
    ofColor(255, 255, 255, 255),  //  font_color_on
    ofColor(255, 255, 255, 255),  //  font_color_on_hover
    ofColor(200, 200, 200, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(255, 255, 255, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::FramedDefault({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(26, 188, 166, 255),   //  frame_color_off
    ofColor(72, 201, 176, 255),   //  frame_color_off_hover
    ofColor(22, 160, 133, 255),   //  frame_color_on
    ofColor(22, 160, 133, 255),   //  frame_color_on_hover
    ofColor(26, 188, 166, 255),   //  font_color_off
    ofColor(72, 201, 176, 255),   //  font_color_off_hover
    ofColor(22, 160, 133, 255),   //  font_color_on
    ofColor(22, 160, 133, 255),   //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(200, 200, 200, 255),  //  frame_color_disabled
    ofColor(200, 200, 200, 255),  //  font_color_disabled
    3,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::PlainBlue({
    ofColor(52, 152, 219, 255),   //  background_color_off
    ofColor(93, 173, 226, 255),   //  background_color_off_hover
    ofColor(44, 129, 186, 255),   //  background_color_on
    ofColor(44, 129, 186, 255),   //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(255, 255, 255, 255),  //  font_color_off
    ofColor(255, 255, 255, 255),  //  font_color_off_hover
    ofColor(255, 255, 255, 255),  //  font_color_on
    ofColor(255, 255, 255, 255),  //  font_color_on_hover
    ofColor(200, 200, 200, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(255, 255, 255, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::FramedBlue({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(52, 152, 219, 255),   //  frame_color_off
    ofColor(93, 173, 226, 255),   //  frame_color_off_hover
    ofColor(44, 129, 186, 255),   //  frame_color_on
    ofColor(44, 129, 186, 255),   //  frame_color_on_hover
    ofColor(52, 152, 219, 255),   //  font_color_off
    ofColor(93, 173, 226, 255),   //  font_color_off_hover
    ofColor(44, 129, 186, 255),   //  font_color_on
    ofColor(44, 129, 186, 255),   //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(200, 200, 200, 255),  //  frame_color_disabled
    ofColor(200, 200, 200, 255),  //  font_color_disabled
    3,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::PlainGreen({
    ofColor(46, 204, 113, 255),   //  background_color_off
    ofColor(88, 214, 141, 255),   //  background_color_off_hover
    ofColor(39, 173, 6, 255),     //  background_color_on
    ofColor(39, 173, 6, 255),     //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(255, 255, 255, 255),  //  font_color_off
    ofColor(255, 255, 255, 255),  //  font_color_off_hover
    ofColor(255, 255, 255, 255),  //  font_color_on
    ofColor(255, 255, 255, 255),  //  font_color_on_hover
    ofColor(200, 200, 200, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(255, 255, 255, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::FramedGreen({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(46, 204, 113, 255),   //  frame_color_off
    ofColor(88, 214, 141, 255),   //  frame_color_off_hover
    ofColor(39, 173, 6, 255),     //  frame_color_on
    ofColor(39, 173, 6, 255),     //  frame_color_on_hover
    ofColor(46, 204, 113, 255),   //  font_color_off
    ofColor(88, 214, 141, 255),   //  font_color_off_hover
    ofColor(39, 173, 6, 255),     //  font_color_on
    ofColor(39, 173, 6, 255),     //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(200, 200, 200, 255),  //  frame_color_disabled
    ofColor(200, 200, 200, 255),  //  font_color_disabled
    3,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::PlainRed({
    ofColor(231, 76, 60, 255),    //  background_color_off
    ofColor(236, 112, 99, 255),   //  background_color_off_hover
    ofColor(196, 65, 51, 255),    //  background_color_on
    ofColor(196, 65, 51, 255),    //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(255, 255, 255, 255),  //  font_color_off
    ofColor(255, 255, 255, 255),  //  font_color_off_hover
    ofColor(255, 255, 255, 255),  //  font_color_on
    ofColor(255, 255, 255, 255),  //  font_color_on_hover
    ofColor(200, 200, 200, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(255, 255, 255, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::FramedRed({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(231, 76, 60, 255),    //  frame_color_off
    ofColor(236, 112, 99, 255),   //  frame_color_off_hover
    ofColor(196, 65, 51, 255),    //  frame_color_on
    ofColor(196, 65, 51, 255),    //  frame_color_on_hover
    ofColor(231, 76, 60, 255),    //  font_color_off
    ofColor(236, 112, 99, 255),   //  font_color_off_hover
    ofColor(196, 65, 51, 255),    //  font_color_on
    ofColor(196, 65, 51, 255),    //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(200, 200, 200, 255),  //  frame_color_disabled
    ofColor(200, 200, 200, 255),  //  font_color_disabled
    3,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::Label({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(100, 100, 100, 255),  //  font_color_off
    ofColor(100, 100, 100, 255),  //  font_color_off_hover
    ofColor(100, 100, 100, 255),  //  font_color_on
    ofColor(100, 100, 100, 255),  //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(100, 100, 100, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::PlainGray({
    ofColor(189, 195, 199, 255),  //  background_color_off
    ofColor(202, 207, 210, 255),  //  background_color_off_hover
    ofColor(161, 166, 169, 255),  //  background_color_on
    ofColor(161, 166, 169, 255),  //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(255, 255, 255, 255),  //  font_color_off
    ofColor(255, 255, 255, 255),  //  font_color_off_hover
    ofColor(255, 255, 255, 255),  //  font_color_on
    ofColor(255, 255, 255, 255),  //  font_color_on_hover
    ofColor(200, 200, 200, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(255, 255, 255, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::FramedGray({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(189, 195, 199, 255),  //  frame_color_off
    ofColor(202, 207, 210, 255),  //  frame_color_off_hover
    ofColor(161, 166, 169, 255),  //  frame_color_on
    ofColor(161, 166, 169, 255),  //  frame_color_on_hover
    ofColor(189, 195, 199, 255),  //  font_color_off
    ofColor(202, 207, 210, 255),  //  font_color_off_hover
    ofColor(161, 166, 169, 255),  //  font_color_on
    ofColor(161, 166, 169, 255),  //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(200, 200, 200, 255),  //  frame_color_disabled
    ofColor(200, 200, 200, 255),  //  font_color_disabled
    3,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::PlainYellow({
    ofColor(241, 196, 15, 255),   //  background_color_off
    ofColor(244, 211, 19, 255),   //  background_color_off_hover
    ofColor(205, 167, 13, 255),   //  background_color_on
    ofColor(205, 167, 13, 255),   //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(255, 255, 255, 255),  //  font_color_off
    ofColor(255, 255, 255, 255),  //  font_color_off_hover
    ofColor(255, 255, 255, 255),  //  font_color_on
    ofColor(255, 255, 255, 255),  //  font_color_on_hover
    ofColor(200, 200, 200, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(255, 255, 255, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::FramedYellow({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(241, 196, 15, 255),   //  frame_color_off
    ofColor(244, 211, 19, 255),   //  frame_color_off_hover
    ofColor(205, 167, 13, 255),   //  frame_color_on
    ofColor(205, 167, 13, 255),   //  frame_color_on_hover
    ofColor(241, 196, 15, 255),   //  font_color_off
    ofColor(244, 211, 19, 255),   //  font_color_off_hover
    ofColor(205, 167, 13, 255),   //  font_color_on
    ofColor(205, 167, 13, 255),   //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(200, 200, 200, 255),  //  frame_color_disabled
    ofColor(200, 200, 200, 255),  //  font_color_disabled
    3,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::PlainDarkblue({
    ofColor(52, 73, 94, 255),     //  background_color_off
    ofColor(65, 91, 118, 255),    //  background_color_off_hover
    ofColor(44, 62, 80, 255),     //  background_color_on
    ofColor(44, 62, 80, 255),     //  background_color_on_hover
    ofColor(255, 255, 255, 255),  //  frame_color_off
    ofColor(255, 255, 255, 255),  //  frame_color_off_hover
    ofColor(255, 255, 255, 255),  //  frame_color_on
    ofColor(255, 255, 255, 255),  //  frame_color_on_hover
    ofColor(255, 255, 255, 255),  //  font_color_off
    ofColor(255, 255, 255, 255),  //  font_color_off_hover
    ofColor(255, 255, 255, 255),  //  font_color_on
    ofColor(255, 255, 255, 255),  //  font_color_on_hover
    ofColor(200, 200, 200, 255),  //  background_color_disabled
    ofColor(255, 255, 255, 255),  //  frame_color_disabled
    ofColor(255, 255, 255, 255),  //  font_color_disabled
    0,                            // frame_width
    7,                            // roundness
});
const ofxCuiCui::Style ofxCuiCui::Style::FramedDarkblue({
    ofColor(255, 255, 255, 255),  //  background_color_off
    ofColor(255, 255, 255, 255),  //  background_color_off_hover
    ofColor(255, 255, 255, 255),  //  background_color_on
    ofColor(255, 255, 255, 255),  //  background_color_on_hover
    ofColor(52, 73, 94, 255),     //  frame_color_off
    ofColor(65, 91, 118, 255),    //  frame_color_off_hover
    ofColor(44, 62, 80, 255),     //  frame_color_on
    ofColor(44, 62, 80, 255),     //  frame_color_on_hover
    ofColor(52, 73, 94, 255),     //  font_color_off
    ofColor(65, 91, 118, 255),    //  font_color_off_hover
    ofColor(44, 62, 80, 255),     //  font_color_on
    ofColor(44, 62, 80, 255),     //  font_color_on_hover
    ofColor(255, 255, 255, 255),  //  background_color_disabled
    ofColor(200, 200, 200, 255),  //  frame_color_disabled
    ofColor(200, 200, 200, 255),  //  font_color_disabled
    3,                            // frame_width
    7,                            // roundness
});

ofxCuiCui::Style::Style() : ofxCuiCui::Style(ofxCuiCui::Style::Default) {}

ofxCuiCui::Style::Style(ofxCuiCui::Style const& src)
    : background_color_off(src.background_color_off),
      background_color_off_hover(src.background_color_off_hover),
      background_color_on_hover(src.background_color_on_hover),
      background_color_on(src.background_color_on),
      frame_color_off(src.frame_color_off),
      frame_color_off_hover(src.frame_color_off_hover),
      frame_color_on(src.frame_color_on),
      frame_color_on_hover(src.frame_color_on_hover),
      font_color_off(src.font_color_off),
      font_color_off_hover(src.font_color_off_hover),
      font_color_on(src.font_color_on),
      font_color_on_hover(src.font_color_on_hover),
      background_color_disabled(src.background_color_disabled),
      frame_color_disabled(src.frame_color_disabled),
      font_color_disabled(src.font_color_disabled),
      frame_width(src.frame_width),
      roundness(src.roundness) {}

ofxCuiCui::Style& ofxCuiCui::Style::operator=(ofxCuiCui::Style const& src) {
    if (this != &src) {
        background_color_off = src.background_color_off;
        background_color_off_hover = src.background_color_off_hover;
        background_color_on = src.background_color_on;
        background_color_on_hover = src.background_color_on_hover;
        frame_color_off = src.frame_color_off;
        frame_color_off_hover = src.frame_color_off_hover;
        frame_color_on = src.frame_color_on;
        frame_color_on_hover = src.frame_color_on_hover;
        font_color_off = src.font_color_off;
        font_color_off_hover = src.font_color_off_hover;
        font_color_on = src.font_color_on;
        font_color_on_hover = src.font_color_on_hover;
        background_color_disabled = src.background_color_disabled;
        frame_color_disabled = src.frame_color_disabled;
        font_color_disabled = src.font_color_disabled;
        frame_width = src.frame_width;
        roundness = src.roundness;
    }
    return *this;
}

ofxCuiCui::Style::Style(
    ofColor background_color_off_, ofColor background_color_off_hover_,
    ofColor background_color_on_, ofColor background_color_on_hover_,
    ofColor frame_color_off_, ofColor frame_color_off_hover_,
    ofColor frame_color_on_, ofColor frame_color_on_hover_,
    ofColor font_color_off_, ofColor font_color_off_hover_,
    ofColor font_color_on_, ofColor font_color_on_hover_,
    ofColor background_color_disabled_, ofColor frame_color_disabled_,
    ofColor font_color_disabled_, int frame_width_, int roundness_)
    : background_color_off(background_color_off_),
      background_color_off_hover(background_color_off_hover_),
      background_color_on(background_color_on_),
      background_color_on_hover(background_color_on_hover_),
      frame_color_off(frame_color_off_),
      frame_color_off_hover(frame_color_off_hover_),
      frame_color_on(frame_color_on_),
      frame_color_on_hover(frame_color_on_hover_),
      font_color_off(font_color_off_),
      font_color_off_hover(font_color_off_hover_),
      font_color_on(font_color_on_),
      font_color_on_hover(font_color_on_hover_),
      background_color_disabled(background_color_disabled_),
      frame_color_disabled(frame_color_disabled_),
      font_color_disabled(font_color_disabled_),
      frame_width(frame_width_),
      roundness(roundness_) {}

ofxCuiCui::Style::~Style() {}
