/*
 * ofxCuiCui::ShapeEditor.hpp
 *
 * Shape Editor (Modes : translation, scaling, rotation)
 *
 * This code has been authored by Jules Françoise <jfrancoi@sfu.ca>
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

#ifndef ofxCuiCuiShapeEditor_hpp
#define ofxCuiCuiShapeEditor_hpp

#include "../core/ofxCuiCuiCommon.hpp"

namespace ofxCuiCui {

/**
 @ingroup components
 @brief Shape editor
 */
class ShapeEditor {
  public:
    /**
     @brief Index of the selector of the shape
     */
    enum class Selector {
        None,
        Shape,
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

    /**
     @brief Type of mouse interaction mode
     */
    enum class MouseDraggingMode { Normal, Symmetric, Rotation };

    /**
     @brief Event arguments for shape editing events
     */
    class EditEvent : public ofEventArgs {
      public:
        /**
         @brief type of editing event
         */
        enum class Type { Translation, Scaling, Rotation };

        /**
         @brief Constructor
         @param sender_ pointer to the sender component
         @param type_ type of editing event
         @param x_ x position of the shape editor box
         @param y_ y position of the shape editor box
         @param width_ width of the shape editor box
         @param height_ height of the shape editor box
         @param angle_ angle of the shape editor box
         */
        EditEvent(ShapeEditor *sender_, Type type_, float x_, float y_,
                  float width_, float height_, float angle_);

        /**
         @brief pointer to the sender component
         */
        ShapeEditor *sender;

        /**
         @brief type of editing event
         */
        Type type;

        /**
         @brief x position of the shape editor box
         */
        float x;

        /**
         @brief y position of the shape editor box
         */
        float y;

        /**
         @brief width of the shape editor box
         */
        float width;

        /**
         @brief height of the shape editor box
         */
        float height;

        /**
         @brief angle of the shape editor box
         */
        float angle;
    };

    /**
     @brief Set callback function for shape editing events
     @param owner pointer to the owner object
     @param listenerMethod method to be called on eaech event
     @tparam T type of the owner object
     @tparam args arguments of the callback function
     @tparam ListenerClass class to which the listener method belongs
     */
    template <typename T, typename args, class ListenerClass>
    void onEditShape(T *owner, void (ListenerClass::*listenerMethod)(args)) {
        using namespace std::placeholders;
        shape_editor_event_callback_ = std::bind(listenerMethod, owner, _1);
    }

    /**
     @brief Constructor
     @param x_ x position (left)
     @param y_ y position (top)
     @param width_ component width
     @param height_ component height
     @param angle_ component angle
     */
    ShapeEditor(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0,
                float angle_ = 0);

    /**
     @brief Destructor
     */
    virtual ~ShapeEditor();

    /**
     @brief OF-like draw function
     */
    virtual void draw();

    /**
     @brief checks if a point is inside the shape editor
     @param x_ x position (in pixels)
     @param y_ y position (in pixels)
     @return true if a point is inside the shape editor
     */
    virtual bool inside(int x_, int y_);

    /**
     @brief checks if a point is inside a selector of the shape editor (corner
     or mid-edge)
     @param x_ x position (in pixels)
     @param y_ y position (in pixels)
     @return true if a point is inside a selector the shape editor
     */
    virtual ShapeEditor::Selector insideSelector(int x_, int y_);

    /**
     @brief x position (left)
     */
    float x;

    /**
     @brief y position(top)
     */
    float y;

    /**
     @brief editor width
     */
    float width;

    /**
     @brief editor height
     */
    float height;

    /**
     @brief editor angle
     */
    float angle;

    /**
     @brief width of the editor frame
     */
    int frame_width;

    /**
     @brief color of the editor frame
     */
    ofColor color;

    /**
     @brief size of the corner and edge selectors
     */
    int selector_size;

  protected:
    virtual void mouseDragged(ofMouseEventArgs &e);
    virtual void mousePressed(ofMouseEventArgs &e);
    virtual void mouseReleased(ofMouseEventArgs &e);
    virtual void keyPressed(ofKeyEventArgs &e);
    virtual void keyReleased(ofKeyEventArgs &e);
    virtual void mouseDraggedNormal(ofMouseEventArgs &e);
    virtual void mouseDraggedSymmetric(ofMouseEventArgs &e);
    virtual void mouseDraggedRotation(ofMouseEventArgs &e);

    Selector dragging_;
    MouseDraggingMode dragging_mode_;
    ofPoint mouse_offset_;
    float reference_angle_;
    std::function<void(ofxCuiCui::ShapeEditor::EditEvent &)>
        shape_editor_event_callback_;
};
}

#endif
