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

#ifndef MILX_MODULE_H
#define MILX_MODULE_H

#include <string>
#include <map>

#include <milx/controller.h>
#include <milx/routing.h>
#include <milx/path.h>
#include <milx/http/call.h>

namespace milx {
  class Application;
  /*class Controller;
  class ControllerPtr;*/
  class Module {
    std::string _name;
    Routing _routes;
    Application& _app;
    /**
     * The controllers held by the application.
     */
    std::map<std::string, milx::ControllerPtr> _controllers;
    milx::Path _views_path;

   public:
    Module(Application&, std::string="");
    std::string name();
    void name(std::string);
    Routing& routes();
    milx::Path views_path();
    void views_path(const milx::Path&);
    Application& application() const { return _app; }

    /**
     * Register the controller on the application.
     * \param the controller Instance
     * \param the controller name
     */
    void controller(ControllerPtr, std::string);
    /**
     * Retrieve a registered controller instance.
     * \param the controller name
     */
    ControllerPtr controller(std::string);
    virtual void dispatch(milx::http::Call&);
    std::string controller_name(Controller* obj);
  };
}

#endif  // MILX_MODULE_H
