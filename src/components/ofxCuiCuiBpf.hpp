/*
 * ofxCuiCuiBpf.hpp
 *
 * Breakpoint function component
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

#ifndef ofxCuiCuiBpf_hpp
#define ofxCuiCuiBpf_hpp

#include "ofxCuiCuiComponent.hpp"
#include "ofxCuiCuiGraph.hpp"

namespace ofxCuiCui {

/**
 @ingroup components
 @brief Breakpoint function component
 @details Mouse Interaction modes: click + drag. Single clik can be used to edit
 existing values, double click can be used for either adding or removing nodes
 in the BPF
 */
class Bpf : public Component {
  public:
    /**
     @brief Appearance of the BPF display
     */
    enum class Appearance {
        /**
         @brief Display as lines
         */
        Lines,

        /**
         @brief Display as filled surface to the bottom of the display
         */
        FillBottom,

        /**
         @brief Display as filled surface to the top of the display
         */
        FillTop,

        /**
         @brief Display as filled surface to zero
         */
        FillZero
    };

    /**
     @brief Event arguments when a point is edited
     */
    class EditPointEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param x_ x value of the point edited
         @param y_ y value of the point edited
         */
        EditPointEvent(float x_, float y_);

        /**
         @brief x value of the point edited
         */
        float x;

        /**
         @brief y value of the point edited
         */
        float y;
    };

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Bpf(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~Bpf();

    /**
     @brief Set callback function for editing events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onEditPoint(T *owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        callback_ = std::bind(listenerMethod, owner, _1);
    }

    /**
     @brief OF-like update function
     */
    virtual void update();

    /**
     @brief Set the bounds to the min/max of the values
     */
    void clipBounds();

    /**
     @brief Vector of x/y values of the BPF
     */
    vector<ofVec2f> values;

    /**
     @brief 2D Graph area
     */
    Graph graph;

    /**
     @brief Appearance of the BPF display
     */
    Appearance appearance = Appearance::Lines;

    /**
     @brief Radius of the node of the BPF
     */
    float point_radius = 8;

  protected:
    virtual void drawLabel();
    virtual void mousePressed(ofMouseEventArgs &e);
    virtual void mouseDragged(ofMouseEventArgs &e);
    virtual void mouseReleased(ofMouseEventArgs &e);

    int point_selected_;
    float time_mouse_pressed_;
    std::function<void(Bpf::EditPointEvent &)> callback_;
};
}

#endif
