#include "web_call.hpp"

Milx::WebCall::WebCall(Milx::CallMethod method, std::string path) :
	_method(method),
	_path(path),
	_mime_type("text/html"),
	_status(200),
	_encoding("UTF-8")
{
}

