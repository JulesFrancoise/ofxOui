/*
 * ofxCuiCuiCheckBox.hpp
 *
 * Checkbox component (well... a button with an icon)
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

#ifndef ofxCuiCuiCheckBox_hpp
#define ofxCuiCuiCheckBox_hpp

#include "ofxCuiCuiButton.hpp"

namespace ofxCuiCui {

/**
 @ingroup components
 @brief Check box component (specialization of button)
 */
class CheckBox : public Button {
  public:
    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    CheckBox(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~CheckBox();

  protected:
    virtual void drawIcon();
};
}

#endif
