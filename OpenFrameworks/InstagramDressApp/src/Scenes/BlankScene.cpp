/*
 *  BlankScene.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#include "BlankScene.h"
#include "AppManager.h"

BlankScene::BlankScene(): ofxScene("BLANK"){}

void BlankScene::setup() {
    ofLogNotice("BlankScene::setup");
}

void BlankScene::update() {
    
}

void BlankScene::draw() {
    ofBackground(0,0,0);
    
}

void BlankScene::willFadeIn() {
    ofLogNotice("BlankScene::willFadeIn");
    AppManager::getInstance().getLayoutManager().setTitle(getName());
}

void BlankScene::willDraw() {
    ofLogNotice("BlankScene::willDraw");
}

void BlankScene::willFadeOut() {
    ofLogNotice("BlankScene::willFadeOut");
}

void BlankScene::willExit() {
    ofLogNotice("BlankScene::willExit");
}
