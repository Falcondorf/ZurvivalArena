#pragma once

#include "character.h"
#include <string>
class Heroes : public Character
{

public:
	inline Heroes();
	inline  Heroes(std::string name);

	inline std::string getName() const;
private:

	std::string name_;

};

Heroes::Heroes() {

}



std::string Heroes::getName() const {

	return name_;
}