/*
 * ofxOuiGraph.hpp
 *
 * Graph view area
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

#ifndef ofxOuiGraph_hpp
#define ofxOuiGraph_hpp

#include "ofMain.h"
#include "ofxOuiTextBox.hpp"

namespace ofxOui {

/**
 @ingroup core
 @brief 2D Graph Area (with virtual coordinate system)
 */
class Graph {
  public:
    class Ruler {
      public:
        enum class Layout { Horizontal, Vertical };

        Ruler(Layout layout_ = Layout::Horizontal) : layout(layout_) {}
        void update();
        void draw();

        float x;
        float y;
        float width;
        float height;

        float min;
        float max;

        Layout layout;

      protected:
        vector<float> ticks_minor;
        vector<float> ticks_major;
        vector<TextBox> ticks_labels;
    };

    /**
     @brief Bounds of the graph space
     */
    struct Bounds {
        float x_min = 0.;
        float x_max = 1.;
        float y_min = 0.;
        float y_max = 1.;
    };

    /**
     @brief Event arguments for pan/zoom events resulting in bounds changes of
     the graph area
     */
    class BoundsChangedEvent : public ofEventArgs {
      public:
        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         */
        BoundsChangedEvent(Graph* sender_);

        /**
         @brief pointer to the sender component
         */
        Graph* sender;
    };

    /**
     @brief Default Constructor
     */
    Graph();

    /**
     @brief Destructor
     */
    ~Graph();

    void drawRuler();
    void setupViewport();
    void restoreViewport();

    /**
     @brief Set callback function for bounds changed events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onBoundsChanged(T* owner,
                         void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        if (owner)
            bounds_changed_event_callback_ =
                std::bind(listenerMethod, owner, _1);
        else
            bounds_changed_event_callback_ = nullptr;
    }

    /**
     @brief Checks if a point is in the view area
     @param pointAsPixels 2D coordinates (in pixels)
     @return true if the point is in the view area
     */
    bool insideViewArea(ofVec2f const& pointAsPixels) const;

    /**
     @brief Checks if a point is in the graph area
     @param pointAsCoord 2D coordinates (in graph units)
     @return true if the point is in the graph area
     */
    bool insideGraphArea(ofVec2f const& pointAsCoord) const;

    /**
     @brief Convert graph coordinates to pixel coordinates
     @param pointAsCoord 2D coordinates (in graph units)
     @return 2D coordinates (in pixels)
     */
    ofVec2f coord2pix(ofVec2f const& pointAsCoord) const;

    /**
     @brief Convert pixel coordinates to graph coordinates
     @param pointAsPixels 2D coordinates (in pixels)
     @return 2D coordinates (in graph units)
     */
    ofVec2f pix2coord(ofVec2f const& pointAsPixels) const;

    /**
     @brief Scale graph units to pixel units
     @param scaleAsCoord scale in graph units
     @return scale in pixel units
     */
    ofVec2f scale2view(ofVec2f const& scaleAsCoord) const;

    /**
     @brief Scale pixel units to graph units
     @param scaleAsPixels scale in pixel units
     @return scale in graph units
     */
    ofVec2f scale2graph(ofVec2f const& scaleAsPixels) const;

    /**
     @brief View area rectangle (in pixels)
     */
    ofRectangle view;

    /**
     @brief Bounds of the graph space
     */
    Bounds graph_area;

    bool iso_zoom = true;
    std::pair<bool, Ruler> horizontal_ruler = {true, {}};
    std::pair<bool, Ruler> vertical_ruler = {true, {Ruler::Layout::Vertical}};

  protected:
    void mouseScrolled(ofMouseEventArgs& e);
    std::function<void(Graph::BoundsChangedEvent&)>
        bounds_changed_event_callback_;

    bool viewport_valid = false;
};
}

#endif
