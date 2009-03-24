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

#ifndef MILX_CGI_REQUEST_H
#define MILX_CGI_REQUEST_H

#include <string>
#include <cstdlib>
#include "../request.h"

namespace Milx
{
    namespace CGI
    {
        /**
         * Milx::CGI::Request is the CGI implementation of a Request
         */
        class Request : public Milx::Request
        {
        public:
            /**
             * \see Milx::Request#accept()
             */
            std::string accept();
            /**
             * \see Milx::Request#acceptCharset()
             */
            std::string acceptCharset();
            /**
             * \see Milx::Request#acceptEncoding()
             */
            std::string acceptEncoding();
            /**
             * \see Milx::Request#acceptLanguage()
             */
            std::string acceptLanguage();
            /**
             * \see Milx::Request#from()
             */
            std::string from();
            /**
             * \see Milx::Request#host()
             */
            std::string host();
            /**
             * \see Milx::Request#pragma()
             */
            std::string pragma();
            /**
             * \see Milx::Request#referer()
             */
            std::string referer();
            /**
             * \see Milx::Request#userAgent()
             */
            std::string userAgent();
            /**
             * \see Milx::Request#queryString()
             */
            std::string queryString();
            /**
             * \see Milx::Request#remoteAddress()
             */
            std::string remoteAddress();
            /**
             * \see Milx::Request#remoteHost()
             */
            std::string remoteHost();
            /**
             * \see Milx::Request#contentType()
             */
            std::string contentType();
        protected:
            /**
             * \see Milx::Request#cookieHeader()
             */
	    std::string cookieHeader();
        private:
            /**
             * Ensure that the variable exists in environment, if doesn't
             * returns "" (nothing, nada, niente)
             */
            std::string _getenv(const char* name)
            {
                char *env = getenv(name);
                return std::string((env == NULL) ? "" : env);
            }
        };
    }
}

#endif
