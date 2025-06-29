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
#include "termcolor.h"

int
main ( int argc, char* argv[] )
{
  ligen2::ligen_result_t exec = ligen2::execute ( argc, argv );
  if ( !exec.succeeded )
    {
      PRINT_LOG ( "error", exec.cause )
      exit ( EXIT_FAILURE );
    }

  PRINT_LOG ( "log", "successfully injected license header" );
  return EXIT_SUCCESS;
}