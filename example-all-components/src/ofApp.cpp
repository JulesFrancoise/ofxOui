/*
 * ofApp.cpp
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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(50);
    ofSetBackgroundColor(ofColor::white);

    gui.width = ofGetWindowWidth();
    gui.height = ofGetWindowHeight();

    shared_ptr<ofxOui::Label> label = make_shared<ofxOui::Label>();
    if (gui.addComponent(label, 0, 0, 1, 3)) {
        label->font.setFontSize(18);
        label->style = ofxOui::Style::Label;
        label->labelOff = "Buttons";
    }

    shared_ptr<ofxOui::Button> button = make_shared<ofxOui::Button>();
    if (gui.addComponent(button, 1, 0)) {
        button->labelOff = button->labelOn = "A";
        button->shape = ofxOui::Shape::Circle;
    }
    button = make_shared<ofxOui::Button>();
    if (gui.addComponent(button, 1, 1)) {
        button->labelOff = button->labelOn = "B";
        button->shape = ofxOui::Shape::Circle;
    }
    button = make_shared<ofxOui::Button>();
    if (gui.addComponent(button, 1, 2)) {
        button->labelOff = button->labelOn = "C";
        button->shape = ofxOui::Shape::Circle;
    }

    button = make_shared<ofxOui::Button>();
    if (gui.addComponent(button, 2, 0, 1, 3)) {
        button->labelOff = "toggle: off";
        button->labelOn = "toggle: on";
        button->toggle = true;
        button->shape = ofxOui::Shape::RectRounded;
    }

    button = make_shared<ofxOui::Button>();
    if (gui.addComponent(button, 3, 0, 1, 3)) {
        button->labelOff = "button: disabled";
        button->disabled = true;
        button->shape = ofxOui::Shape::Rectangle;
    }

    shared_ptr<ofxOui::CheckBox> checkbox =
        make_shared<ofxOui::CheckBox>();
    if (gui.addComponent(checkbox, 4, 0, 1, 3)) {
        checkbox->labelOff = checkbox->labelOn = "checkbox";
        checkbox->shape = ofxOui::Shape::RectRounded;
    }

    button = make_shared<ofxOui::Button>();
    if (gui.addComponent(button, 5, 0, 1, 3)) {
        button->labelOff = "toggle: off";
        button->labelOn = "toggle: on";
        button->toggle = true;
        button->style = ofxOui::Style::FramedYellow;
        button->shape = ofxOui::Shape::RectRounded;
    }

    shared_ptr<ofxOui::Matrix> matrix = make_shared<ofxOui::Matrix>();
    if (gui.addComponent(matrix, 6, 0, 3, 3)) {
        matrix->labelOff = matrix->labelOn = "matrix";
        matrix->toggle = true;
        matrix->style = ofxOui::Style::PlainYellow;
        matrix->rows = 3;
        matrix->cols = 5;
    }

    label = make_shared<ofxOui::Label>();
    if (gui.addComponent(label, 0, 3, 1, 3)) {
        label->font.setFontSize(18);
        label->style = ofxOui::Style::Label;
        label->labelOff = "Numbox & Sliders";
    }

    numbox = make_shared<ofxOui::Numbox>();
    if (gui.addComponent(numbox, 1, 3, 1, 3)) {
        numbox->labelOff = numbox->labelOn = "Numbox";
        numbox->precision = 3;
        numbox->min = -1.;
        numbox->max = 1.;
        numbox->onEditValue(this, &ofApp::onNumboxEvent);
    }

    slider1 = make_shared<ofxOui::Slider>();
    if (gui.addComponent(slider1, 2, 3, 1, 3)) {
        slider1->labelOff = slider1->labelOn = "Slider 1";
        slider1->min = -1.;
        slider1->max = 1.;
        slider1->precision = 1;
        slider1->onEditValue(this, &ofApp::onSliderEvent);
    }

    slider2 = make_shared<ofxOui::Slider>();
    if (gui.addComponent(slider2, 3, 3, 1, 3)) {
        slider2->labelOff = slider2->labelOn = "Slider 2";
        slider2->min = -1.;
        slider2->max = 1.;
        slider2->precision = 3;
        slider2->origin = ofxOui::Slider::Origin::Zero;
        slider2->onEditValue(this, &ofApp::onSliderEvent);
    }
    ofxOui::Slider::ValueEvent e(nullptr, 0.234);
    onSliderEvent(e);

    shared_ptr<ofxOui::Slider> slider3 = make_shared<ofxOui::Slider>();
    if (gui.addComponent(slider3, 4, 3, 2, 1)) {
        slider3->labelOff = slider3->labelOn = "blablah";
        slider3->precision = 0;
        slider3->min = 0;
        slider3->max = 100;
        slider3->layout = ofxOui::Slider::Layout::Vertical;
        slider3->style = ofxOui::Style::PlainDarkblue;
    }

    multislider_color = make_shared<ofxOui::MultiSlider>();
    if (gui.addComponent(multislider_color, 4, 4, 2, 2)) {
        multislider_color->labelOff = multislider_color->labelOn =
            "multislider";
        multislider_color->min = 0;
        multislider_color->max = 255;
        multislider_color->values = {0., 0., 0.};
        multislider_color->layout = ofxOui::MultiSlider::Layout::Vertical;
        multislider_color->style = ofxOui::Style::PlainDarkblue;
        multislider_color->onEditSlider(this, &ofApp::onMultiSliderEvent);
        ofxOui::MultiSlider::ValueEvent e(nullptr, 0, 0.);
        for (int i = 0; i < 3; i++) {
            e.index = i;
            onMultiSliderEvent(e);
        }
    }

    shared_ptr<ofxOui::MultiSlider> multislider =
        make_shared<ofxOui::MultiSlider>();
    if (gui.addComponent(multislider, 6, 3, 3, 3)) {
        multislider->labelOff = multislider->labelOn = "multislider";
        multislider->min = -1.;
        multislider->max = 1.;
        multislider->values = {0.2, -0.6, 0.9, 0.7, 0., -0.5};
        multislider->style = ofxOui::Style::PlainBlue;
    }

    label = make_shared<ofxOui::Label>();
    if (gui.addComponent(label, 0, 6, 1, 3)) {
        label->font.setFontSize(18);
        label->style = ofxOui::Style::Label;
        label->labelOff = "Other Stuff";
    }

    shared_ptr<ofxOui::TextInput> textinput =
        make_shared<ofxOui::TextInput>();
    if (gui.addComponent(textinput, 1, 6, 1, 3)) {
        textinput->style = ofxOui::Style::PlainBlue;
        textinput->labelOff = "Text input";
        textinput->labelOn = "Text input";
        textinput->onTextInput(this, &ofApp::onTextInputEvent);
    }

    bpf = make_shared<ofxOui::Bpf>();
    if (gui.addComponent(bpf, 2, 6, 2, 3)) {
        bpf->labelOff = bpf->labelOn = "BPF";
        bpf->values = {
            {0., 1.}, {1., 1.5}, {3., -0.5}, {4.3, 0.},
        };
        bpf->clipBounds();
        bpf->style = ofxOui::Style::PlainGray;
    }

    shared_ptr<ofxOui::DropDown> dropdown =
        make_shared<ofxOui::DropDown>();
    if (gui.addComponent(dropdown, 4, 6, 1, 3)) {
        dropdown->labelOff = dropdown->labelOn = "BPF Appearance";
        dropdown->items = {"Lines", "FillBottom", "FillTop", "FillZero"};
        dropdown->onSelect(this, &ofApp::onDropDownEvent);
    }

    gui.setup();
}

//--------------------------------------------------------------
void ofApp::update() { gui.update(); }

//--------------------------------------------------------------
void ofApp::draw() { gui.draw(); }

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    gui.width = ofGetWindowWidth();
    gui.height = ofGetWindowHeight();
    gui.setup();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

//--------------------------------------------------------------
void ofApp::onNumboxEvent(ofxOui::Numbox::ValueEvent& e) {
    slider1->value = e.value;
    slider2->value = e.value;
    if (e.value < 0.) {
        slider1->style = ofxOui::Style::PlainRed;
        slider2->style = ofxOui::Style::PlainRed;
        numbox->style = ofxOui::Style::PlainRed;
    } else {
        slider1->style = ofxOui::Style::PlainGreen;
        slider2->style = ofxOui::Style::PlainGreen;
        numbox->style = ofxOui::Style::PlainGreen;
    }
}

//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxOui::Slider::ValueEvent& e) {
    numbox->value = e.value;
    slider1->value = e.value;
    slider2->value = e.value;
    if (e.value < 0.) {
        slider1->style = ofxOui::Style::PlainRed;
        slider2->style = ofxOui::Style::PlainRed;
        numbox->style = ofxOui::Style::PlainRed;
    } else {
        slider1->style = ofxOui::Style::PlainGreen;
        slider2->style = ofxOui::Style::PlainGreen;
        numbox->style = ofxOui::Style::PlainGreen;
    }
}

void ofApp::onTextInputEvent(ofxOui::TextInput::TextInputEvent& e) {
    bpf->labelOff = bpf->labelOn = e.text;
}

void ofApp::onMultiSliderEvent(ofxOui::MultiSlider::ValueEvent& e) {
    ofColor base_color = multislider_color->style.background_color_on;
    base_color[e.index] = max(float(0.), min(float(255.), e.value));
    base_color[3] = 255.;
    multislider_color->style.background_color_on = base_color;
    multislider_color->style.background_color_on_hover = base_color;
    multislider_color->style.background_color_off = base_color;
    multislider_color->style.background_color_off_hover = base_color;
}

void ofApp::onDropDownEvent(ofxOui::DropDown::SelectEvent& e) {
    if (e.text == "Lines") {
        bpf->appearance = ofxOui::Bpf::Appearance::Lines;
    } else if (e.text == "FillBottom") {
        bpf->appearance = ofxOui::Bpf::Appearance::FillBottom;
    } else if (e.text == "FillTop") {
        bpf->appearance = ofxOui::Bpf::Appearance::FillTop;
    } else {
        bpf->appearance = ofxOui::Bpf::Appearance::FillZero;
    }
}
