/*
 * ofxCuiCuiNumbox.hpp
 *
 * Number box (with mouse + keyboard interaction, C74 max style)
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

#ifndef ofxCuiCuiNumbox_hpp
#define ofxCuiCuiNumbox_hpp

#include "../core/ofxCuiCuiComponent.hpp"

namespace ofxCuiCui {

/**
 @ingroup components
 @brief Number box (with mouse + keyboard interaction, C74 max style)
 */
class Numbox : public Component {
  public:
    /**
     @brief Event arguments for value editing events
     */
    class ValueEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         @param value_ value of the number box
         */
        ValueEvent(Numbox *sender_, float value_);

        /**
         @brief pointer to the sender component
         */
        Numbox *sender;

        /**
         @brief value of the number box
         */
        float value;
    };

    /**
     @brief Set callback function for value editing events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onEditValue(T *owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        numbox_event_callback_ = std::bind(listenerMethod, owner, _1);
    }

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Numbox(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~Numbox();

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief value of the number box
     */
    float value;

    /**
     @brief minimum value
     */
    float min;

    /**
     @brief maximum value
     */
    float max;

    /**
     @brief precision of the number display
     */
    int precision;

  protected:
    virtual void drawLabel();
    void clipValue();
    virtual void mouseDragged(ofMouseEventArgs &e);
    virtual void mousePressed(ofMouseEventArgs &e);
    virtual void mouseReleased(ofMouseEventArgs &e);
    virtual void keyPressed(ofKeyEventArgs &e);

    bool dragging_;
    string user_input_;
    int y_pressed_;
    float value_pressed_;
    TextBox value_text_;
    float drag_step_;
    std::function<void(Numbox::ValueEvent &)> numbox_event_callback_;
};
}

#endif
