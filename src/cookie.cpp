/*
 * This file is part of Milx.
 *
 * Milx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Milx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Milx.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#include "cookie.h"

Milx::Cookie::Cookie(std::string name, std::string value) :
_name(name), _value(value)
{
	_version = "1";
	_secure = false;
}

std::string Milx::Cookie::name()
{
	return _name;
}

std::string Milx::Cookie::value()
{
	return _value;
}

std::string Milx::Cookie::version()
{
	return _version;
}

std::string Milx::Cookie::domain()
{
	return _domain;
}

std::string Milx::Cookie::expires()
{
	return _expires;
}

std::string Milx::Cookie::path()
{
	return _path;
}

bool Milx::Cookie::isSecure()
{
	return _secure;
}

void Milx::Cookie::name(std::string name)
{
	this->_name = name;
}

void Milx::Cookie::value(std::string value)
{
	this->_value = value;
}

void Milx::Cookie::expires(std::string expires)
{
	this->_expires = expires;
}

void Milx::Cookie::version(std::string version)
{
	this->_version = version;
}

void Milx::Cookie::domain(std::string domain)
{
	this->_domain = domain;
}

void Milx::Cookie::path(std::string path)
{
	this->_path = path;
}

void Milx::Cookie::isSecure(bool secure)
{
	this->_secure = secure;
}

std::string Milx::Cookie::toString()
{
	std::string result = "Set-Cookie: " + _name + " = " + _value; 
	
	if (!_domain.empty())
		result += "; Domain = " + _domain;

	if (!_path.empty())
		result += "; Path = " + _path;
	
	// FIXME
	if (!_expires.empty())
		result += "; Expires = " + _expires;

	result += std::string("; Secure = ").append((_secure) ? "true" : "false");
	
	result += "; Version = " + _version;
	
	return result;
}

