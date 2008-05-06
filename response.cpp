#include "response.h"

Milx::Response::Response(std::string content, int code, std::string format)
{
    this->code = code;
    this->content = content;
    this->format = format;
}

std::string Milx::Response::getContent()
{
    return content;
}

int Milx::Response::getCode()
{
    return code;
}

std::string Milx::Response::getFormat()
{
    return format;
}

void Milx::Response::setContent(std::string content)
{
    this->content = content;
}

void Milx::Response::setCode(int code)
{
    this->code = code;
}

void Milx::Response::setFormat(std::string format)
{
    this->format = format;
}

std::string Milx::Response::translatedResponseCode()
{
    switch (code)
    {
        // Successful 2xx
        case 200: return "200 OK";
        case 201: return "201 Created";
        case 202: return "202 Accepted";
        case 203: return "203 Non-Authoritative Information";
        case 204: return "204 No Content";
        case 205: return "205 Reset Content";
        case 206: return "206 Partial Content";

        // Redirection 3xx
        case 300: return "300 Multiple Choices";
        case 301: return "301 Moved Permanently";
        case 302: return "302 Found";
        case 303: return "303 See Other";
        case 304: return "304 Not Modified";
        case 305: return "305 Use Proxy";
        case 306: return "306 (Unused)"; // deprecated
        case 307: return "307 Temporary Redirect";

        // Client Error 4xx
        case 400: return "400 Bad Request";
        case 401: return "401 Unauthorized";
        case 402: return "402 Payment Required";
        case 403: return "403 Forbidden";
        case 404: return "404 Not Found";
        case 405: return "405 Method Not Allowed";
        case 406: return "406 Not Acceptable";
        case 407: return "407 Proxy Authentication Required";
        case 408: return "408 Request Timeout";
        case 409: return "409 Conflict";
        case 410: return "410 Gone";
        case 411: return "411 Length Required";
        case 412: return "412 Precondition Failed";
        case 413: return "413 Request Entity Too Large";
        case 414: return "414 Request-URI Too Long";
        case 415: return "415 Unsupported Media Type";
        case 416: return "416 Requested Range Not Satisfiable";
        case 417: return "417 Expectation Failed";

        // Server Error 5xx
        case 500: return "500 Internal Server Error";
        case 501: return "501 Not Implemented";
        case 502: return "502 Bad Gateway";
        case 503: return "503 Service Unavailable";
        case 504: return "504 Gateway Timeout";
        case 505: return "505 HTTP Version Not Supported";
    }

    throw new BadResponseCode();
}
