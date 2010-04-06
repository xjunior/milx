#ifndef MILX_WEB_CALL_H
#define MILX_WEB_CALL_H

#include <string>
#include <map>

namespace Milx
{
	enum CallMethod	{ METHOD_POST, METHOD_GET, METHOD_PUT, METHOD_DELETE };

	class WebCall
	{
	        CallMethod _method;
		std::string _path;
		std::string _content;
		std::string _controller;
		std::string _action;
		std::string _mime_type;
		std::string _encoding;
		int _status;
	    public:
	        WebCall(CallMethod, std::string);

		CallMethod method() { return _method; }
		const std::string& path() { return _path; }
		const std::string& controller() { return _controller; }
		void controller(std::string c) { _controller = c; }
		const std::string& action() { return _action; }
		void action(std::string a) { _action = a; }
		const std::string& response_content() { return _content; }

		std::map<std::string, std::string> params;
		
		// content
		void response_content(const std::string& c) { _content = c; }
		void mime_type(std::string s) { _mime_type = s; }
		std::string mime_type() { return _mime_type; }
		void encoding(std::string s) { _encoding = s; }
		std::string encoding() { return _encoding; }
		void status(int s) { _status = s; }
		int status() { return _status; }
		// void response_content(Milx::View);
	};
}

#endif
