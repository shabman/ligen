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

#ifndef _LIGEN2_GEN_INJECT_H_
#define _LIGEN2_GEN_INJECT_H_

#include "disk/path.h"

namespace ligen2
{

class injector final
{
public:
  explicit injector ( const path_buffer&, const std::string&, const int );
  ~injector ();

private:
  injector& operator= ( const injector& ) = delete;
  injector ( const injector& ) = delete;
  injector ( const injector&& ) = delete;

private:
  void insert_file ( const std::string&, const std::vector<std::string>& );
  bool has_header ( const std::string& ) const noexcept;

public:
  void insert_all ();

private:
  path_buffer m_buffer;
  std::vector<std::string> m_license_contents;
  int m_width;
};

}

#endif /* _LIGEN2_GEN_INJECT_H_ */