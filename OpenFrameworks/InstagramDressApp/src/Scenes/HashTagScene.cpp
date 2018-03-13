/*
 *  HashTagScene.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#include "HashTagScene.h"
#include "AppManager.h"



HashTagScene::HashTagScene(): ofxScene("HASHTAG"), m_initialized(false)
{
}

void HashTagScene::setup() {
    if(m_initialized){
        return;
    }
    
    ofLogNotice("HashTagScene::setup");
    this->setupText();
    m_initialized = true;
}

void HashTagScene::setupText()
{
    int margin =  LayoutManager::MARGIN;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    ofPoint pos = ofPoint(width/2, height/2);
    float w = width - 2*margin;
    float h = height - 2*margin;
    string text = " ";
    //string fontName = "fonts/Arial Unicode.ttf";
    string fontName = "fonts/OpenSansEmoji.ttf";
    float size = 20;
    
    
    m_textVisual.setWidth(w); m_textVisual.setHeight(h);
    m_textVisual.setPosition(pos); m_textVisual.setCentred(true);
    m_textVisual.setLineHeight(1.5);
    m_textVisual.setText(text, fontName, size, ofColor::white);
    
}

void HashTagScene::update()
{
    this->updateText();
}

void HashTagScene::draw() {
    auto color = AppManager::getInstance().getInstagramManager().getCurrentColor();
    ofBackground(color);
    m_textVisual.draw();
}

void HashTagScene::willFadeIn() {
     ofLogNotice("HashTagScene::willFadeIn");
     this->updateText();
     AppManager::getInstance().getLayoutManager().setTitle(getName());
}

void HashTagScene::updateText()
{
    auto text = AppManager::getInstance().getInstagramManager().getCurrentString();
    m_textVisual.setText(text);
}


void HashTagScene::willDraw() {
    ofLogNotice("HashTagScene::willDraw");
}

void HashTagScene::willFadeOut() {
    ofLogNotice("HashTagScene::willFadeOut");
}

void HashTagScene::willExit() {
    ofLogNotice("HashTagScene::willExit");
   
}




