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

#ifndef MILX_SHARED_MODULE_H
#define MILX_SHARED_MODULE_H

#include <boost/filesystem/path.hpp>
#include "module.hpp"
#include "application.hpp"

namespace Milx
{
    class SharedModule : public Module
    {
        void* _shared;
        Application* _app;
    public:
        SharedModule(Application*, boost::filesystem::path);
        Application* application() const;
        ~SharedModule();
    };
}

#define MILX_MODULE_LOAD "milx_module_load"
extern "C" void milx_module_load(Milx::SharedModule&);

#endif
