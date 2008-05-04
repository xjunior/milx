/*
 * This file is part of CPP On Rails.
 *
 * CPP On Rails is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CPP On Rails is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CPP On Rails.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 */

#ifndef CPP_RAILS_CONTROLLER_H
#define CPP_RAILS_CONTROLLER_H

#include <string>

namespace Milx
{
class Application;
class Controller
{
protected:
    Application *application;
public:
    virtual void callAction(std::string)=0;
    void setApplication(Application *a)
    {
        application = a;
    }
};
}

#endif
