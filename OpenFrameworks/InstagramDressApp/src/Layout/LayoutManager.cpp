/*
 *  LayoutManager.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"
#include "ViewManager.h"


#include "LayoutManager.h"


const int LayoutManager::MARGIN = 20;
const int LayoutManager::FRAME_MARGIN = 2;
const string LayoutManager::LAYOUT_FONT =  "fonts/OpenSansEmoji.ttf";
const string LayoutManager::LAYOUT_FONT_LIGHT =  "fonts/open-sans/OpenSans-Light.ttf";

LayoutManager::LayoutManager(): Manager()
{
	//Intentionally left empty
}


LayoutManager::~LayoutManager()
{
    ofLogNotice() <<"LayoutManager::Destructor";
}


void LayoutManager::setup()
{
	if(m_initialized)
		return;

	Manager::setup();
    
    this->setupFbo();
    this->setupWindowFrame();
    
    this->createTextVisuals();
    this->createSvgVisuals();
    this->createImageVisuals();
    //this->addVisuals();
    
    ofLogNotice() <<"LayoutManager::initialized";

}


void LayoutManager::setupFbo()
{
    int margin = MARGIN;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    
    m_fbo.allocate(width, height, GL_RGBA);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
}

void LayoutManager::resetWindowRect()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    float ratio = width/ height;
    float frame_width = ofGetWidth() - AppManager::getInstance().getGuiManager().getWidth() - 2*MARGIN;
    
    m_windowRect.width = frame_width- 4*MARGIN;
    m_windowRect.height =  m_windowRect.width / ratio;
    
    m_windowRect.x = AppManager::getInstance().getGuiManager().getWidth()  + 4*MARGIN;
    m_windowRect.y = ofGetHeight()*0.5 - m_windowRect.height/2;
}
void LayoutManager::setupWindowFrame()
{
    this->resetWindowRect();
    this->resetWindowFrame();
    
    float width = ofGetScreenWidth();
    float height = ofGetScreenHeight()/80;
    
    
    ofColor color = AppManager::getInstance().getSettingsManager().getColor("FrameRectangle");
    m_windowFrame.setColor(color);
    
}

void LayoutManager::resetWindowFrame()
{
    m_windowFrame.setPosition(ofPoint( m_windowRect.x - FRAME_MARGIN, m_windowRect.y - FRAME_MARGIN, 0));
    m_windowFrame.setWidth(m_windowRect.width + 2*FRAME_MARGIN); m_windowFrame.setHeight(m_windowRect.height + 2*FRAME_MARGIN);

}

void LayoutManager::update()
{
    if(!m_initialized)
        return;
}

void LayoutManager::createTextVisuals()
{
    float size = 20;
    float w = m_windowRect.width;
    float h = size;
    float x =  m_windowRect.x + m_windowRect.getWidth()*0.5;
    float y =  m_windowRect.y - h - 2*MARGIN;
    ofPoint pos = ofPoint(x, y);
    string text = "Current Scene";
    string fontName = LAYOUT_FONT;
    

    auto textVisual = ofPtr<TextVisual>(new TextVisual(pos,w,h,true));
    textVisual->setText(text, fontName, size, ofColor::white);
    m_textVisuals["SceneName"] = textVisual;
    
}


void LayoutManager::resetWindowTitle()
{
    float x =  m_windowRect.x + m_windowRect.getWidth()*0.5;
    float y =  m_windowRect.y -  m_textVisuals["SceneName"]->getHeight()*0.5 - MARGIN;
    ofPoint pos = ofPoint(x, y);
    m_textVisuals["SceneName"]->setPosition(pos);
}



void LayoutManager::createSvgVisuals()
{
    ///To implement in case we have text visuals
}


void LayoutManager::createImageVisuals()
{
    //this->createBackground();
}

void LayoutManager::createBackground()
{
}

void LayoutManager::addVisuals()
{
    int depthLevel = -1;
    for(SvgMap::iterator it = m_svgVisuals.begin(); it!= m_svgVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
    
    for(TextMap::iterator it = m_textVisuals.begin(); it!= m_textVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
    
    for(ImageMap::iterator it = m_imageVisuals.begin(); it!= m_imageVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
}


void LayoutManager::onFullScreenChange(bool value)
{
    if(value){
        ofSetWindowShape(ofGetScreenWidth(),ofGetScreenHeight());
    }
    else{

        float width = 4*MARGIN + 2*AppManager::getInstance().getGuiManager().getWidth();
        float height = AppManager::getInstance().getGuiManager().getHeight() + 2*MARGIN;
        ofSetWindowShape(width,height);
    }
}

void LayoutManager::draw()
{
    if(!m_initialized)
        return;
    
    this->drawFbo();
    this->drawText();
    //this->drawRectangles();
}


void LayoutManager::drawText()
{
    for(auto textVisual: m_textVisuals){
        textVisual.second->draw();
    }
}


void LayoutManager::drawFbo()
{
    
    ofEnableAlphaBlending();
    m_fbo.begin();
    ofClear(0, 0, 0);
        AppManager::getInstance().getSceneManager().draw();
    
    m_fbo.end();
    ofDisableAlphaBlending();
    
    m_windowFrame.draw();
    m_fbo.draw(m_windowRect.x,m_windowRect.y,m_windowRect.width,m_windowRect.height);
}

void LayoutManager::setTitle(const string& title)
{
    string titleKey = "SceneName";
    if( m_textVisuals.find(titleKey) == m_textVisuals.end()){
        return;
    }
    
    m_textVisuals[titleKey]->setText(title);
}

void LayoutManager::windowResized(int w, int h)
{
    if(!m_initialized){
        return;
    }
    
    this->resetWindowRect();
    this->resetWindowFrame();
    this->resetWindowTitle();
}



