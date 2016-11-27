#pragma once

#include "character.h"
#include <string>
class Heroes : public Character
{

public:
	inline Heroes();
	inline  Heroes(std::string name,unsigned pv,HitBox hb);

	inline std::string getName() const;
	 HitBox hitPerimeter();
private:

	std::string name_;

};

Heroes::Heroes() {
	
}

Heroes::Heroes(std::string name,unsigned pv, HitBox hb):Character(pv,hb),name_(name){

}



std::string Heroes::getName() const {

	return name_;
}