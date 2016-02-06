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

    shared_ptr<ofxCuiCui::Label> label = make_shared<ofxCuiCui::Label>();
    if (gui.addComponent(label, 0, 0, 1, 3)) {
        label->font.setFontSize(18);
        label->style = ofxCuiCui::Style::Label;
        label->labelOff = "Buttons";
    }

    shared_ptr<ofxCuiCui::Button> button = make_shared<ofxCuiCui::Button>();
    if (gui.addComponent(button, 1, 0)) {
        button->labelOff = button->labelOn = "A";
        button->shape = ofxCuiCui::Shape::Circle;
    }
    button = make_shared<ofxCuiCui::Button>();
    if (gui.addComponent(button, 1, 1)) {
        button->labelOff = button->labelOn = "B";
        button->shape = ofxCuiCui::Shape::Circle;
    }
    button = make_shared<ofxCuiCui::Button>();
    if (gui.addComponent(button, 1, 2)) {
        button->labelOff = button->labelOn = "C";
        button->shape = ofxCuiCui::Shape::Circle;
    }

    button = make_shared<ofxCuiCui::Button>();
    if (gui.addComponent(button, 2, 0, 1, 3)) {
        button->labelOff = "toggle: off";
        button->labelOn = "toggle: on";
        button->toggle = true;
        button->shape = ofxCuiCui::Shape::RectRounded;
    }

    button = make_shared<ofxCuiCui::Button>();
    if (gui.addComponent(button, 3, 0, 1, 3)) {
        button->labelOff = "button: disabled";
        button->disabled = true;
        button->shape = ofxCuiCui::Shape::Rectangle;
    }

    shared_ptr<ofxCuiCui::CheckBox> checkbox =
        make_shared<ofxCuiCui::CheckBox>();
    if (gui.addComponent(checkbox, 4, 0, 1, 3)) {
        checkbox->labelOff = checkbox->labelOn = "checkbox";
        checkbox->shape = ofxCuiCui::Shape::RectRounded;
    }

    button = make_shared<ofxCuiCui::Button>();
    if (gui.addComponent(button, 5, 0, 1, 3)) {
        button->labelOff = "toggle: off";
        button->labelOn = "toggle: on";
        button->toggle = true;
        button->style = ofxCuiCui::Style::FramedYellow;
        button->shape = ofxCuiCui::Shape::RectRounded;
    }

    shared_ptr<ofxCuiCui::Matrix> matrix = make_shared<ofxCuiCui::Matrix>();
    if (gui.addComponent(matrix, 6, 0, 3, 3)) {
        matrix->labelOff = matrix->labelOn = "matrix";
        matrix->toggle = true;
        matrix->style = ofxCuiCui::Style::PlainYellow;
        matrix->rows = 3;
        matrix->cols = 5;
    }

    label = make_shared<ofxCuiCui::Label>();
    if (gui.addComponent(label, 0, 3, 1, 3)) {
        label->font.setFontSize(18);
        label->style = ofxCuiCui::Style::Label;
        label->labelOff = "Numbox & Sliders";
    }

    numbox = make_shared<ofxCuiCui::Numbox>();
    if (gui.addComponent(numbox, 1, 3, 1, 3)) {
        numbox->labelOff = numbox->labelOn = "Numbox";
        numbox->precision = 3;
        numbox->min = -1.;
        numbox->max = 1.;
        numbox->onEditValue(this, &ofApp::onNumboxEvent);
    }

    slider1 = make_shared<ofxCuiCui::Slider>();
    if (gui.addComponent(slider1, 2, 3, 1, 3)) {
        slider1->labelOff = slider1->labelOn = "Slider 1";
        slider1->min = -1.;
        slider1->max = 1.;
        slider1->precision = 1;
        slider1->onEditValue(this, &ofApp::onSliderEvent);
    }

    slider2 = make_shared<ofxCuiCui::Slider>();
    if (gui.addComponent(slider2, 3, 3, 1, 3)) {
        slider2->labelOff = slider2->labelOn = "Slider 2";
        slider2->min = -1.;
        slider2->max = 1.;
        slider2->precision = 3;
        slider2->origin = ofxCuiCui::Slider::Origin::Zero;
        slider2->onEditValue(this, &ofApp::onSliderEvent);
    }
    ofxCuiCui::Slider::ValueEvent e(nullptr, 0.234);
    onSliderEvent(e);

    shared_ptr<ofxCuiCui::Slider> slider3 = make_shared<ofxCuiCui::Slider>();
    if (gui.addComponent(slider3, 4, 3, 2, 1)) {
        slider3->labelOff = slider3->labelOn = "blablah";
        slider3->precision = 0;
        slider3->min = 0;
        slider3->max = 100;
        slider3->layout = ofxCuiCui::Slider::Layout::Vertical;
        slider3->style = ofxCuiCui::Style::PlainDarkblue;
    }

    multislider_color = make_shared<ofxCuiCui::MultiSlider>();
    if (gui.addComponent(multislider_color, 4, 4, 2, 2)) {
        multislider_color->labelOff = multislider_color->labelOn =
            "multislider";
        multislider_color->min = 0;
        multislider_color->max = 255;
        multislider_color->values = {0., 0., 0.};
        multislider_color->layout = ofxCuiCui::MultiSlider::Layout::Vertical;
        multislider_color->style = ofxCuiCui::Style::PlainDarkblue;
        multislider_color->onEditSlider(this, &ofApp::onMultiSliderEvent);
        ofxCuiCui::MultiSlider::ValueEvent e(nullptr, 0, 0.);
        for (int i = 0; i < 3; i++) {
            e.index = i;
            onMultiSliderEvent(e);
        }
    }

    shared_ptr<ofxCuiCui::MultiSlider> multislider =
        make_shared<ofxCuiCui::MultiSlider>();
    if (gui.addComponent(multislider, 6, 3, 3, 3)) {
        multislider->labelOff = multislider->labelOn = "multislider";
        multislider->min = -1.;
        multislider->max = 1.;
        multislider->values = {0.2, -0.6, 0.9, 0.7, 0., -0.5};
        multislider->style = ofxCuiCui::Style::PlainBlue;
    }

    label = make_shared<ofxCuiCui::Label>();
    if (gui.addComponent(label, 0, 6, 1, 3)) {
        label->font.setFontSize(18);
        label->style = ofxCuiCui::Style::Label;
        label->labelOff = "Other Stuff";
    }

    shared_ptr<ofxCuiCui::TextInput> textinput =
        make_shared<ofxCuiCui::TextInput>();
    if (gui.addComponent(textinput, 1, 6, 1, 3)) {
        textinput->style = ofxCuiCui::Style::PlainBlue;
        textinput->labelOff = "Text input";
        textinput->labelOn = "Text input";
        textinput->onTextInput(this, &ofApp::onTextInputEvent);
    }

    bpf = make_shared<ofxCuiCui::Bpf>();
    if (gui.addComponent(bpf, 2, 6, 2, 3)) {
        bpf->labelOff = bpf->labelOn = "BPF";
        bpf->values = {
            {0., 1.}, {1., 1.5}, {3., -0.5}, {4.3, 0.},
        };
        bpf->clipBounds();
        bpf->style = ofxCuiCui::Style::PlainGray;
    }

    shared_ptr<ofxCuiCui::DropDown> dropdown =
        make_shared<ofxCuiCui::DropDown>();
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
void ofApp::onNumboxEvent(ofxCuiCui::Numbox::ValueEvent& e) {
    slider1->value = e.value;
    slider2->value = e.value;
    if (e.value < 0.) {
        slider1->style = ofxCuiCui::Style::PlainRed;
        slider2->style = ofxCuiCui::Style::PlainRed;
        numbox->style = ofxCuiCui::Style::PlainRed;
    } else {
        slider1->style = ofxCuiCui::Style::PlainGreen;
        slider2->style = ofxCuiCui::Style::PlainGreen;
        numbox->style = ofxCuiCui::Style::PlainGreen;
    }
}

