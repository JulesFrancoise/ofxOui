/*
 * ofxCuiCuiIcon.hpp
 *
 * Jui Icon Box (Wrapper around ofImage)
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

#ifndef ofxCuiCuiIcon_hpp
#define ofxCuiCuiIcon_hpp

#include "ofxCuiCuiCommon.hpp"

namespace ofxCuiCui {

/**
 @ingroup core
 @brief Icon image box wrapper
 */
class Icon {
  public:
    /**
     @brief Default Constructor
     */
    Icon();

    /**
     @brief Destructor
     */
    virtual ~Icon();

    /**
     @brief OF-like update function: updates the position of the icon
     */
    virtual void update();

    /**
     @brief OF-like draw function: draws the icon
     */
    virtual void draw();

    /**
     @brief load the image file
     @param filename path to the image file
     */
    virtual void load(string filename);

    /**
     @brief x position (of the containing box)
     */
    int x = 0;

    /**
     @brief y position (of the containing box)
     */
    int y = 0;

    /**
     @brief width (of the containing box)
     */
    int width = 100;

    /**
     @brief height (of the containing box)
     */
    int height = 100;

    /**
     @brief padding (within the containing box)
     */
    int padding = 10;

    /**
     @brief Alignment
     */
    Anchor alignment = ofxCuiCui::Anchor::MiddleCenter;

    /**
     @brief Color (in case of a binary icon)
     */
    ofColor color = ofColor::black;

    /**
     @brief Actual rectangle where the icon is drawn
     */
    ofRectangle rect;

  protected:
    ofImage icon_;
};
}

#endif
