/*

Copyright (c) 2009-2010, Apple Inc. All rights reserved.
Copyright (c) 2011-2013, ARM Limited. All rights reserved.
Copyright (c) 2004,2006,2012,2013, Intel Corporation. All rights reserved.
Copyright (c) 2013, Matthias Wenzel. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "efiguid.h"
#include "efi_guid_list.h"

#define MAX_GUID_NAME_LEN 4096

void usage(void)
{
  printf("usage for efiguid:\n");
  printf("\n");
  printf("\tefiguid [-e] [-d | -1 | -2 | -4 ]\n");
  printf("\n");
  printf("\tefiguid       : emits its own header efi_guid_list.h\n");
  printf("\t                you may edit/expand efi_guid_list.h and rerun\n");
  printf("\t                \"efiguid > efi_guid_list.h && make\"\n");
  printf("\n");
  printf("\tefiguid -e    : swap default endianess\n");
  printf("\n");
  printf("\tefiguid -d    : emits an (U)EFI standard header\n");
  printf("\n");
  printf("\tefiguid -1    : emits 128 bit (full) GUIDs in hex to be used e.g. by bgrep\n");
  printf("\n");
  printf("\tefiguid -2    : emits first 64 bit of GUIDs in hex to be used e.g. by bgrep\n");
  printf("\n");
  printf("\tefiguid -4    : emits first 32 bit of GUIDs in hex to be used e.g. by bgrep\n");
  printf("\n");
}

void usage_error_exit(void)
{
  usage();
  exit(1);
}

void emit_efi_guid_list_h(void)
{
  int i;

  printf(
"/*\n"
"\n"
"Copyright (c) 2009-2010, Apple Inc. All rights reserved.\n"
"Copyright (c) 2011-2013, ARM Limited. All rights reserved.\n"
"Copyright (c) 2004,2006,2012,2013, Intel Corporation. All rights reserved.\n"
"Copyright (c) 2013, Matthias Wenzel. All rights reserved.\n"
"\n"
"Redistribution and use in source and binary forms, with or without\n"
"modification, are permitted provided that the following conditions\n"
"are met:\n"
"\n"
"* Redistributions of source code must retain the above copyright\n"
"  notice, this list of conditions and the following disclaimer.\n"
"* Redistributions in binary form must reproduce the above copyright\n"
"  notice, this list of conditions and the following disclaimer in\n"
"  the documentation and/or other materials provided with the\n"
"  distribution.\n"
"\n"
"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n"
"\"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n"
"LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS\n"
"FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE\n"
"COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,\n"
"INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,\n"
"BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;\n"
"LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER\n"
"CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\n"
"LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN\n"
"ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n"
"POSSIBILITY OF SUCH DAMAGE.\n"
"\n"
"*/\n"
"\n");



  printf("/* this header is generated.\n");
  printf(" * still you may edit it, as it can regenerate itself.\n");
  printf(" * to do so rerun \"efiguid > efi_guid_list.h && make\".\n");
  printf(" */\n");
  printf("\n");
  printf("#ifndef _EFI_GUID_LIST_H_\n");
  printf("#define _EFI_GUID_LIST_H_\n");
  printf("\n");
  printf("#include \"efiguid.h\"\n");
  printf("\n");

  printf("NAME_EFI_GUID all_efi_guids[] =\n");
  printf("{\n");

  for (i=0; i<sizeof(all_efi_guids) / sizeof(NAME_EFI_GUID); i++)
  {
    char buf[MAX_GUID_NAME_LEN];
    if (strlen(all_efi_guids[i].guid_name) > MAX_GUID_NAME_LEN-4)
    {
      fprintf(stderr, "nope, your GUID name is too long. index: %d\n", i);
      exit(1);
    }
    snprintf(buf, MAX_GUID_NAME_LEN, "\"%s\",", all_efi_guids[i].guid_name);
    printf("  {%-70s { 0x%.8x, 0x%.4x, 0x%.4x, { 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x } } },\n",
            buf,
            all_efi_guids[i].guid.data1,
            all_efi_guids[i].guid.data2,
            all_efi_guids[i].guid.data3,
            all_efi_guids[i].guid.data4[0],
            all_efi_guids[i].guid.data4[1],
            all_efi_guids[i].guid.data4[2],
            all_efi_guids[i].guid.data4[3],
            all_efi_guids[i].guid.data4[4],
            all_efi_guids[i].guid.data4[5],
            all_efi_guids[i].guid.data4[6],
            all_efi_guids[i].guid.data4[7]
            );
  }
  printf("};\n");
  printf("\n");
  printf("#endif /* _EFI_GUID_LIST_H_ */\n");
}

