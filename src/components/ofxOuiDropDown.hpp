/*
 * ofxOuiDropDown.hpp
 *
 * Dropdown Menu
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

#ifndef ofxOuiDropDown_hpp
#define ofxOuiDropDown_hpp

#include "ofxOuiButton.hpp"

namespace ofxOui {

/**
 @ingroup components
 @brief Drop-down menu
 */
class DropDown : public Component {
  public:
    /**
     @brief Event arguments for menu item selection
     */
    class SelectEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         @param text_ label of the selected menu item
         */
        SelectEvent(DropDown *sender_, string text_);

        /**
         @brief pointer to the sender component
         */
        DropDown *sender;

        /**
         @brief label of the selected menu item
         */
        string text;
    };

    /**
     @brief Set callback function for item selection events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onSelect(T *owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        if (owner)
            select_event_callback_ = std::bind(listenerMethod, owner, _1);
        else
            select_event_callback_ = nullptr;
    }

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    DropDown(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~DropDown();

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief OF-like draw function
     */
    virtual void draw();

    /**
     @brief list of items contained in the menu
     */
    vector<string> items;

  protected:
    void createSubGui();
    void mouseMoved(ofMouseEventArgs &e);
    void mouseDragged(ofMouseEventArgs &e);
    void mousePressed(ofMouseEventArgs &e);
    void mouseReleased(ofMouseEventArgs &e);

    bool mouse_moved_;
    vector<ofxOui::Button *> sub_buttons_;
    std::function<void(DropDown::SelectEvent &)> select_event_callback_;
};
}

#endif
