/*
 *  GuiManager.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "GUI";
const int GuiManager::GUI_WIDTH = 350;


GuiManager::GuiManager(): Manager(), m_showGui(true), m_currentScene(-1), m_currentColor(-1), m_currentEffect(-1)
{
    //Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    
    this->setupGuiParameters();
    this->setupGuiScenes();
    this->setupGuiColors();
    this->setupGuiEffects();
  //  this->loadGuiValues();
    //this->onSceneChange("DEFAULT");
    
    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{
    m_gui.setDefaultWidth(GUI_WIDTH);
    m_gui.setup(GUI_SETTINGS_NAME, GUI_SETTINGS_FILE_NAME);
    //m_gui.setPosition(ofGetWidth() - GUI_WIDTH - 20, 40);
    m_gui.setPosition(20, 20);
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
    //ofxGuiSetFont( "fonts/open-sans/OpenSans-Semibold.ttf", 9 );
    
}
void GuiManager::setupGuiScenes()
{
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    vector<string> scenes;
    
    for(int i = 0; i < sceneManager->getNumberScenes(); i++)
    {
        scenes.push_back(sceneManager->getSceneName(i));
    }
    
    for(auto scene: scenes)
    {
        m_scenesParameters.push_back(ofParameter<bool>(scene,false));
    }
    
    m_matrixScenes.setup("Scenes",1);
    for(unsigned int i = 0; i < m_scenesParameters.size(); i++) {
        //m_scenesParameters.at(i).addListener(this, &GuiManager::onMatrixSceneChange);
        m_matrixScenes.add(new ofxMinimalToggle(m_scenesParameters.at(i)));
    }
    //m_matrixNotes.setBorderColor(ofColor::aquamarine);
    // m_matrixNotes.setElementHeight(26);
    m_matrixScenes.allowMultipleActiveToggles(false);
    
    m_gui.add(&m_matrixScenes);
}


void GuiManager::setupGuiColors()
{
    auto colorNames = AppManager::getInstance().getInstagramManager().getColorNames();
    
    for(auto color: colorNames)
    {
        m_colorParameters.push_back(ofParameter<bool>(color,false));
    }
    
    m_matrixColors.setup("Colors",1);
    for(unsigned int i = 0; i < m_colorParameters.size(); i++) {
        m_matrixColors.add(new ofxMinimalToggle(m_colorParameters.at(i)));
    }

    m_matrixColors.allowMultipleActiveToggles(false);
    
    m_gui.add(&m_matrixColors);
}

void GuiManager::setupGuiEffects()
{
    auto effectNames = AppManager::getInstance().getInstagramManager().getEffectNames();
    
    for(auto effect: effectNames)
    {
        m_effectsParameters.push_back(ofParameter<bool>(effect,false));
    }
    
    m_matrixEffects.setup("Effects",1);
    for(unsigned int i = 0; i < m_effectsParameters.size(); i++) {
        m_matrixEffects.add(new ofxMinimalToggle(m_effectsParameters.at(i)));
    }
 
    m_matrixEffects.allowMultipleActiveToggles(false);
    
    m_gui.add(&m_matrixEffects);
}


void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    
    m_guiFPS = ofGetFrameRate();
    m_gui.draw();
    
}

void GuiManager::update()
{
    this->updateScenes();
    this->updateColors();
    this->updateEffects();
}

void GuiManager::updateScenes()
{
    if(m_currentScene != m_matrixScenes.getActiveToggleIndex()){
    
        m_currentScene = m_matrixScenes.getActiveToggleIndex();
        //ofLogNotice() <<"GuiManager::updateScenes -> Current Scene: " << m_currentScene;
        AppManager::getInstance().getSceneManager().changeScene(m_currentScene);
        m_matrixScenes.setActiveToggle(m_currentScene);
        
    }
}


void GuiManager::updateColors()
{
    if(m_currentColor != m_matrixColors.getActiveToggleIndex()){
        
        m_currentColor = m_matrixColors.getActiveToggleIndex();
        AppManager::getInstance().getInstagramManager().setCurrentColor(m_currentColor);
        AppManager::getInstance().getInstagramManager().resetHashTagScene();
        ofLogNotice() <<"GuiManager::updateColors -> Current Color: " << m_currentColor;
        //AppManager::getInstance().getSceneManager().changeScene(m_currentColor);
        m_matrixColors.setActiveToggle(m_currentColor);
        
    }
}

void GuiManager::updateEffects()
{
    if(m_currentEffect != m_matrixEffects.getActiveToggleIndex()){
        
        m_currentEffect = m_matrixEffects.getActiveToggleIndex();
        AppManager::getInstance().getInstagramManager().setCurrentEffect(m_currentEffect);
        
        AppManager::getInstance().getInstagramManager().resetHashTagScene();
        ofLogNotice() <<"GuiManager::updateEffects -> Current Effect: " << m_currentEffect;
        //AppManager::getInstance().getSceneManager().changeScene(m_currentColor);
        m_matrixEffects.setActiveToggle(m_currentEffect);
        
    }
}



void GuiManager::saveGuiValues()
{
    m_gui.saveToFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}


void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofRect( m_gui.getPosition().x - 20, 0, GUI_WIDTH + 60, ofGetHeight());
    ofPopStyle();
}


void GuiManager::onSceneChange(const string &sceneName)
{
    int index = AppManager::getInstance().getSceneManager().getIndex(sceneName);
    this->onSceneChange(index);
}

void GuiManager::onSceneChange(int sceneIndex)
{
    
    if(sceneIndex>=0&&sceneIndex<m_scenesParameters.size())
    {
         m_matrixScenes.setActiveToggle(sceneIndex);
    }
   
}


void GuiManager::onMatrixSceneChange(bool& value)
{
    for(unsigned int i = 0; i < m_scenesParameters.size(); i++) {
        if( value && (m_scenesParameters.at(i).get() == true))
        {
            int index = m_matrixScenes.getActiveToggleIndex();
            //ofLogNotice() <<"GuiManager::m_scenesParameters -> Scene: " << i << ", index = " << index;
            //AppManager::getInstance().getSceneManager().changeScene(i);
        }
    }
}


void GuiManager::setColor(int value) {
    
    m_matrixColors.setActiveToggle(value);
    //m_currentColor = value;
    ofLogNotice() <<"GuiManager::setColor -> color: " << value;
    
}

void GuiManager::setEffect(int value) {
    //m_currentEffect = value;
    m_matrixEffects.setActiveToggle(value);
    ofLogNotice() <<"GuiManager::setEffect -> effect: " << value;
}
