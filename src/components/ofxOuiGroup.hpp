/*
 * ofxOuiGroup.hpp
 *
 * UI Component Group with grid layout
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

#ifndef ofxOuiGroup_hpp
#define ofxOuiGroup_hpp

#include "ofxOuiComponent.hpp"

namespace ofxOui {

/**
 @ingroup components
 @brief Group of UI components
 */
class Group {
  public:
    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     */
    Group(int x_ = 0, int y_ = 0, int width_ = 100, int height_ = 100);

    /**
     @brief Destructor
     */
    ~Group();

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
     @brief checks if the point (x, y) is inside the UI group
     */
    virtual bool inside(int x_, int y_);

    /**
     @brief get the number of rows in the group
     @return total number of rows (including multi-row spans)
     */
    int rows() const;

    /**
     @brief get the number of columns in the group
     @return total number of columns (including multi-column spans)
     */
    int cols() const;

    /**
     @brief add a component to the group
     @param component shared pointer to the component to add
     @param row index of the row in the group grid
     @param col index of the column in the group grid
     @param rowSpan number of rows the component is spanning in the group grid
     @param colSpan number of columns the component is spanning in the group
     grid
     @return true if the component was successully added to the group
     */
    bool addComponent(shared_ptr<Component> component, int row, int col,
                      int rowSpan = 1, int colSpan = 1);

    /**
     @brief get the pointer to a component by grid position
     @param row index of the row in the group grid
     @param col index of the column in the group grid
     @return shared pointer to the component if it exists (else nullptr)
     */
    shared_ptr<Component> getComponent(int row, int col);

    /**
     @brief get the pointer to a component by label (inactive label)
     @param label label of the component (inactive mode)
     @warning returns the first component with the given label
     */
    shared_ptr<Component> getComponentByLabel(string label);

    /**
     @brief get a vector of pointers to the components of the group
     @return vector of pointers to the components of the group
     */
    vector<shared_ptr<Component>> getComponents();

    /**
     @brief remove a given component from the group by pointer
     @param component shared pointer to the component
     @return true if the component was successfully removed from the group
     */
    bool removeComponent(shared_ptr<Component> component);

    /**
     @brief remove a given component from the group by position
     @param row index of the row in the group grid
     @param col index of the column in the group grid
     @return true if the component was successfully removed from the group
     */
    bool removeComponent(int row, int col);

    /**
     @brief clear the UI group (deletes all components)
     */
    void clear();

    /**
     @brief disable all components
     */
    void disable();

    /**
     @brief disable all components
     */
    void enable();

    /**
     @brief x position (left)
     */
    float x;

    /**
     @brief y position(top)
     */
    float y;

    /**
     @brief group width
     */
    float width;

    /**
     @brief group height
     */
    float height;

    /**
     @brief maximum width of each component
     */
    int max_component_width;

    /**
     @brief maximum height of each component
     */
    int max_component_height;

    /**
     @brief padding between the components
     */
    int padding;

    /**
     @brief background color of the group
     */
    ofColor backgroundColor;

    /**
     @brief frame color of the group
     */
    ofColor frameColor;

    /**
     @brief width of the group frame
     */
    int frame_width;

    /**
     @brief width of the group frame
     */
    ofxOui::Anchor alignment = ofxOui::Anchor::TopLeft;

  protected:
    map<vector<int>, shared_ptr<Component>> components;
};
}

#endif
