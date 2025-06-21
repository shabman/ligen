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

#include "disk/path.h"
#include "disk/file.h"
#include <filesystem>
#include <iostream>

using namespace ligen2;

path_buffer
ligen2::read_all ( const std::string& path, const std::string* exclude )
{
  path_buffer buffer {};

  if ( path.empty () )
    {
      return {};
    }

  if ( !ligen2::is_valid_dir ( path ) )
    {
      return {};
    }

  for ( std::filesystem::recursive_directory_iterator i ( path ), end; i != end; i++ )
    {
      std::filesystem::path path = std::filesystem::canonical ( i->path () );
      if ( !ligen2::is_valid_dir ( path ) )
        {
          file f ( path.string () );

          if ( exclude )
            {
              std::string parent = path.parent_path ().string ().substr ( path.parent_path ().string ().find_last_of ( "/" ) + 1 );
              std::string n_excldue = exclude->substr ( exclude->find_last_of ( "/" ) + 1 );

              if ( n_excldue != parent )
                {
                  std::vector<std::string> contents = f.read ();
                  LIGEN_ADD ( path.string (), buffer, contents )
                }
            }
          else
            {
              std::vector<std::string> contents = f.read ();
              LIGEN_ADD ( path.string (), buffer, contents )
            }
        }
    }

  return buffer;
}

[[nodiscard]] bool
ligen2::is_valid_dir ( const std::string& path )
{
  return std::filesystem::is_directory ( path );
}
