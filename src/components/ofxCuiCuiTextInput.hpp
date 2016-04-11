/*
 * ofxCuiCuiTextInput.hpp
 *
 * Text Input Element (single-line text I guess...)
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

#ifndef ofxCuiCuiTextInput_hpp
#define ofxCuiCuiTextInput_hpp

#include "../core/ofxCuiCuiComponent.hpp"

namespace ofxCuiCui {

/**
 @ingroup components
 @brief Text input component (single-line)
 */
class TextInput : public Component {
  public:
    /**
     @brief Event arguments for text editing events
     */
    class TextInputEvent : public ofEventArgs {
      public:
        TextInputEvent(TextInput *sender_, string text_);

        /**
         @brief pointer to the sender component
         */
        TextInput *sender;

        string text;
    };

    /**
     @brief Set callback function for text input events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onTextInput(T *owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        text_input_event_callback_ = std::bind(listenerMethod, owner, _1);
    }

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    TextInput(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~TextInput();

  protected:
    virtual void drawLabel();
    void mouseMoved(ofMouseEventArgs &e);
    void mouseDragged(ofMouseEventArgs &e);
    void mousePressed(ofMouseEventArgs &e);
    void mouseReleased(ofMouseEventArgs &e);
    void keyPressed(ofKeyEventArgs &e);

    bool erase_on_next_input_;
    std::function<void(TextInput::TextInputEvent &)> text_input_event_callback_;
};
}

#endif
