/* "main" for the compiler driver.
   Copyright (C) 1987-2023 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* This source file contains "main" for the compiler driver.
   All of the real work is done within gcc.cc; we implement "main"
   in here for the "gcc" binary so that gcc.o can be used in
   libgccjit.so.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "xregex.h"
#include "obstack.h"
#include "intl.h"
#include "prefix.h"
#include "opt-suggestions.h"
#include "gcc.h"

/* Implement the top-level "main" within the driver in terms of
   driver::main (implemented in gcc.cc).  */

extern int main (int, char **);

/**
 * I use this to control the printf
 * because if you use printf, it will affect:
 * - configure script
 * - make script
 * They will cause the makefile to contain the printf you put, when you run
 * During build also will fail because some extra line were added into file
 * Usage: I only check the last argument got `-me` or not
 * To enable my printf, put `-me` at the last of the argument
 * eg: gcc test.c -me
*/
int ME_PRINTF = 0;

int
main (int argc, char **argv)
{  // MEE Breakpoints
  driver d (false, /* can_finalize */
	    false); /* debug */

   /**
    * Pointer study
    * **argv is double pointer
    * It holds the address of a pointer
    * The address is passed into this main function
    * so whenever you type `argv`, you are accessing the pointer that points to the array.
    * so is not like the `argv` is the 2nd pointer that points to 1st pointer then points to array
    * not like this: p2 -> p1 -> array
    * What's passed into this function, is the address of `p1`
    * So, by typing `argv[0]`, you are accessin the array already
    * I found that, by typing `*argv[0]`, you are accessing the 1st char of the 1st element of array
    * eg: ['/usr/gcc','/workspace/test.c',]
    * argv[0] = 0x7fffffffe442 "/usr/gcc"
    * argv[1] = 0x7fffffffe455 "/workspace/test.c"
    * *argv[0] = "/" (this is pointing the 1st char of the 1st element of array ("/usr/gcc"))
    * *argv[1] = "/" (This is pointing the 1st char of the 2nd element of array ("/workspace/test.c"))
    * argv[0][0] = 47 '/' (The 1st char of the 1st element of the array ("/usr/gcc"))
    * *argv[0][0] = no such thing
    * TBH, i dk how argv[0] works, it returns address of the element of the array? Then stops until null termination?
   */
   if(
      argv[argc-1][0] == '-' &&
      argv[argc-1][1] == 'm' &&
      argv[argc-1][2] == 'e'
   )
   {
      // gotta remove the argument
      // else will affect how gcc perform, like, gcc doesn't exepct there's `-me` argument in it
      ME_PRINTF = TRUE;
      argv[argc-1] = NULL;
      argc -= 1;
   }

  return d.main (argc, argv);
}
