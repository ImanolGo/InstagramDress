/*
 *  InstagramManager.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#include "InstagramManager.h"
#include "AppManager.h"


InstagramManager::InstagramManager(): Manager(), m_currentString(""), m_newTag(false), m_firstTag(true), m_currentCode(""), m_currentColorIndex(0), m_currentEffectIndex(0)
{
    //Intentionally left empty
}

InstagramManager::~InstagramManager()
{
   ofLogNotice() << "InstagramManager::destructor";
   ofUnregisterURLNotification(this);
}


//--------------------------------------------------------------

void InstagramManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupTags();
    this->setupTimers();
    
    ofRegisterURLNotification(this);
    
    ofLogNotice() <<"InstagramManager::initialized" ;
}

void InstagramManager::setupTags()
{
    //m_triggerTags.push_back("dorobaer");
    m_triggerTags.push_back("colors");
    m_colorTags = {"red", "green", "blue", "magenta", "yellow", "cyan"};
    m_effectTags = {"rainbow", "pulse", "strobe", "wipe", "chase"};
    m_colors = {ofColor::red, ofColor::green, ofColor::blue, ofColor::magenta, ofColor::yellow, ofColor::cyan};
    
}

void InstagramManager::setupTimers()
{
    auto requestTime = AppManager::getInstance().getSettingsManager().getRequestTime();
    m_urlTimer.setup( requestTime );
    
    m_urlTimer.start( false ) ;
    ofAddListener( m_urlTimer.TIMER_COMPLETE , this, &InstagramManager::urlTimerCompleteHandler ) ;
    
    auto playbackTime = AppManager::getInstance().getSettingsManager().getPlaybackTime();
    m_scenesTimer.setup( playbackTime );
    
    m_scenesTimer.start( false ) ;
    ofAddListener( m_scenesTimer.TIMER_COMPLETE , this, &InstagramManager::scenesTimerCompleteHandler ) ;
}

void InstagramManager::update()
{
    this->updateTimers();
   
    if(m_newTag){
        m_newTag = false;
        this->resetHashTagScene();
    }
}


void InstagramManager::updateTimers()
{
    m_urlTimer.update();
    m_scenesTimer.update();
}

void InstagramManager::resetHashTagScene()
{
    AppManager::getInstance().getGuiManager().onSceneChange("HASHTAG");
    AppManager::getInstance().getSceneManager().changeScene("HASHTAG");
    AppManager::getInstance().getUdpManager().sendColorEffect(m_currentColorIndex, m_currentEffectIndex);
    ofLogNotice() <<"InstagramManager::resetHashTagScenes" ;
    m_scenesTimer.start(false, true);
}



bool InstagramManager::checkUpdate(const string& result, const string& tag)
{
   
    if ( std::find(m_triggerTags.begin(), m_triggerTags.end(), tag) == m_triggerTags.end() )
    {
        return false;
    }
    
    
    string codeString = this->parseJsonCode(result);
    
    
    if(m_currentCode!=codeString){
        m_currentCode=codeString;
        
        string hashtagString = this->parseJsonTag(result);
        ofLogNotice() <<"InstagramManager::parseJson -> " << tag << ": "<< m_currentCode;
        ofLogNotice() <<"InstagramManager::result -> " << hashtagString;
        string resultTag;
        if(this->checkColorTags(hashtagString)){
            m_currentString = hashtagString;
            this->checkEffectTags(hashtagString);
            return true;
        }
        
    }
    
     return false;
    
    // cout << json["tag"]["media"]["nodes"][0]["caption"].asString() <<endl;
}

string InstagramManager::parseJsonTag(const string& result)
{
    m_json.clear();
    m_json.parse(result);
    return m_json["graphql"]["hashtag"]["edge_hashtag_to_media"]["edges"][0]["node"]["edge_media_to_caption"]["edges"][0]["node"]["text"].asString();
}

string InstagramManager::parseJsonCode(const string& result)
{
    m_json.clear();
    m_json.parse(result);
    return m_json["graphql"]["hashtag"]["edge_hashtag_to_media"]["edges"][0]["node"]["shortcode"].asString();
}


void InstagramManager::urlResponse(ofHttpResponse & response)
{
    //ofLogNotice() <<"InstagramManager::urlResponse -> " << response.request.name << ", " << response.status;
    
    if(m_triggerTags.empty()){
        return;
    }

    if(response.status==200 && response.request.name == m_triggerTags.front())
    {
//        ofLogNotice() <<"InstagramManager::urlResponse -> " << response.request.name << ", " << response.status;
        
        m_newTag = this->checkUpdate(response.data, m_triggerTags.front());
    }
}


void InstagramManager::urlTimerCompleteHandler( int &args )
{
    m_urlTimer.start(false);
  //  cout<<"TIMER COMPLETED"<<endl;
    string start = "https://www.instagram.com/explore/tags/" ;
    string end = "/?__a=1" ;
    
    if(m_triggerTags.empty()){
        return;
    }
    
    string url = start + m_triggerTags.front() + end;
    ofLoadURLAsync(url, m_triggerTags.front());
    
    ofLogNotice() <<"InstagramManager::urlTimerCompleteHandler << load : " <<url;
}


void InstagramManager::scenesTimerCompleteHandler( int &args )
{
    //ofLogNotice("InstagramManager::scenesTimerCompleteHandler -> Timer completed");
    AppManager::getInstance().getGuiManager().onSceneChange("DEFAULT");
    AppManager::getInstance().getSceneManager().changeScene("DEFAULT");
    AppManager::getInstance().getUdpManager().sendColorEffect(m_currentColorIndex, 0);
}

bool InstagramManager::checkColorTags(const string& result)
{
    for(int i=0; i< m_colorTags.size(); i++){
        string hastag = '#' + m_colorTags[i];
        if(ofIsStringInString(result, hastag))
        {
            m_currentColorIndex = i;
            ofLogNotice() << "InstagramManager::checkColorTags -> color hashtag found:  " << hastag<< ", index: " << m_currentColorIndex;
            return true;
        }
        
    }

    return false;
}

bool InstagramManager::checkEffectTags(const string& result)
{
    for(int i=0; i< m_effectTags.size(); i++){
        string hastag = '#' + m_effectTags[i];
        if(ofIsStringInString(result, hastag))
        {
            m_currentEffectIndex = i;
            ofLogNotice() << "InstagramManager::checkEffectTags -> effect hashtag found:  " << hastag<< ", index: " << m_currentEffectIndex;
            return true;
        }
        
    }
    
    return false;
}


const ofColor& InstagramManager::getCurrentColor() const
{
    if(m_currentColorIndex>0 && m_currentColorIndex< m_colors.size()){
        return m_colors[m_currentColorIndex];
    }
    
    return m_colors.front();
}


