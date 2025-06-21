/*
 * This file is part of the ligen2 distribution (https://github.com/shabman/ligen)
 * Copyright (c) 2025 Mustafa Malik.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ligen2.h"
#include "disk/file.h"
#include "disk/path.h"
#include "gen/parse.h"

using namespace ligen2;

ligen_result_t
ligen2::execute ( int argc, char* argv[] )
{
  ligen_result_t result = {};
  result.succeeded = false;

  parser p ( argc, argv );
  p.parse_all_input ();

  std::string license = p.get_license ();
  std::string ignore = p.get_ignore ();
  std::string allow = p.get_allow ();
  int width = p.get_width ();

  if ( license.empty () )
    {
      result.cause = "license cannot be empty";
      return result;
    }

  if ( allow.empty () )
    {
      result.cause = "allow directory must be specified";
      return result;
    }

  if ( !is_valid_dir ( allow ) )
    {
      result.cause = "allow must be a directory";
      return result;
    }

  if ( !ignore.empty () )
    {
      if ( !is_valid_dir ( ignore ) )
        {
          result.cause = "ignore must be a directory";
          return result;
        }
    }

  std::vector<std::string> files = read_all ( allow );

  result.succeeded = true;
  return result;
}
