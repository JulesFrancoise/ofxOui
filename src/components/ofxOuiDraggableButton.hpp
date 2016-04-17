/*
 * ofxOuiDraggableButton.hpp
 *
 * Draggable button
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

#ifndef ofxOuiDraggableButton_hpp
#define ofxOuiDraggableButton_hpp

#include "ofxOuiButton.hpp"

namespace ofxOui {

/**
 @ingroup components
 @brief Draggable Button (specialization of button)
 */
class DraggableButton : public Button {
  public:
    /**
     @brief Event arguments for Drag and Drop events
     */
    class DropEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         @param x_ x drop position
         @param y_ y drop position
         */
        DropEvent(DraggableButton *sender_, int x_, int y_);

        /**
         @brief pointer to the sender component
         */
        DraggableButton *sender;

        /**
         @brief x drop position
         */
        int x;

        /**
         @brief y drop position
         */
        int y;
    };

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    DraggableButton(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~DraggableButton();

    /**
     @brief Set callback function for drag and drop events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onDrop(T *owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        if (owner)
            drop_event_callback_ = std::bind(listenerMethod, owner, _1);
        else
            drop_event_callback_ = nullptr;
    }

    /**
     @brief Sets the reference position of the button
     */
    virtual void setReferencePosition();

  protected:
    virtual void mousePressed(ofMouseEventArgs &e);
    virtual void mouseDragged(ofMouseEventArgs &e);
    virtual void mouseReleased(ofMouseEventArgs &e);

    bool mouse_pressed_inside_;
    bool dragging_;
    ofPoint mouse_offset_;
    ofPoint reference_position_;
    std::function<void(DraggableButton::DropEvent &)> drop_event_callback_;
};
}

#endif
