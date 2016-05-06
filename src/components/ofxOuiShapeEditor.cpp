/*
 * ofxOui::ShapeEditor.cpp
 *
 * Shape Editor (Modes : translation, scaling, rotation)
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

#include "ofxOuiShapeEditor.hpp"

ofxOui::ShapeEditor::ShapeEditor(float x_, float y_, float width_,
                                 float height_, float angle_)
    : x(x_),
      y(y_),
      width(width_),
      height(height_),
      angle(angle_),
      frame_width(3),
      color(ofColor::darkGray),
      selector_size(20),
      dragging_(Selector::None),
      dragging_mode_(MouseDraggingMode::Normal) {
    ofAddListener(ofEvents().mousePressed, this,
                  &ofxOui::ShapeEditor::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this,
                  &ofxOui::ShapeEditor::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this,
                  &ofxOui::ShapeEditor::mouseReleased);
    ofAddListener(ofEvents().keyPressed, this,
                  &ofxOui::ShapeEditor::keyPressed);
    ofAddListener(ofEvents().keyReleased, this,
                  &ofxOui::ShapeEditor::keyReleased);
}

ofxOui::ShapeEditor::~ShapeEditor() {
    ofRemoveListener(ofEvents().mousePressed, this,
                     &ofxOui::ShapeEditor::mousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this,
                     &ofxOui::ShapeEditor::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this,
                     &ofxOui::ShapeEditor::mouseReleased);
    ofRemoveListener(ofEvents().keyPressed, this,
                     &ofxOui::ShapeEditor::keyPressed);

    ofRemoveListener(ofEvents().keyReleased, this,
                     &ofxOui::ShapeEditor::keyReleased);
}

void ofxOui::ShapeEditor::draw() {
    ofTranslate(x, y);
    ofRotate(angle * 180. / M_PI);

    ofNoFill();
    ofSetLineWidth(frame_width);
    ofSetColor(color);
    ofDrawRectangle(-width / 2, -height / 2, width, height);
    (dragging_ == Selector::TopLeft) ? ofFill() : ofNoFill();
    ofDrawRectangle(-width / 2 - selector_size / 2,
                    -height / 2 - selector_size / 2, selector_size,
                    selector_size);
    (dragging_ == Selector::TopCenter) ? ofFill() : ofNoFill();
    ofDrawRectangle(-selector_size / 2, -height / 2 - selector_size / 2,
                    selector_size, selector_size);
    (dragging_ == Selector::TopRight) ? ofFill() : ofNoFill();
    ofDrawRectangle(width / 2 - selector_size / 2,
                    -height / 2 - selector_size / 2, selector_size,
                    selector_size);
    (dragging_ == Selector::MiddleRight) ? ofFill() : ofNoFill();
    ofDrawRectangle(width / 2 - selector_size / 2, -selector_size / 2,
                    selector_size, selector_size);
    (dragging_ == Selector::BottomRight) ? ofFill() : ofNoFill();
    ofDrawRectangle(width / 2 - selector_size / 2,
                    height / 2 - selector_size / 2, selector_size,
                    selector_size);
    (dragging_ == Selector::BottomCenter) ? ofFill() : ofNoFill();
    ofDrawRectangle(-selector_size / 2, height / 2 - selector_size / 2,
                    selector_size, selector_size);
    (dragging_ == Selector::BottomLeft) ? ofFill() : ofNoFill();
    ofDrawRectangle(-width / 2 - selector_size / 2,
                    height / 2 - selector_size / 2, selector_size,
                    selector_size);
    (dragging_ == Selector::MiddleLeft) ? ofFill() : ofNoFill();
    ofDrawRectangle(-width / 2 - selector_size / 2, -selector_size / 2,
                    selector_size, selector_size);

    ofRotate(-angle * 180. / M_PI);
    ofTranslate(-x, -y);
}

bool ofxOui::ShapeEditor::inside(float x_, float y_) {
    ofVec2f point(x_ - x, y_ - y);
    point.rotate(-angle * 180. / M_PI);
    return (point.x >= -width / 2) && (point.x <= width / 2) &&
           (point.y >= -height / 2) && (point.y <= height / 2);
}

ofxOui::ShapeEditor::Selector ofxOui::ShapeEditor::insideSelector(float x_,
                                                                  float y_) {
    ofVec2f point(x_ - x, y_ - y);
    point.rotate(-angle * 180. / M_PI);
    if ((point.x >= -width / 2 - selector_size / 2) &&
        (point.y >= -height / 2 - selector_size / 2) &&
        (point.x <= -width / 2 + selector_size / 2) &&
        (point.y <= -height / 2 + selector_size / 2))
        return Selector::TopLeft;
    if ((point.x >= -selector_size / 2) &&
        (point.y >= -height / 2 - selector_size / 2) &&
        (point.x <= selector_size / 2) &&
        (point.y <= -height / 2 + selector_size / 2))
        return Selector::TopCenter;
    if ((point.x >= width / 2 - selector_size / 2) &&
        (point.y >= -height / 2 - selector_size / 2) &&
        (point.x <= width / 2 + selector_size / 2) &&
        (point.y <= -height / 2 + selector_size / 2))
        return Selector::TopRight;
    if ((point.x >= width / 2 - selector_size / 2) &&
        (point.y >= -selector_size / 2) &&
        (point.x <= width / 2 + selector_size / 2) &&
        (point.y <= selector_size / 2))
        return Selector::MiddleRight;
    if ((point.x >= width / 2 - selector_size / 2) &&
        (point.y >= height / 2 - selector_size / 2) &&
        (point.x <= width / 2 + selector_size / 2) &&
        (point.y <= height / 2 + selector_size / 2))
        return Selector::BottomRight;
    if ((point.x >= -selector_size / 2) &&
        (point.y >= height / 2 - selector_size / 2) &&
        (point.x <= selector_size / 2) &&
        (point.y <= height / 2 + selector_size / 2))
        return Selector::BottomCenter;
    if ((point.x >= -width / 2 - selector_size / 2) &&
        (point.y >= height / 2 - selector_size / 2) &&
        (point.x <= -width / 2 + selector_size / 2) &&
        (point.y <= height / 2 + selector_size / 2))
        return Selector::BottomLeft;
    if ((point.x >= -width / 2 - selector_size / 2) &&
        (point.y >= -selector_size / 2) &&
        (point.x <= -width / 2 + selector_size / 2) &&
        (point.y <= selector_size / 2))
        return Selector::MiddleLeft;
    return Selector::None;
}

void ofxOui::ShapeEditor::mousePressed(ofMouseEventArgs &e) {
    dragging_ = insideSelector(e.x, e.y);
    if (dragging_ == Selector::None && inside(e.x, e.y)) {
        dragging_ = Selector::Shape;
    }
    if (dragging_ != Selector::None) {
        mouse_offset_.x = x - e.x;
        mouse_offset_.y = y - e.y;
        if (dragging_mode_ == MouseDraggingMode::Rotation) {
            reference_angle_ = atan(float(e.y - y) / float(e.x - x));
        }
    }
}

void ofxOui::ShapeEditor::mouseDragged(ofMouseEventArgs &e) {
    if (dragging_ == Selector::None) return;
    EditEvent::Type type((dragging_ == Selector::Shape)
                             ? EditEvent::Type::Translation
                             : EditEvent::Type::Scaling);
    if (dragging_mode_ == MouseDraggingMode::Normal) {
        mouseDraggedNormal(e);
    } else if (dragging_mode_ == MouseDraggingMode::Symmetric) {
        mouseDraggedSymmetric(e);
    } else if (dragging_mode_ == MouseDraggingMode::Rotation) {
        mouseDraggedRotation(e);
        type = EditEvent::Type::Rotation;
    }
    ofxOui::ShapeEditor::EditEvent event =
        ofxOui::ShapeEditor::EditEvent(this, type, x, y, width, height, angle);
    if (shape_editor_event_callback_ != nullptr) {
        shape_editor_event_callback_(event);
    }
}

void ofxOui::ShapeEditor::mouseReleased(ofMouseEventArgs &e) {
    if (dragging_ == Selector::None) return;
    ofxOui::ShapeEditor::EditEvent event = ofxOui::ShapeEditor::EditEvent(
        this, EditEvent::Type::Done, x, y, width, height, angle);
    if (shape_editor_event_callback_ != nullptr) {
        shape_editor_event_callback_(event);
    }
    dragging_ = Selector::None;
}

void ofxOui::ShapeEditor::keyPressed(ofKeyEventArgs &e) {
    if (e.key == OF_KEY_ALT) {
        dragging_mode_ = MouseDraggingMode::Symmetric;
    } else if (e.key == OF_KEY_SHIFT) {
        // dragging_mode_ = Homothetic;
    } else if (e.key == OF_KEY_SUPER) {
        dragging_mode_ = MouseDraggingMode::Rotation;
    }
}

void ofxOui::ShapeEditor::keyReleased(ofKeyEventArgs &e) {
    if (e.key == OF_KEY_ALT && dragging_mode_ != MouseDraggingMode::Rotation) {
        dragging_mode_ = MouseDraggingMode::Normal;
    } else if (e.key == OF_KEY_SHIFT) {
        // dragging_mode_ = HomotheticResize;
    } else if (e.key == OF_KEY_SUPER &&
               dragging_mode_ != MouseDraggingMode::Symmetric) {
        dragging_mode_ = MouseDraggingMode::Normal;
    }
}

void ofxOui::ShapeEditor::mouseDraggedNormal(ofMouseEventArgs &e) {
    if (dragging_ == Selector::Shape) {
        x = e.x + mouse_offset_.x;
        y = e.y + mouse_offset_.y;
    } else {
        ofVec2f point(e.x - x, e.y - y);
        point.rotate(-angle * 180. / M_PI);
        ofVec2f displacement(0, 0);
        if (dragging_ == Selector::TopRight ||
            dragging_ == Selector::MiddleRight ||
            dragging_ == Selector::BottomRight) {
            displacement.x = (point.x - width / 2) / 2;
            width += 2 * displacement.x;
        }
        if (dragging_ == Selector::TopLeft ||
            dragging_ == Selector::MiddleLeft ||
            dragging_ == Selector::BottomLeft) {
            displacement.x = (point.x + width / 2) / 2;
            width += -2 * displacement.x;
        }
        if (dragging_ == Selector::TopLeft ||
            dragging_ == Selector::TopCenter ||
            dragging_ == Selector::TopRight) {
            displacement.y = (point.y + height / 2) / 2;
            height += -2 * displacement.y;
        }
        if (dragging_ == Selector::BottomLeft ||
            dragging_ == Selector::BottomCenter ||
            dragging_ == Selector::BottomRight) {
            displacement.y = (point.y - height / 2) / 2;
            height += 2 * displacement.y;
        }
        displacement.rotate(angle * 180. / M_PI);
        x += displacement.x;
        y += displacement.y;
    }
}

void ofxOui::ShapeEditor::mouseDraggedSymmetric(ofMouseEventArgs &e) {
    if (dragging_ == Selector::Shape) {
        x = e.x + mouse_offset_.x;
        y = e.y + mouse_offset_.y;
    } else {
        ofVec2f point(e.x - x, e.y - y);
        point.rotate(-angle * 180. / M_PI);
        if (dragging_ != Selector::TopCenter &&
            dragging_ != Selector::BottomCenter)
            width = 2 * abs(point.x);
        if (dragging_ != Selector::MiddleLeft &&
            dragging_ != Selector::MiddleRight)
            height = 2 * abs(point.y);
    }
}

void ofxOui::ShapeEditor::mouseDraggedRotation(ofMouseEventArgs &e) {
    float newAngle = atanf(float(e.y - y) / float(e.x - x));
    if ((e.y >= y) && (e.x < x)) newAngle += M_PI;
    if ((e.y < y) && (e.x < x)) newAngle -= M_PI;
    angle += newAngle - reference_angle_;
    reference_angle_ = newAngle;
}

ofxOui::ShapeEditor::EditEvent::EditEvent(ShapeEditor *sender_, Type type_,
                                          float x_, float y_, float width_,
                                          float height_, float angle_)
    : sender(sender_),
      type(type_),
      x(x_),
      y(y_),
      width(width_),
      height(height_),
      angle(angle_) {}
