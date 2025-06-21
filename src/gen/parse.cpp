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

#include "gen/parse.h"
#include <charconv>
#include <iostream>

static bool
is_number ( const std::string& s )
{
  return !s.empty () && std::find_if ( s.begin (), s.end (), [] ( unsigned char c ) { return !std::isdigit ( c ); } ) == s.end ();
}

namespace ligen2
{

parser::parser ( int argc, char* argv[] )
{
  m_args = std::vector<std::string> ( argv + 1, argv + argc );
}

parser::~parser () = default;

void
parser::parse_all_input () noexcept
{
  if ( m_args.empty () )
    {
      return;
    }

  size_t len = m_args.size ();
  for ( size_t i = 0; i < len; i++ )
    {
      if ( m_args[ i ].rfind ( "--", 0 ) == 0 )
        {
          std::string cmd = m_args[ i ].erase ( 0, 2 );
          if ( ( i + 1 ) < len )
            {
              std::string arg = m_args[ i + 1 ];
              if ( cmd == "license" )
                {
                  m_license = arg;
                }
              else if ( cmd == "ignore" )
                {
                  m_ignore = arg;
                }
              else if ( cmd == "allow" )
                {
                  m_allow = arg;
                }
              else if ( cmd == "width" )
                {
                  if ( is_number ( arg ) )
                    {
                      m_width = std::stoi ( arg );
                    }
                  else
                    {
                      std::cout << "[LIGEN WARNING]: invalid operand provided, defaulting to 1 width space\n";
                    }
                }
            }
        }
    }

  if ( m_width < 0 || m_width == -1 || m_width > 4 )
    {
      std::cout << "[LIGEN WARNING]: invalid width argument provided, defaulting to 1 width space\n";
      m_width = 1;
    }

  //   std::cout << "license: " << m_license << "\n";
  //   std::cout << "ignore: " << m_ignore << "\n";
  //   std::cout << "allow: " << m_allow << "\n";
  //   std::cout << "width: " << m_width << "\n";
}

std::string
parser::get_license () const noexcept
{
  return m_license;
}

std::string
parser::get_ignore () const noexcept
{
  return m_ignore;
}

std::string
parser::get_allow () const noexcept
{
  return m_allow;
}

int
parser::get_width () const noexcept
{
  return m_width;
}

}