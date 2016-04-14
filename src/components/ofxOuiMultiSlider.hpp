/*
 * ofxOuiMultiSlider.hpp
 *
 * MultiSlider
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

#ifndef ofxOuiMultiSlider_hpp
#define ofxOuiMultiSlider_hpp

#include "ofxOuiComponent.hpp"

namespace ofxOui {

/**
 @ingroup components
 @brief MultiSlider
 */
class MultiSlider : public Component {
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
     @brief Event arguments for slider editing events
     */
    class ValueEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         @param index_ index of the modified slider
         @param value_ value of the modified slider
         */
        ValueEvent(MultiSlider* sender_, int index_, float value_);

        /**
         @brief pointer to the sender component
         */
        MultiSlider* sender;

        /**
         @brief index of the modified slider
         */
        int index;

        /**
         @brief value of the modified slider
         */
        float value;
    };

    /**
     @brief Set callback function for slider editing events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onEditSlider(T* owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        multislider_event_callback_ = std::bind(listenerMethod, owner, _1);
    }

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    MultiSlider(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~MultiSlider();

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief Slider values
     */
    vector<float> values;

    /**
     @brief Minimum value of each slider
     */
    float min = 0.;

    /**
     @brief Maximum value of each slider
     */
    float max = 1.;

    /**
     @brief Display Layout
     */
    Layout layout = Layout::Horizontal;

    /**
     @brief Origin of the slider filling
     */
    Origin origin = Origin::Lower;

  protected:
    virtual void drawLabel();
    void clipValues();
    virtual void mouseDragged(ofMouseEventArgs& e);
    virtual void mousePressed(ofMouseEventArgs& e);

    ofRectangle slider_rect_;
    bool dragging_ = false;
    ofVec2f previous_position_;
    std::function<void(MultiSlider::ValueEvent&)> multislider_event_callback_;
};
}

#endif
