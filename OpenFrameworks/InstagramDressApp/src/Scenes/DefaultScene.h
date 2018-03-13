/*
 *  DefaultScene.h
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */

#pragma once


#include "ofxScene.h"

class DefaultScene : public ofxScene {

public:

    //! Constructor
    DefaultScene();
    
    //! Set up the scene
    void setup();

    //! Update the scene
    void update();

    //! Draw the scene
    void draw();
    
    //! Called when fading in
    void willFadeIn();

    //! Called when to start drawing
    void willDraw();

    //! Called fading out
    void willFadeOut();

    //! Called when exit
    void willExit();
    
private:
    
    void setupColor();
    
    void updateColor();
    
private:
    
    float   m_hue;
    ofColor m_color;

    
};

