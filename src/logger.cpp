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

#include "logger.hpp"

Milx::Logger::Logger(std::ostream &stream = std::cout) :
    _stream(stream)
{ }

void Milx::Logger::warn(const std::string& txt)
{
    _stream << "[WARNNING] " << txt << std::endl;
}

void Milx::Logger::info(const std::string& txt)
{
    _stream << "[INFO] " << txt << std::endl;
}

void Milx::Logger::error(const std::string& txt)
{
    _stream << "[ERROR] " << txt << std::endl;
}