void emit_efi_guid_definitions(void)
{
  int i;

  printf("/* this header is generated. \n");
  printf(" * DO NOT EDIT.\n");
  printf(" * edit efi_guid_list.h instead,\n");
  printf(" * and rerun \"make && efiguid -d\" > my_guids.h\n");
  printf(" */\n");


  for (i=0; i<sizeof(all_efi_guids) / sizeof(NAME_EFI_GUID); i++)
  {
    printf("#define %-70s { 0x%.8x, 0x%.4x, 0x%.4x, { 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x } }\n",
            all_efi_guids[i].guid_name,
            all_efi_guids[i].guid.data1,
            all_efi_guids[i].guid.data2,
            all_efi_guids[i].guid.data3,
            all_efi_guids[i].guid.data4[0],
            all_efi_guids[i].guid.data4[1],
            all_efi_guids[i].guid.data4[2],
            all_efi_guids[i].guid.data4[3],
            all_efi_guids[i].guid.data4[4],
            all_efi_guids[i].guid.data4[5],
            all_efi_guids[i].guid.data4[6],
            all_efi_guids[i].guid.data4[7]
            );
  }
}

void emit_efi_guid128(void)
{
  int i;

  for (i=0; i<sizeof(all_efi_guids) / sizeof(NAME_EFI_GUID); i++)
  {
    printf("%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x\n",
            ( all_efi_guids[i].guid.data1 >>  0 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >>  8 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >> 16 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >> 24 ) & 0xff,

            ( all_efi_guids[i].guid.data2 >>  0 ) & 0xff,
            ( all_efi_guids[i].guid.data2 >>  8 ) & 0xff,

            ( all_efi_guids[i].guid.data3 >>  0 ) & 0xff,
            ( all_efi_guids[i].guid.data3 >>  8 ) & 0xff,

            all_efi_guids[i].guid.data4[0],
            all_efi_guids[i].guid.data4[1],
            all_efi_guids[i].guid.data4[2],
            all_efi_guids[i].guid.data4[3],
            all_efi_guids[i].guid.data4[4],
            all_efi_guids[i].guid.data4[5],
            all_efi_guids[i].guid.data4[6],
            all_efi_guids[i].guid.data4[7]
            );
  }
}

void emit_efi_guid64(void)
{
  int i;

  for (i=0; i<sizeof(all_efi_guids) / sizeof(NAME_EFI_GUID); i++)
  {
    printf("%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x\n",
            ( all_efi_guids[i].guid.data1 >>  0 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >>  8 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >> 16 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >> 24 ) & 0xff,

            ( all_efi_guids[i].guid.data2 >>  0 ) & 0xff,
            ( all_efi_guids[i].guid.data2 >>  8 ) & 0xff,

            ( all_efi_guids[i].guid.data3 >>  0 ) & 0xff,
            ( all_efi_guids[i].guid.data3 >>  8 ) & 0xff
            );
  }
}

void emit_efi_guid32(void)
{
  int i;

  for (i=0; i<sizeof(all_efi_guids) / sizeof(NAME_EFI_GUID); i++)
  {
    printf("%.2x%.2x%.2x%.2x\n",
            ( all_efi_guids[i].guid.data1 >>  0 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >>  8 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >> 16 ) & 0xff,
            ( all_efi_guids[i].guid.data1 >> 24 ) & 0xff
            );
  }
}

int main(int argc, char ** argv)
{
  fprintf(stderr, "/* %-40s: %lu */\n", "number of GUIDs", sizeof(all_efi_guids) / sizeof(NAME_EFI_GUID));

  int i;
  int opt;
  int mode = OPT_OWN_HEADER;
  int swap_endianess = 0;

  while ((opt = getopt(argc, argv, "ed124")) != -1)
  {
    switch (opt)
    {
      case 'e':
        swap_endianess = 1;
        break;
      case 'd':
        mode = OPT_EFI_HEADER;
        break;
      case '1':
        mode = OPT_GUID128;
        break;
      case '2':
        mode = OPT_GUID64;
        break;
      case '4':
        mode = OPT_GUID32;
        break;
      default:
        usage_error_exit();
    }
  }

  if (swap_endianess)
  {
    for (i=0; i<sizeof(all_efi_guids) / sizeof(NAME_EFI_GUID); i++)
    {
      all_efi_guids[i].guid.data1 = swap32(all_efi_guids[i].guid.data1);
      all_efi_guids[i].guid.data2 = swap16(all_efi_guids[i].guid.data2);
      all_efi_guids[i].guid.data3 = swap16(all_efi_guids[i].guid.data3);
    }
  }

  switch (mode)
  {
    case OPT_OWN_HEADER:
      emit_efi_guid_list_h();
      break;
    case OPT_EFI_HEADER:
      emit_efi_guid_definitions();
      break;
    case OPT_GUID128:
      emit_efi_guid128();
      break;
    case OPT_GUID64:
      emit_efi_guid64();
      break;
    case OPT_GUID32:
      emit_efi_guid32();
      break;
    default:
      usage_error_exit();
  }
  return 0;
}
