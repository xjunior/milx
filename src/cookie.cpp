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

Milx::Cookie::Cookie() {
	version = "1";
	secure = false;
}

std::string Milx::Cookie::getName() {
	return name;
}

std::string Milx::Cookie::getValue() {
	return value;
}

std::string Milx::Cookie::getVersion() {
	return version;
}

std::string Milx::Cookie::getDomain() {
	return domain;
}

std::string Milx::Cookie::getExpires() {
	return expires;
}

std::string Milx::Cookie::getPath() {
	return path;
}

bool Milx::Cookie::isSecure() {
	return secure;
}

void Milx::Cookie::setName(std::string name) {
	this->name = name;
}

void Milx::Cookie::setValue(std::string value) {
	this->value = value;
}

void Milx::Cookie::setExpires(std::string expires) {
	this->expires = expires;
}

void Milx::Cookie::setVersion(std::string version) {
	this->version = version;
}

void Milx::Cookie::setDomain(std::string domain) {
	this->domain = domain;
}

void Milx::Cookie::setPath(std::string path) {
	this->path = path;
}

void Milx::Cookie::setSecure(bool secure) {
	this->secure = secure;
}

std::string Milx::Cookie::toString() {
	std::string result = "Set-Cookie: " + name + " = " + value; 
	
	if(!domain.empty()) {
		result += "; Domain = " + domain;
	}

	if(!path.empty()) {
		result += "; Path = " + path;
	}
	
	// FIXME
	if(!expires.empty()) {
		result += "; Expires = " + expires;
	}

	result += std::string("; Secure = ").append((secure) ? "true" : "false");
	
	result += "; Version = " + version;
	
	return result;
}
