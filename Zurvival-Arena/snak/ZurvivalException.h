#pragma once
#include <exception>
#include <string>
//Basé sur l'exemple basique sur https://openclassrooms.com/courses/programmez-avec-le-langage-c/la-gestion-des-erreurs-avec-les-exceptions

class ZurvivalException : public std::exception {
public:
	ZurvivalException(std::string const& phrase = "") throw()
		: m_phrase(phrase)
	{}

	virtual const char* what() const throw()
	{
		return m_phrase.c_str();
	}

	virtual ~ZurvivalException() throw()
	{}

private:
	std::string m_phrase;            //Description de l'erreur
};