//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxCuiCui::Slider::ValueEvent& e) {
    numbox->value = e.value;
    slider1->value = e.value;
    slider2->value = e.value;
    if (e.value < 0.) {
        slider1->style = ofxCuiCui::Style::PlainRed;
        slider2->style = ofxCuiCui::Style::PlainRed;
        numbox->style = ofxCuiCui::Style::PlainRed;
    } else {
        slider1->style = ofxCuiCui::Style::PlainGreen;
        slider2->style = ofxCuiCui::Style::PlainGreen;
        numbox->style = ofxCuiCui::Style::PlainGreen;
    }
}

void ofApp::onTextInputEvent(ofxCuiCui::TextInput::TextInputEvent& e) {
    bpf->labelOff = bpf->labelOn = e.text;
}

void ofApp::onMultiSliderEvent(ofxCuiCui::MultiSlider::ValueEvent& e) {
    ofColor base_color = multislider_color->style.background_color_on;
    base_color[e.index] = max(float(0.), min(float(255.), e.value));
    base_color[3] = 255.;
    multislider_color->style.background_color_on = base_color;
    multislider_color->style.background_color_on_hover = base_color;
    multislider_color->style.background_color_off = base_color;
    multislider_color->style.background_color_off_hover = base_color;
}

void ofApp::onDropDownEvent(ofxCuiCui::DropDown::SelectEvent& e) {
    if (e.text == "Lines") {
        bpf->appearance = ofxCuiCui::Bpf::Appearance::Lines;
    } else if (e.text == "FillBottom") {
        bpf->appearance = ofxCuiCui::Bpf::Appearance::FillBottom;
    } else if (e.text == "FillTop") {
        bpf->appearance = ofxCuiCui::Bpf::Appearance::FillTop;
    } else {
        bpf->appearance = ofxCuiCui::Bpf::Appearance::FillZero;
    }
}
