/*
 * ofxCuiCuiComponent.hpp
 *
 * UI Component Base Class
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

#ifndef ofxCuiCuiComponent_hpp
#define ofxCuiCuiComponent_hpp

#include "ofxCuiCuiIcon.hpp"
#include "ofxCuiCuiStyle.hpp"
#include "ofxCuiCuiTextBox.hpp"

namespace ofxCuiCui {

/**
 @ingroup core
 @brief Base UI Component (equivalent to a label)
 */
class Component {
  public:
    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Component(float x_ = 0, float y_ = 0, float width_ = 0, float height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~Component();

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief OF-like draw function
     @details this method is subdivided in protected sub-methods that can be
     overloaded in inherited components
     */
    virtual void draw();

    /**
     @brief checks if a point is inside the component (depending on the shape)
     @return true if the point of coordinates (x, y) is inside the component
     */
    virtual bool inside(float x_, float y_) const;

    /**
     @brief get the type of the component
     @return type of the component
     */
    inline Type type() const { return type_; }

    /**
     @brief shape of the component
     */
    Shape shape = ofxCuiCui::Shape::Rectangle;

    /**
     @brief style of the component
     */
    Style style = ofxCuiCui::Style::Default;

    /**
     @brief textbox for the main label of the component
     */
    TextBox font;

    /**
     @brief icon box of the component
     */
    Icon icon;

    /**
     @brief x position (left)
     */
    float x;

    /**
     @brief y position(top)
     */
    float y;

    /**
     @brief component width
     */
    float width;

    /**
     @brief component height
     */
    float height;

    /**
     @brief Label of the component (active)
     */
    string labelOn = "";

    /**
     @brief Label of the component (not active)
     */
    string labelOff = "";

    /**
     @brief specifies if the component should be in "disabled" mode (no
     interaction)
     */
    bool disabled = false;

    /**
     @brief specifies if the component is active
     */
    bool active = false;

  protected:
    virtual void drawBackground();
    virtual void drawFrame();
    virtual void drawLabel();
    virtual void drawIcon();
    Type type_ = ofxCuiCui::Type::Label;
    bool hover_ = false;
    ofColor current_background_color_;
    ofColor current_frame_color_;

    static Component* blocking_component;
};

/**
 @brief Label UI Component
 */
typedef Component Label;
}

#endif
