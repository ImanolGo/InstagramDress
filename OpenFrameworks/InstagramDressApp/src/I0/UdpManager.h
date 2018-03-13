/*
 *  UdpManager.h
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxNetwork.h"
#include "TextVisual.h"




//=========================== UdpData =======================================
//===========================================================================


typedef struct UdpData
{
    UdpData()
    : m_color(0), m_effect(0)
    {
        // Do nothing
    }
    int m_color;
    int m_effect;

} UdpData;



//========================== class UdpManager =======================================
//==============================================================================
/** \class UdpManager UdpManager.h
 *	\brief class for managing the UDP messages
 *	\details It reads all the UDP messages and create the proper application events
 */


class UdpManager: public Manager
{

    static const int UDP_MESSAGE_LENGHT; ///Defines the Udp"s message length
    static const char START_COMMAND; ///Defines the start command byte
    static const char END_COMMAND; ///Defines the end command byte
    static const char AUTODISCOVERY_COMMAND; ///Defines the autodiscovery command byte
   

public:
    //! Constructor
    UdpManager();

    //! Destructor
    virtual ~UdpManager();

    //! setups the manager
    void setup();

    //! updates the manager
    void update();
    
    void sendData(const UdpData& data);
    
    void sendColorEffect(int colorIndex, int effectIndex);

private:
    
    //! sets up the udp
    void setupUdpConnection();
        
    //! setups the text visuals
    void setupText();
    
    //! updates receiving information text visuals
    void updateReceiveText(const string& message);
    
    void updateReveivePackage();
    
    bool isMessage(char * buffer, int size);
    
    void parseMessage(char * buffer, int size);
    
    void receivedIp(char _id);
    
    void receivedHeartbeat(char _id, char val1, char val2);
    
    void createConnection(string& ip, int port);

    
 private:
    

    ofxUDPManager          m_udpConnection;        ///< ofxUdpManager  class
    ofPtr<TextVisual>      m_udpText;
    
};

