/*
 *  GuiManager.h
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#pragma once

#include "Manager.h"
#include "ofxGui.h"
#include "ofxGuiExtended.h"

//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application«s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    static const int GUI_WIDTH;
    
public:
    
    //! Constructor
    GuiManager();
    
    //! Destructor
    ~GuiManager();
    
    //! Set-up the gui
    void setup();
    
    //! Draw the gui
    void draw();
    
    void update();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    int getWidth() {return GUI_WIDTH;}
    
    int getHeight() {return m_gui.getHeight();}
    
    ofPoint  getPosition() {return m_gui.getPosition();}
    
    void onSceneChange(const string& sceneName);
    
    void onSceneChange(int sceneIndex);
    
    void onMatrixSceneChange(bool& value);
    
private:
    
    void setupGuiParameters();
    
    void drawRectangle();
    
    void setupGuiScenes();
    
    void setupGuiColors();
    
    void setupGuiEffects();
    
    void updateScenes();
    
    void updateColors();
    
    void updateEffects();
    
private:
    
    // Fluid GUI
    ofxPanel			m_gui;
    
    ofParameter<float>	m_guiFPS;
    
    ofxGuiMatrix        m_matrixScenes;
    ofxGuiMatrix        m_matrixColors;
    ofxGuiMatrix        m_matrixEffects;
    vector<ofParameter<bool>>   m_scenesParameters;
    vector<ofParameter<bool>>   m_colorParameters;
    vector<ofParameter<bool>>   m_effectsParameters;
    
    int         m_currentScene;
    int         m_currentColor;
    int         m_currentEffect;
    
    
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================

