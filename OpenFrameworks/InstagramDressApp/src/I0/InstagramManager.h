/*
 *  InstagramManager.h
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxSimpleTimer.h"
#include "ofxJSON.h"

//========================== class InstagramManager =======================================
//==============================================================================
/** \class InstagramManager InstagramManager.h
 *	\brief class for managing the Instagram feeds
 *	\details It frequently checks for certain instagram hashtags
 */


class InstagramManager: public Manager
{
public:
    //! Constructor
    InstagramManager();

    //! Destructor
    virtual ~InstagramManager();

    //! setups DMX
    void setup();

    void update();
    
    void urlResponse(ofHttpResponse & response);
    
    void urlTimerCompleteHandler( int &args ) ;
    
    void scenesTimerCompleteHandler( int &args ) ;
    
    const string& getCurrentString() const {return m_currentString;}
    
    const ofColor& getCurrentColor() const;
    
private:
    
    void setupTimers();
    
    void setupTags();
    
    void updateTimers();
    
    bool checkUpdate(const string& result, const string& tag);
    
    string parseJsonTag(const string& result);
    
    string parseJsonCode(const string& result);
    
    bool checkColorTags(const string& result);
    
    bool checkEffectTags(const string& result);
    
    void resetHashTagScene();
    
private:
    
    
    typedef            map<string,string> TagMap; ///< Defines a map of current feeds related to a tag
    typedef            vector<string> TagVector; ///< Defines a map of current feeds related to a tag
    
    typedef            vector<ofColor> ColorsVector; ///< Defines a map of current feeds related to a tag
    
    TagVector          m_triggerTags;
    TagVector          m_colorTags;
    TagVector          m_effectTags;
    ColorsVector       m_colors;
    ofxSimpleTimer     m_urlTimer;
    ofxSimpleTimer     m_scenesTimer;
    ofxJSONElement     m_json;
    string             m_currentString;
    string             m_currentCode;
    int                m_currentColorIndex;
    int                m_currentEffectIndex;
    bool               m_newTag;
    bool               m_firstTag;

};

