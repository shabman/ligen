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

#include "disk/file.h"

namespace ligen2
{

file::file ( const std::string& path ) : m_path ( path )
{
}

file::~file ()
{
  if ( m_stream.is_open () )
    {
      m_stream.close ();
    }
}

std::vector<std::string>
file::read ()
{
  if ( m_path.empty () )
    {
      return {};
    }

  m_stream = std::fstream ( m_path );

  if ( !m_stream.is_open () )
    {
      return {};
    }

  std::string line;
  while ( std::getline ( m_stream, line ) )
    {
      m_contents.push_back ( line );
    }

  return m_contents;
}

std::string
file::fext ( const std::string& file ) noexcept
{
  if ( file.empty () )
    {
      return "";
    }

  return file.substr ( file.find_last_of ( "." ) + 1 );
}

bool
file::write ( const std::vector<std::string>& data )
{
  if ( data.empty () )
    {
      return false;
    }

  std::ofstream out ( m_path );

  if ( !out.is_open () )
    {
      return false;
    }

  std::ostream_iterator<std::string> oit ( out );
  std::copy ( std::begin ( data ), std::end ( data ), oit );

  out.close ();
  return true;
}

}