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

#ifndef MILX_MODULE_H
#define MILX_MODULE_H

#include <string>
#include "controller.hpp"
#include "routing.hpp"

namespace Milx
{
    class Module
    {
        std::string _name;
        Routing _routes;
        /**
         * The controllers held by the application.
         */
        std::map<std::string, Controller*> _controllers;

    public:
        Module(std::string="");
        std::string name();
        void name(std::string);
        Routing& routes();
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
    };
}

#endif
