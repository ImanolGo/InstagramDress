/*
 *  UdpManager.cpp
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */



#include "UdpManager.h"
#include "AppManager.h"


const int UdpManager::UDP_MESSAGE_LENGHT = 100;

const char UdpManager::START_COMMAND = 'd';
const char UdpManager::END_COMMAND = 255;
const char UdpManager::AUTODISCOVERY_COMMAND = '?';

UdpManager::UdpManager(): Manager()
{
    //Intentionally left empty
}

UdpManager::~UdpManager()
{
   ofLogNotice() << "UdpManager::destructor";
}


//--------------------------------------------------------------

void UdpManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupUdpConnection();
    //this->createConnections();
    this->setupText();
    
    ofLogNotice() <<"UdpManager::initialized" ;
}

void UdpManager::setupUdpConnection()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getUdpPortReceive();
    ofLogNotice() <<"UdpManager::setupUdpReceiver -> listening for udp messages on port  " << portReceive;
    
    //m_udpConnection.SetEnableBroadcast(true);
    m_udpConnection.Create(); //create the socket
    m_udpConnection.Bind(portReceive); //and bind to port
    
    
    string ip = AppManager::getInstance().getSettingsManager().getIpAddress();
    int portSend = AppManager::getInstance().getSettingsManager().getUdpPortSend();
   
    m_udpConnection.Connect(ip.c_str(),portSend);
    m_udpConnection.SetNonBlocking(true);
    
    ofLogNotice() <<"UdpManager::setupUdpReceiver -> sending to IP " << ip <<" to port " << portSend;
    
}

void UdpManager::createConnection(string& ip, int send)
{
    m_udpConnection.Connect(ip.c_str(),send);
    m_udpConnection.SetNonBlocking(true);
}

void UdpManager::setupText()
{
    
    int width =  ofGetWidth();
    int fontSize = 12;
    int height = fontSize*2;
    
    ofVec3f position;

    position.y = LayoutManager::MARGIN;
    position.x = 4*LayoutManager::MARGIN + AppManager::getInstance().getGuiManager().getWidth();
    
    string ip = AppManager::getInstance().getSettingsManager().getIpAddress();
    int portSend = AppManager::getInstance().getSettingsManager().getUdpPortSend();

    
    int porReceive = AppManager::getInstance().getSettingsManager().getUdpPortReceive();

    string text = "IP Address: " + ip + ", Tx Port: " + ofToString(portSend) + ", Rx Port: " + ofToString(porReceive);
    
    m_udpText =  ofPtr<TextVisual> (new TextVisual(position, width, height));
    m_udpText->setText(text, "fonts/OpenSansEmoji.ttf", fontSize);
    m_udpText->setColor(ofColor::white);
    m_udpText->setLineHeight(2.5);
    
    
   // AppManager::getInstance().getViewManager().addOverlay(m_udpText);
}


void UdpManager::update()
{
    this->updateReveivePackage();
}

void UdpManager::updateReveivePackage()
{
    char udpMessage[UDP_MESSAGE_LENGHT];
    m_udpConnection.Receive(udpMessage,UDP_MESSAGE_LENGHT);
    string message=udpMessage;
    
    if(message!="")
    {
        //ofLogNotice() <<"UdpManager::updateReveivePackage -> SIZE " << message.size();
        //ofLogNotice() <<"UdpManager::updateReveivePackage -> message " << message;
        if(isMessage(udpMessage, UDP_MESSAGE_LENGHT)){
            this->parseMessage(udpMessage, UDP_MESSAGE_LENGHT);
        }
    }
}

bool UdpManager::isMessage(char * buffer, int size)
{
    if(size<UDP_MESSAGE_LENGHT){
        return false;
    }
    
    if(buffer[0] != START_COMMAND && buffer[2] != END_COMMAND){
        return false;
    }
    
  
    string ip; int port;
    m_udpConnection.GetRemoteAddr(ip, port);
    
    ofLogNotice() <<"UdpManager::isMessage -> Received Message from: " << ip;
    
    return true;
}

void UdpManager::parseMessage(char * buffer, int size)
{
    if(size<UDP_MESSAGE_LENGHT){
        return;
    }
    
    if(buffer[1] == AUTODISCOVERY_COMMAND){
        ofLogNotice() <<"UdpManager::isMessage -> Received Autodiscovery: " << AUTODISCOVERY_COMMAND;
        string ip; int port;
        m_udpConnection.GetRemoteAddr(ip, port);
        this->createConnection(ip, port );
    }
}


void UdpManager::updateReceiveText(const string& message)
{
    int porReceive = AppManager::getInstance().getSettingsManager().getUdpPortReceive();
    //string text = ">> UDP receiving -> Port: " + ofToString(porReceive) ;
    //text += "   " + message;
    //m_udpReceiveTextFont->setText(text);
//
//    m_udpReceiveMessageFont->setText("   " + message);

}

void UdpManager::sendData(const UdpData& data)
{
    string message="";
    
    message+= START_COMMAND;
    
    char id_ = (char) ofClamp(data.m_color, 0, 254);
    message+= id_;
    
    char strip_nr = (char) ofClamp(data.m_effect, 0, 254);
    message+= strip_nr;
    
    message+= END_COMMAND;
  
    m_udpConnection.Send(message.c_str(),message.length());
    
    ofLogNotice() <<"UdpManager::sendData << " << message;
}


void UdpManager::sendColorEffect(int colorIndex, int effectIndex)
{
    UdpData data; data.m_color = colorIndex; data.m_effect = effectIndex;
    this->sendData(data);
}








