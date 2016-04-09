/*
 * ofxCuiCuiMatrix.hpp
 *
 * Button Matrix (supports both button -single-button activation- and toggle
 * -multi-button activation-)
 *
 * This code has been authored by Jules Fran√ßoise <jfrancoi@sfu.ca>
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

#ifndef ofxCuiCuiMatrix_hpp
#define ofxCuiCuiMatrix_hpp

#include "ofxCuiCuiButton.hpp"

namespace ofxCuiCui {

/**
 @ingroup components
 @brief Button Matrix (supports both button -single-button activation- and
 toggle -multi-button activation-)
 */
class Matrix : public Component {
  public:
    /**
     @brief Event arguments for button clicks
     */
    class ClickEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         @param row_ row of the clicked button
         @param col_ column of the clicked button
         @param value_ value of the clicked button
         */
        ClickEvent(Matrix* sender_, int row_, int col_, bool value_);

        /**
         @brief pointer to the sender component
         */
        Matrix* sender;

        int row;
        int col;
        bool value;
    };

    /**
     @brief Set callback function for click events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onClick(T* owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        click_event_callback_ = std::bind(listenerMethod, owner, _1);
    }

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Matrix(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~Matrix();

    /**
     @brief Setup the Matrix layout
     */
    virtual void setup();

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief OF-like draw function
     */
    virtual void draw();

    /**
     @brief number of rows
     */
    int rows;

    /**
     @brief number of columns
     */
    int cols;

    /**
     @brief padding between matrix buttons
     */
    float padding;

    /**
     @brief specifies if the matrix works in toggle with several buttons that
     can be activated at the same time or if a single button can be activated at
     a time
     */
    bool toggle;

    /**
     @brief specifies if the grid between buttons should be drawn
     */
    bool draw_grid;

    /**
     @brief shape of individual buttons
     */
    Shape button_shape;

    /**
     @brief Matrix of button GUIs
     */
    vector<vector<Button>> buttons;

  protected:
    void mouseDragged(ofMouseEventArgs& e);
    void onButtonClick(Button::ClickEvent& e);

    ofRectangle grid_rect_;
    float button_width_;
    float button_height_;
    Button const* selected_button_;
    std::function<void(Matrix::ClickEvent&)> click_event_callback_;
};
}

#endif
