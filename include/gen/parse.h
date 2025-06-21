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

#ifndef _LIGEN2_GEN_PARSE_H_
#define _LIGEN2_GEN_PARSE_H_

#include <map>
#include <vector>

namespace ligen2
{

class parser final
{
public:
  explicit parser ( int argc, char* argv[] );
  ~parser ();

public:
  void parse_all_input () noexcept;
  [[nodiscard]] std::string get_license () const noexcept;
  [[nodiscard]] std::string get_ignore () const noexcept;
  [[nodiscard]] std::string get_allow () const noexcept;
  [[nodiscard]] int get_width () const noexcept;

private:
  std::vector<std::string> m_args;
  std::string m_license;
  std::string m_ignore;
  std::string m_allow;
  int m_width = -1;
};

}

#endif /* _LIGEN2_GEN_PARSE_H_ */
