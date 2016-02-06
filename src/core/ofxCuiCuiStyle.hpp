/*
 * ofxCuiCuiStyle.hpp
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

#ifndef ofxCuiCuiStyle_hpp
#define ofxCuiCuiStyle_hpp

#include "ofxCuiCuiCommon.hpp"

namespace ofxCuiCui {

/**
 @ingroup core
 @brief Style structure shared among all components
 */
class Style {
  public:
    /**
     @brief Default Constructor
     */
    Style();

    /**
     @brief Complete Constructor
     @param background_color_off_ background color (active = off)
     @param background_color_off_hover_ background color (active = off + mouse
     hover)
     @param background_color_on_ background color (active = on)
     @param background_color_on_hover_ background color (active = on + mouse
     hover)
     @param frame_color_off_ frame color (active = off)
     @param frame_color_off_hover_ frame color (active = off + mouse hover)
     @param frame_color_on_ frame color (active = on)
     @param frame_color_on_hover_ frame color (active = on + mouse hover)
     @param font_color_off_ font color (active = off)
     @param font_color_off_hover_ font color (active = off + mouse hover)
     @param font_color_on_ font color (active = on)
     @param font_color_on_hover_ font color (active = on + mouse hover)
     @param background_color_disabled_ background color (disabled)
     @param frame_color_disabled_ frame color (disabled)
     @param font_color_disabled_ font color (disabled)
     @param frame_width_ frame width (px)
     @param roundness_ roundness of rectangle corners
     */
    Style(ofColor background_color_off_, ofColor background_color_off_hover_,
          ofColor background_color_on_, ofColor background_color_on_hover_,
          ofColor frame_color_off_, ofColor frame_color_off_hover_,
          ofColor frame_color_on_, ofColor frame_color_on_hover_,
          ofColor font_color_off_, ofColor font_color_off_hover_,
          ofColor font_color_on_, ofColor font_color_on_hover_,
          ofColor background_color_disabled_, ofColor frame_color_disabled_,
          ofColor font_color_disabled_, int frame_width_, int roundness_);

    /**
     @brief Copy Constructor
     */
    Style(Style const& src);

    /**
     @brief Assignment operator
     */
    Style& operator=(Style const& src);

    /**
     @brief Destructor
     */
    virtual ~Style();

    /**
     @brief background color (active = off)
     */
    ofColor background_color_off;

    /**
     @brief background color (active = off + mouse hover)
     */
    ofColor background_color_off_hover;

    /**
     @brief background color (active = on)
     */
    ofColor background_color_on;

    /**
     @brief background color (active = on + mouse hover)
     */
    ofColor background_color_on_hover;

    /**
     @brief frame color (active = off)
     */
    ofColor frame_color_off;

    /**
     @brief frame color (active = off + mouse hover)
     */
    ofColor frame_color_off_hover;

    /**
     @brief frame color (active = on)
     */
    ofColor frame_color_on;

    /**
     @brief frame color (active = on + mouse hover)
     */
    ofColor frame_color_on_hover;

    /**
     @brief font color (active = off)
     */
    ofColor font_color_off;

    /**
     @brief font color (active = off + mouse hover)
     */
    ofColor font_color_off_hover;

    /**
     @brief font color (active = on)
     */
    ofColor font_color_on;

    /**
     @brief font color (active = on + mouse hover)
     */
    ofColor font_color_on_hover;

    /**
     @brief background color (disabled)
     */
    ofColor background_color_disabled;

    /**
     @brief frame color (disabled)
     */
    ofColor frame_color_disabled;

    /**
     @brief font color (disabled)
     */
    ofColor font_color_disabled;

    /**
     @brief frame width (px)
     */
    int frame_width;

    /**
     @brief roundness of rectangle corners
     */
    int roundness;

    static const Style Default, FramedDefault, PlainBlue, FramedBlue,
        PlainGreen, FramedGreen, PlainRed, FramedRed, Label, PlainGray,
        FramedGray, PlainYellow, FramedYellow, PlainDarkblue, FramedDarkblue;
};
}

#endif
