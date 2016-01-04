/**
 * Copyright (C) 2015 Michele Laurenti
 * email: asmeikal [at] me [dot] com
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
 * You can find a copy of the GNU General Public License at 
 * http://www.gnu.org/licenses/gpl.html
 */

#include <CopyrightNotice.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static const char notice[] = " \
\n \
%s Copyright (C) %d %s\n \
This program comes with ABSOLUTELY NO WARRANTY; for details type 'w'.\n \
This is free software, and you are welcome to redistribute it\n \
under certain conditions; type 'c' for details. Type 'q' to exit.\n \
Type anything else to continue.\n \
";

static const char prompt[] = " \
\n> ";

static const char copyright[] = " \
\n \
Please visit http://www.gnu.org/licenses/gpl.html for details.\n \
";

static const char warranty[] = " \
\n \
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY \n \
APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT \n \
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY \n \
OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, \n \
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR \n \
PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE \n \
PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME \n \
THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n \
";

void copyright_notice(const char *pname, const unsigned int year, const char *author)
{
    fprintf(stderr, notice, pname, year, author);

    char in[10];

    while(1) {
        fprintf(stderr, prompt);
        fgets(in, 10, stdin);

        switch(in[0]) {
            case 'c':
                fprintf(stderr, copyright);
                break;

            case 'w':
                fprintf(stderr, warranty);
                break;

            case 'q':
                raise(SIGINT);
                break;

            default:
                fprintf(stderr, "\n");
                return;
        }

    }

}
