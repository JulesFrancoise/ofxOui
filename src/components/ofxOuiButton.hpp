/*
 * ofxOuiButton.hpp
 *
 * Button component (with toggle mode)
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

#ifndef ofxOuiButton_hpp
#define ofxOuiButton_hpp

#include "../core/ofxOuiComponent.hpp"

namespace ofxOui {

/**
 @ingroup components
 @brief Button component (allows both button and toggle modes)
 */
class Button : public Component {
  public:
    /**
     @brief Event arguments for button clicks
     */
    class ClickEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         @param value_ button value
         */
        ClickEvent(Button* sender_, bool value_);

        /**
         @brief pointer to the sender component
         */
        Button* sender;

        /**
         @brief button value
         */
        bool value;
    };

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Button(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~Button();

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
        if (owner)
            click_event_callback_ = std::bind(listenerMethod, owner, _1);
        else
            click_event_callback_ = nullptr;
    }

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief specifies if the button works as button or toggle
     */
    bool toggle;

  protected:
    virtual void mousePressed(ofMouseEventArgs& e);

    int num_frames_on_;
    std::function<void(Button::ClickEvent&)> click_event_callback_;
};
}

#endif
