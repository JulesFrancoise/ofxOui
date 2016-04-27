/*
 * ofxOuiCommon.hpp
 *
 * Jui's Common definition: Component types, anchors and shapes
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

#ifndef ofxOuiCommon_h
#define ofxOuiCommon_h

#include "ofMain.h"

namespace ofxOui {

/**
 @defgroup core Core Classes and Utilities
 @defgroup components UI Components
 */

extern bool RetinaEnabled;

/**
 @ingroup components
 @brief Type of UI Component
 */
enum class Type {
    Label,
    Button,
    CheckBox,
    DraggableButton,
    Matrix,
    DropDown,
    Numbox,
    Slider,
    MultiSlider,
    Bpf,
    TextInput,
    Waveform
};

/**
 @ingroup core
 @brief Generic Anchor specifier for Text/Image alignment
 */
enum class Anchor {
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
 @ingroup core
 @brief Base shape of the UI components
 */
enum class Shape { Circle, Rectangle, RectRounded };

/**
 @ingroup core
 @brief Global configuration
 */
class Globals {
  public:
    /**
     @brief Set retina display on/off
     @param enabled Specifies if high definition should be enabled
     */
    static void setRetina(bool enabled) {
        getInstance().retina_enabled_ = enabled;
        getInstance().reloadFonts();
    }

    /**
     @brief Get the retina setting
     @return true if the screen is high definition
     */
    static bool getRetina() { return getInstance().retina_enabled_; }

    /**
     @brief Set the default font path
     @param path path to the default TTF font
     */
    static void setDefaultFontPath(string path) {
        getInstance().font_path_ = path;
    }

    /**
     @brief Get the default font path
     @return path to the default TTF font
     */
    static string getDefaultFontPath() { return getInstance().font_path_; }

    /**
     @brief Set the default font size
     @param font_size font size
     */
    static void setDefaultFontSize(float font_size) {
        getInstance().font_size_ = font_size;
        getInstance().reloadFonts();
    }

    /**
     @brief Get the default font size
     @return the default font size for all UI components
     */
    static float getDefaultFontSize() { return getInstance().font_size_; }

    /**
     @brief Set the default line height
     @param line_height line height
     */
    static void setDefaultLineHeight(float line_height) {
        getInstance().line_height_ = line_height;
        getInstance().reloadFonts();
    }

    /**
     @brief Get the default line height
     @return the default line height for all UI components
     */
    static float getDefaultLineHeight() { return getInstance().line_height_; }

    /**
     @brief Request a font with a particular setting
     @param client pointer to the client who requested the font
     @param font_path path to the TTF font
     @param font_size font size (pts)
     @param line_height line height (pts)
     @param letter_spacing letter spacing (pts)
     @return a pointer to the font with required settings
     */
    static ofTrueTypeFont* requestFont(void* client, string font_path,
                                       float font_size, float line_height,
                                       float letter_spacing) {
        pair<string, vector<float>> fontSettings(
            font_path, {font_size, line_height, letter_spacing});
        for (auto& f : getInstance().catalog_) {
            if (f.second.second.count(client) > 0) {
                if (f.first == fontSettings) return f.second.first;
                f.second.second.erase(client);
                if (f.second.second.empty()) {
                    delete f.second.first;
                    getInstance().catalog_.erase(f.first);
                }
                break;
            }
        }
        auto it = getInstance().catalog_.find(fontSettings);
        if (it == getInstance().catalog_.end()) {
            ofTrueTypeFont* font = new ofTrueTypeFont();
            font->load(font_path, getRetina() ? font_size * 2. : font_size);
            font->setLineHeight(getRetina() ? line_height * 2. : line_height);
            font->setLetterSpacing(letter_spacing);
            getInstance().catalog_[fontSettings].first = font;
            getInstance().catalog_.at(fontSettings).second.insert(client);
            return font;
        } else {
            getInstance().catalog_.at(fontSettings).second.insert(client);
            return it->second.first;
        }
    }

    /**
     @brief Release a font from a particular client
     @param client pointer to the client who initially requested the font
     */
    static void releaseFont(void* client) {
        for (auto& f : getInstance().catalog_) {
            if (f.second.second.count(client) > 0) {
                f.second.second.erase(client);
                if (f.second.second.empty()) {
                    delete f.second.first;
                    getInstance().catalog_.erase(f.first);
                }
                break;
            }
        }
    }

  private:
    Globals(){};
    Globals(const Globals&) = delete;
    Globals(Globals&&) = delete;
    Globals& operator=(const Globals&) = delete;
    Globals& operator=(Globals&&) = delete;

    static Globals& getInstance() {
        static Globals settings;
        return settings;
    }

    void reloadFonts() {
        for (auto& f : catalog_) {
            f.second.first->load(f.first.first, getRetina()
                                                    ? f.first.second[0] * 2.
                                                    : f.first.second[0]);
            f.second.first->setLineHeight(ofxOui::Globals::getRetina()
                                              ? f.first.second[1] * 2.
                                              : f.first.second[1]);
            f.second.first->setLetterSpacing(f.first.second[2]);
        }
    }

    bool retina_enabled_ = false;
    string font_path_ = "Lato-Regular.ttf";
    float font_size_ = 10.;
    float line_height_ = 12.;

    map<pair<string, vector<float>>, pair<ofTrueTypeFont*, set<void*>>>
        catalog_;
};
}

#endif
