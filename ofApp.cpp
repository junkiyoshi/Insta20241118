#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 10) {

		this->noise_value += ofMap(ofGetFrameNum() % 50, 0, 10, 5, 0);
	}

	ofColor color;
	for (int i = 0; i < 500; i++) {

		auto radius = ofRandom(250);
		auto deg = ofRandom(360);

		this->location_list.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
		this->life_list.push_back(0);
		color.setHsb(ofMap(deg, 0, 360, 0, 255), 255, 255);
		this->color_list.push_back(color);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (this->life_list[i] > 50 || (abs(this->location_list[i].x) > 420 || abs(this->location_list[i].y) > 420)) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->location_list[i].x * 0.015, this->location_list[i].y * 0.015, this->noise_value), 0, 1, -360, 360);
		auto next = this->location_list[i] + glm::vec2(5 * cos(deg * DEG_TO_RAD), 5 * sin(deg * DEG_TO_RAD));
		this->location_list[i] = next;
		this->life_list[i] += 1;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		auto alpha = this->life_list[i] > 30 ? ofMap(this->life_list[i], 30, 50, 255, 0) : 255;
		ofSetColor(this->color_list[i], alpha);
		auto size = this->life_list[i] < 20 ? ofMap(this->life_list[i], 0, 20, 0, 4) : 4;
		ofDrawCircle(this->location_list[i], size);
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto alpha = this->life_list[i] > 30 ? ofMap(this->life_list[i], 30, 50, 255, 0) : 255;
		ofSetColor(0, alpha);
		auto size = this->life_list[i] < 20 ? ofMap(this->life_list[i], 0, 20, 0, 4) : 4;
		ofDrawCircle(this->location_list[i], size * 0.4);
	}

	/*
	int start = 60;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}