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

#include "gen/inject.h"
#include "disk/file.h"
#include "termcolor.h"
#include <filesystem>

namespace ligen2
{

injector::injector ( const path_buffer& files, const std::string& license_path, const int width ) : m_buffer ( files ), m_width ( width )
{
  std::filesystem::path path = std::filesystem::canonical ( license_path );

  if ( is_valid_dir ( path.string () ) )
    {
      PRINT_LOG ( "error", "license file cannot be a directory" )
      exit ( EXIT_FAILURE );
    }

  file f ( path.string () );
  m_license_contents = f.read ();

  if ( m_license_contents.empty () )
    {
      return;
    }

  m_license_contents.insert ( m_license_contents.begin (), "/**\n" );

  for ( auto i = m_license_contents.begin () + 1; i < m_license_contents.end (); i++ )
    {
      std::string commented;

      for ( int i = 0; i != m_width; i++ )
        {
          commented += " ";
        }

      commented += "* ";
      commented += *i;
      commented += "\n";

      *i = commented;
    }

  m_license_contents.insert ( m_license_contents.end (), "*/\n" );
}

injector::~injector ()
{
}

void
injector::insert_file ( const std::string& fpath, const std::vector<std::string>& contents )
{
  if ( is_valid_dir ( fpath ) )
    {
      PRINT_LOG ( "warn", "skipping" << fpath << "beacuse it's a directory" )
      return;
    }

  if ( has_header ( fpath ) )
    {
      PRINT_LOG ( "warn", "skipping " << fpath << " because a comment/license header was found" )
      return;
    }

  std::vector<std::string> write {};

  for ( const std::string& lines : m_license_contents )
    {
      write.push_back ( lines );
    }

  write.push_back ( "\n" );

  for ( const std::string& lines : contents )
    {
      write.push_back ( lines + "\n" );
    }

  file f ( fpath );
  bool did_write = f.write ( write );

  if ( !did_write )
    {
      PRINT_LOG ( "error", "could not write to file: " << fpath );
    }
}

bool
injector::has_header ( const std::string& fpath ) const noexcept
{
  file f ( fpath );
  std::vector<std::string> contents = f.read ();

  if ( contents.empty () )
    {
      return false;
    }

  return contents[ 0 ].rfind ( "/*", 0 ) == 0 || contents[ 0 ].rfind ( "/**", 0 ) == 0;
}

void
injector::insert_all ()
{
  if ( m_license_contents.empty () )
    {
      PRINT_LOG ( "error", "license file is empty" )
      exit ( EXIT_FAILURE );
    }

  if ( m_buffer.empty () )
    {
      PRINT_LOG ( "error", "buffer is empty" )
      exit ( EXIT_FAILURE );
    }

  for ( const auto& map : m_buffer )
    {
      for ( const auto& [ key, value ] : map )
        {
          insert_file ( key, value );
        }
    }
}

}