/*
 * ofxOuiColormap.hpp
 *
 * Sequential color maps (basic...)
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

#ifndef sequentialColorMap_hpp
#define sequentialColorMap_hpp

#include "ofMain.h"

namespace ofxOui {

/**
 @ingroup core
 @brief Sequential Colormap generator
*/
class Colormap {
  public:
    /**
     @brief Default Constructor
     */
    Colormap();

    /**
     @brief Destructor
     */
    virtual ~Colormap();

    /**
     @brief get the name of the current colormap
     @return name of the current colormap
     */
    string getName() const;

    /**
     @brief set the colormap by name
     @param name name of the current colormap
     @return true if the colormap exists
     */
    bool setByName(string name);

    /**
     @brief set a colormap from a vector of base colors
     @param colors vector of Colors to of the sequential colormap
     */
    void setBaseColors(vector<ofColor> colors);

    /**
     @brief resize the colormap
     @return num_values size of the colormap (number of color steps)
     */
    void resize(int num_values);

    /**
     @brief vector of colors of the colormap
     */
    vector<ofColor> values;

    ofColor sample(float position);

  private:
    void generateValues();
    vector<ofColor> base_colors_;
    static map<string, vector<ofColor>> fabric_;
    string current_map_name_;
};
}

#endif
