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

#ifndef _EFIGUID_H_
#define _EFIGUID_H_

#include <stdint.h>

typedef struct {
  uint32_t  data1;
  uint16_t  data2;
  uint16_t  data3;
  uint8_t   data4[8];
} EFI_GUID;


typedef struct {
  char   * guid_name;
  EFI_GUID guid;
} NAME_EFI_GUID;

#define swap32(x) \
  ((x >> 24) & 0x000000ff) | \
  ((x >> 16) & 0x0000ff00) | \
  ((x << 16) & 0x00ff0000) | \
  ((x << 24) & 0xff000000)

#define swap16(x) \
  ((x >> 8) & 0x00ff) | \
  ((x << 8) & 0xff00)

#define OPT_OWN_HEADER 0x0001
#define OPT_EFI_HEADER 0x0002
#define OPT_GUID128    0x0010
#define OPT_GUID64     0x0020
#define OPT_GUID32     0x0040

#endif /* _EFIGUID_H_ */
