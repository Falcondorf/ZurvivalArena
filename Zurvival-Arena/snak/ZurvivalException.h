#pragma once
#include <exception>
#include <string>
//Basé sur l'exemple basique sur https://openclassrooms.com/courses/programmez-avec-le-langage-c/la-gestion-des-erreurs-avec-les-exceptions

/*!
*\brief Class qui contient les exception liée au jeu zurvival arena.
*\file ZurvivalException.h
*\author Aynaou Dupont Fakir Bauwens
*/
class ZurvivalException : public std::exception {
private:
	/*!
	*\brief la description du cas lançant l'exception
	*/
	std::string m_phrase;            //Description de l'erreur
public:
	/*!
	*\brief le constructeur de l'exception
	*\param phrase constient la description du cas lançant l'exception
	*/
	ZurvivalException(std::string const& phrase = "") throw()
		: m_phrase(phrase)
	{}

	/*!
	*\brief la description
	*\return pourquoi l'exception est lancée
	*/
	virtual const char* what() const throw()
	{
		return m_phrase.c_str();
	}
	/*!
	*\brief le destructeur de l'exception
	*/
	virtual ~ZurvivalException() throw()
	{}


};