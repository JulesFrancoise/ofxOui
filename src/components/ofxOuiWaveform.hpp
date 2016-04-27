/*
 * ofxOuiWaveform.hpp
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

#ifndef ofxOuiWaveform_hpp
#define ofxOuiWaveform_hpp

#include "ofxOuiComponent.hpp"
#include "ofxOuiGraph.hpp"

namespace ofxOui {

/**
 @ingroup components
 @brief Breakpoint function component
 @details Mouse Interaction modes: click + drag. Single clik can be used to edit
 existing values, double click can be used for either adding or removing nodes
 in the Waveform
 */
class Waveform : public Component {
  public:
    /**
     @brief Layout of the different channels
     */
    enum class Layout {
        /**
         @brief Appearance of the Waveform display
         */
        Superposed,

        /**
         @brief Appearance of the Waveform display
         */
        Juxtaposed
    };

    /**
     @brief Appearance of the Waveform display
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
     @brief Event arguments when a frame is edited
     */
    class EditEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param x_ x value of the point edited
         @param y_ y value of the point edited
         */
        EditEvent(int frame_index_, vector<float> const &values_);

        /**
         @brief Index of the edited frame
         */
        int frame_index;

        /**
         @brief Edited values
         */
        vector<float> values;
    };

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Waveform(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0);

    /**
     @brief Destructor
     */
    virtual ~Waveform();

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
        if (owner)
            callback_ = std::bind(listenerMethod, owner, _1);
        else
            callback_ = nullptr;
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
     @brief Vector of x/y values of the Waveform
     */
    float *values;

    /**
     @brief Size of the data (number of frames)
     */
    int size;

    /**
     @brief Dimension of the data (number of channels)
     */
    int dimension;

    /**
     @brief Data channels to display and Associated colors
     */
    map<int, ofColor> channels_colors;

    /**
     @brief 2D Graph area
     */
    shared_ptr<Graph> graph;

    /**
     @brief Appearance of the Waveform display
     */
    Appearance appearance = Appearance::Lines;

  protected:
    virtual void drawLabel();
    std::function<void(Waveform::EditEvent &)> callback_;
};
}

#endif
