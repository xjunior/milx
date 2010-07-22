#include <iostream>
#include <iterator>
#include <fstream>
#include <malloc.h>
#include "web_call.hpp"
#include "path.hpp"

Milx::WebCall::WebCall(Milx::CallMethod method, std::string path) :
	_method(method),
	_path(path),
	_content_type("text/html; charset=utf-8"),
	_status(200)
{
	_content.str("");
	_content.flush();
	_content.clear();
}

void Milx::WebCall::content(const Milx::Path& path)
{
	if (path.exists() && path.stat().is_file()) {
		std::ifstream infile(path.str().c_str(), std::ios::in);
		if (infile.is_open()) {
			content_type(path.type());

			_content.str("");
			_content.flush();
			_content.clear();
			std::istreambuf_iterator<char> file_begin(infile.rdbuf());
			const std::istreambuf_iterator<char> file_end;
			while (!file_begin.equal(file_end)) _content << *file_begin++;
			infile.close();
		} else
			; // become error 500 or throw exception
	} else {
		; // become error 500 or throw exception
	}
}

