/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

namespace XBMC
{
  class ContextOpaque;

  /**
   * This class sets up a few instances and services. Currently it only
   *  provides a logger to the CThread functionality. If it never does
   *  more than this it can be removed.
   */
  class Context
  {
    ContextOpaque* impl;
  public:
    Context();
    virtual ~Context();
  private:
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
  };
}


