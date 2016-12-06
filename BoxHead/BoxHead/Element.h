#pragma once
#include "HitBox.h"
#include <string>

class Element {
private:
	HitBox hb_;
	std::string type_;
	bool isReachable_;
public:
	inline Element(Position x,Position y,std::string type);
	inline std::string getType();
	inline bool getIsReachable();
};

Element::Element(Position x, Position y, std::string type): type_(type) {
	//if (type == "floor") {
	//	isReachable_ = true;
	//}else{
	//	isReachable_ = false;
	//}

	//HitBox hb(x, y);
	//hb_ = hb;
}

std::string Element::getType() {
	return type_;
}

bool Element::getIsReachable() {
	return isReachable_;
}
