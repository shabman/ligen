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

#ifndef _LIGEN2_DISK_PATH_H_
#define _LIGEN2_DISK_PATH_H_

#include <iostream>
#include <map>
#include <vector>

#define LIGEN_ADD_IF( dest, src ) \
  if ( !src.empty () )            \
    {                             \
      dest.push_back ( src );     \
    }

namespace ligen2
{

[[nodiscard]] std::vector<std::vector<std::string>> read_all ( const std::string&, const std::string* );

[[nodiscard]] bool is_valid_dir ( const std::string& );

}

#endif /* _LIGEN2_DISK_PATH_H_ */