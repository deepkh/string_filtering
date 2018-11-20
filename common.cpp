/*
 * Copyright (c) 2018, Gary Huang (deepkh@gmail.com)
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include "common.h"

u16string cvt_utf8_utf16(string &str) {
    wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
    u16string dest = convert.from_bytes(str.c_str());    
    return dest;
}

string cvt_utf16_utf8(u16string &str) {
    wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> conversion;
    string mbs = conversion.to_bytes((char16_t *) str.c_str());
    return mbs;
}

void utf16_hex(u16string &utf16) {
    unsigned int i;
    printf("-------dump %lu of utf-16 to hex-------------------------------------------------------\n", utf16.size());
    for (i=0; i<utf16.size(); i++) {
        if ((i%16)== 0) {
            printf("0x%08X ", i);
        }
        printf("%02X%02X "
            , (utf16[i] >> 8) & 0xFF
            , utf16[i] & 0xFF);
        if ((i+1)%16 == 0) {
            printf("\n");
        }
    }
    printf("\n-------------------------------------------------------------------------------------\n");
}

