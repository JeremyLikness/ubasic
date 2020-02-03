/*
 * Copyright (c) 2006, Adam Dunkels
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "ubasic.h"
#include <stdio.h>

static const char program[] =
"10 print \"Welcome to WASI BASIC!\"\n\
20 print \"Try passing a filename\"\n\
";

/*---------------------------------------------------------------------------*/
int
main(int argc, char **argv)
{
  if (argc > 1) {
    char source[9999];
    FILE *fp = fopen(argv[1], "r"); 
    if (fp != NULL) {
      size_t newLen = fread(source, sizeof(char), 9999, fp);
      if ( ferror( fp ) != 0 ) {
        fputs("Error reading file", stderr);
      } else {
        source[newLen++] = '\0'; /* Just to be safe. */
      }

    fclose(fp);
    ubasic_init(source);
    }
  } 
  else {
      ubasic_init(program);
  }

  do {
    ubasic_run();
  } while(!ubasic_finished());

  return 0;
}
/*---------------------------------------------------------------------------*/
