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


GuiManager::GuiManager(): Manager(), m_showGui(true), m_currentScene(-1)
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
    this->loadGuiValues();
    this->onSceneChange("DEFAULT");
    
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
    
    m_matrixScenes.setup("Presets",1);
    for(unsigned int i = 0; i < m_scenesParameters.size(); i++) {
        //m_scenesParameters.at(i).addListener(this, &GuiManager::onMatrixSceneChange);
        m_matrixScenes.add(new ofxMinimalToggle(m_scenesParameters.at(i)));
    }
    //m_matrixNotes.setBorderColor(ofColor::aquamarine);
    // m_matrixNotes.setElementHeight(26);
    m_matrixScenes.allowMultipleActiveToggles(false);
    
    m_gui.add(&m_matrixScenes);
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

