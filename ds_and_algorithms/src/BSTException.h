#ifndef BSTEXCEPTION_H
#define BSTEXCEPTION_H
#include <exception>
#include <iostream>
#include <string>

class BSTException : public std::exception
{
public:
	BSTException(const std::string &exception)
		: m_exception{ exception }
	{
	}

	const char* what() const noexcept {
		return m_exception.c_str();
	}
private:
	std::string m_exception{};
};
#endif