#ifndef MILX_RESPONSE_H
#define MILX_RESPONSE_H

#include <string>

namespace Milx
{
    class Response
    {
        int code;
        std::string content;
        std::string format;

        public:
            Response(std::string, int=200, std::string="text/html");
            std::string getContent();
            void setContent(std::string);
            int getCode();
            void setCode(int);
            std::string getFormat();
            void setFormat(std::string);
            std::string translatedResponseCode();
    };

    class BadResponseCode { };
}

#endif
