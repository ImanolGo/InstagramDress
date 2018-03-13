/*
 *  DefaultScene.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#include "DefaultScene.h"
#include "AppManager.h"

DefaultScene::DefaultScene(): ofxScene("DEFAULT"), m_hue(0)
{
}

void DefaultScene::setup() {
    ofLogNotice("DefaultScene::setup");
    
    this->setupColor();
}

void DefaultScene::setupColor()
{
    m_color.setHueAngle(m_hue);
    m_color.setSaturation(255);
    m_color.setBrightness(255);
}

void DefaultScene::update() {
    float dt = ofGetLastFrameTime();
    m_hue = fmod(m_hue + dt*30,360);
    //ofLogNotice() << "DefaultScene::update -> hue: " << m_hue;
    
    m_color.setHueAngle(m_hue);
}

void DefaultScene::updateColor() {
    this->updateColor();
}


void DefaultScene::draw() {
    ofBackground(m_color);
}

void DefaultScene::willFadeIn() {
    ofLogNotice("DefaultScene::willFadeIn");
    
    AppManager::getInstance().getLayoutManager().setTitle(getName());
}

void DefaultScene::willDraw() {
    ofLogNotice("DefaultScene::willDraw");
}

void DefaultScene::willFadeOut() {
    ofLogNotice("DefaultScene::willFadeOut");
}

void DefaultScene::willExit() {
    ofLogNotice("DefaultScene::willExit");
}


