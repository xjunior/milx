/*
 * Copyright 2010 Carlos Junior
 *
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

#include "module.h"
#include "logger.h"
#include "http/call.h"

namespace milx {
  class Path;
  /**
   * The Milx::Application class handle the currently running application.
   *
   * This class is responsible by loading the controllers from the current
   * project and handle the application.
   *
   * The application rendering and response are made by the handlers (CGI,
   * FCGI, Apache, etc).
   */
  class Application {
    /**
     * Enabled Modules
     */
    std::vector<ModulePtr> _modules;
    /**
     * The common application Logger
     */
    milx::Logger *_logger;
   public:
    /**
     * Constructor for application. No argument needed (yet).
     */
    Application();
    /**
     * Destructor for application.
     */
    ~Application();
    /**
     * Dispatch a request to the correct controller/action
     * \param req is the request to be dispatched
     * \return a http response
     */
    void dispatch(milx::http::Call&);

    void load_module(const milx::Path&);
    void add_module(milx::ModulePtr);
    /**
     * Get the application logger
     * \return the default logger
     */
    const milx::Logger& logger() { return *_logger; }
    void logger(milx::Logger* l) { _logger = l; }
  };
}

#endif  // MILX_APPLICATION_H
