/*
* Ligen. A simple header-only library to generate licenses for your project.
* Copyright (C) 2024. Mustafa Malik
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __LIB_LIGEN_H__
#define __LIB_LIGEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <limits.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#if defined(_WIN32)
#   error Ligen only runs on Linux and macOS ONLY
#endif

#if (defined(__STDC__) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901)
#   include <stdbool.h>
#else
    typedef enum bool { true = 1, false = 0 } bool;
#endif

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define LIPRNT( COL, fmt, ... ) \
    printf("%s", KNRM); \
    printf("%s", "[LIGEN]: "); \
    printf("%s", COL); \
    printf(fmt, __VA_ARGS__);

/*
Design:

- Read (finds files)
- Gen headers (writes)

*/

const char* __LIGEN_USAGE__ = "\nLigen Usage\n\tligen <root dir> <license path>\n\nRun ligen --help for more.";

bool
is_c_file( const char* contents )
{
    do {
        if ( *contents == '.' && *( contents + 1 ) == 'c' ) return true;
        *contents++;
    } while ( *contents != '\0' );

    return false;
}

bool
has_license ( const char* contents )
{
    do {
        if ( *contents == '/' && *( contents + 1 ) == '*' ) return true;
        *contents++;
    } while ( *contents != '\0' );

    return false;
}

/// TODO: Make it generic to all languages later on
void
get_c_files( char* buffer[], const char* root, int* actual )
{
    struct dirent* dp;
    DIR* dfd;

    char* dir = ( char* ) root;
    if ( ( dfd = opendir( dir ) ) == NULL )
        return;

    int count = 0;

    while ( ( dp = readdir( dfd ) ) != NULL )
    {
        if ( is_c_file( dp->d_name ) )
        {
            buffer[count] = dp->d_name;
            count++;
        }
    }

    *actual = count;
    buffer[count] = 0;
}

char*
get_awd ( void )
{
    char* cwd = ( char* ) malloc( PATH_MAX * sizeof( char* ) );
    if ( getcwd( cwd, PATH_MAX ) != NULL )
        return cwd;
    return NULL;
}

const char*
get_data ( const char* fp )
{
    FILE* f = fopen( fp, "r" );

    if ( f == NULL )
        return NULL;

    fseek( f, 0, SEEK_END );
    long fs = ftell( f );
    fseek( f, 0, SEEK_SET );

    char* buffer = ( char* ) malloc( fs + 1 );
    
    if ( buffer == NULL )
    {
        fclose( f );
        return NULL;
    }

    fread( buffer, 1, fs, f );
    buffer[ fs ] = '\0';
    fclose( f );

    return (const char*) buffer;
}

void
set_data ( const char* file_path, const char* buffer )
{
    // Warning: Ligen expects you to make sure the path is valid
    FILE* f;
    if ( ( f = fopen( file_path, "w" ) ) != NULL )
    {
        fprintf( f, "%s", buffer );
        fclose( f );
    }
}

bool
gen_headers ( const char* target_path, const char* header_path )
{
    char* awd = get_awd();
    LIPRNT(KGRN, "%s\n", "Generating license headers...");

    char* files_avail[20];
    int files_avail_count;

    get_c_files( files_avail, awd, &files_avail_count );

    for (int i = 0; i < 19; i++)
    {
        if (files_avail[i] == 0) break;
        printf("%s\n", files_avail[i]);
    }

    // Iterate through all C files
    for ( int i = 0; i < files_avail_count; i++ )
    {
        const char* license_text    = get_data( header_path );
        const char* tmp_source      = get_data( files_avail[i] );

        if ( license_text == NULL || tmp_source == NULL )
            return false;

        char* n_src = (char*) malloc( ( sizeof( license_text ) + sizeof( tmp_source ) ) + 1 );
        strcat( n_src, license_text );
        strcat( n_src, "\n\n" );
        strcat( n_src, tmp_source );

        if ( has_license( tmp_source ) )
        {
            LIPRNT(KRED, "%s%s%s\n", "Unable to generate license header for: ", files_avail[i], " license already exists");
            continue;
        }
        else
            set_data( files_avail[i], n_src );

        free( ( char* ) license_text );
        free( ( char* ) tmp_source );
        free( n_src );
    }

    LIPRNT(KGRN, "%s\n", "Operation Completed.");

    free( awd );

    return true;
}

#endif /* __LIB_LIGEN_H__ */