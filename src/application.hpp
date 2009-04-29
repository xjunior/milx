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

#ifndef MILX_APPLICATION_H
#define MILX_APPLICATION_H

#include <vector>
#include <string>
#include <map>
#include <boost/filesystem/path.hpp>
#include "routing.hpp"

namespace Milx
{
    class Response;
    class Request;
    class Controller;
    class Logger;

    /**
     * The Milx::Application class handle the currently running application.
     *
     * This class is responsible by loading the controllers from the current
     * project and handle the application.
     *
     * The application rendering and response are made by the handlers (CGI,
     * FCGI, Apache, etc).
     */
    class Application
    {
        /**
         * Loaded extensions (Shared Libraries)
         */
        // TODO maybe create a new class for loaded SO's, which will also handle the Routes for that SO
	std::vector<void*> _loaded;
        /**
         * The controllers held by the application.
         */
        std::map<std::string, Controller*> _controllers;

        Milx::Logger *_logger;
    public:
        // TODO it should be an array of routes'
        Milx::Routing routes;
        /**
         * Constructor for application. No argument needed (yet).
         */
        Application();
        /**
         * Destructor for application.
         */
        ~Application();
        /**
         * Register the controller on the application.
         * \param the controller Instance
         * \param the controller name
         */
        void controller(Controller*, std::string);
        /**
         * Retrieve a registered controller instance.
         * \param the controller name
         */
        Controller* controller(std::string);
        /**
         * Dispatch a request to the correct controller/action
         * \param req is the request to be dispatched
         * \return a http response
         */
        Milx::Response* dispatch(Milx::Request&);
	/**
	 * Add routes to the application, good thing.
	 */
        void addRoutes(Milx::Routing*);
        void loadFile(const boost::filesystem::path);
        // TODO create loadDirecotory(path, recursive=false)
        Milx::Logger* logger() { return _logger; }
        void logger(Milx::Logger* logger) { if (logger != NULL) _logger = logger; }
    };
}

extern "C" void milx_on_load(Milx::Application&);

#endif
