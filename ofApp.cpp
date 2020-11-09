#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", 28);
	font_settings.antialiased = true;	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		u8"ž", u8"‹É", u8"½", u8"ãÄ", u8"ƒ",
		u8"ãJ", u8"Šó", u8"g", u8"‹", u8"‰ä",
		u8"‰Ô", u8"’¹", u8"“û", u8"•—", u8"ŒŽ",
	};
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(0, -14, 0);

	int radius = 300;
	for (int deg = 0; deg < 360; deg += 8) {

		for (int y = -300; y <= 300; y += 35) {

			auto location = glm::vec3(0, y, -radius);
			auto rotation_y = glm::rotate(glm::mat4(), (float)(deg * DEG_TO_RAD), glm::vec3(0, 1, 0));
			location = glm::vec4(location, 0) * rotation_y;

			ofPushMatrix();
			ofTranslate(location);
			ofRotateY(180 - deg);

			if (location.z > 150) {

				ofSetColor(ofColor(0));
			}
			else {

				ofSetColor(ofColor(0, ofMap(location.z, -300, 150, 32, 255)));
			}

			int noise_value = ofMap(ofNoise(location.x * 0.003, location.y * 0.0003 + ofGetFrameNum() * 0.005, location.z * 0.003), 0, 1, 0, this->words.size());
			string str = this->words[noise_value];
			this->font.drawString(str, 0, 0);

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}