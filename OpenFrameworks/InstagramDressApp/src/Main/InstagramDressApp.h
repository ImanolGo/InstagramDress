/*
 *  InstagramDressApp.h
 *  Instagram Dress
 *
 *  Created by Imanol Gomez on 13/03/18.
 *
 */


#pragma once

#include "ofMain.h"

class InstagramDressApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

};

