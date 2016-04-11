/*
 * ofxCuiCuiSlider.hpp
 *
 * Slider (inherits Numbox)
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

#ifndef ofxCuiCuiSlider_hpp
#define ofxCuiCuiSlider_hpp

#include "ofxCuiCuiNumbox.hpp"

namespace ofxCuiCui {

/**
 @ingroup components
 @brief Slider controller
 */
class Slider : public Numbox {
  public:
    /**
     @brief Display Layout
     */
    enum class Layout { Horizontal, Vertical };

    /**
     @brief Origin of the slider filling
     */
    enum class Origin { Lower, Upper, Zero };

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Slider(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~Slider();

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief Display Layout
     */
    Layout layout;

    /**
     @brief Origin of the slider filling
     */
    Origin origin;

  protected:
    virtual void drawLabel();
    virtual void mouseDragged(ofMouseEventArgs &e);
    virtual void mousePressed(ofMouseEventArgs &e);

    ofRectangle slider_rect_;
};
}

#endif
