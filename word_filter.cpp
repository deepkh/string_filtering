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

#include "word_filter.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

u16string wf_keyword_generator(int unicode_range_min, int unicode_range_max, int keyword_len_max)
{
    int i;
    int gen_num = rnd_gen(1, keyword_len_max+1);
    u16string u16;
    for (i=0; i<gen_num; i++) {
        u16 += (char16_t)rnd_gen(unicode_range_min, unicode_range_max);
    }
    return u16;
}

int test_wf_keyword_generator()
{
    //0x4E00 ~ 0x9FCC: https://unicode-table.com/en/blocks/cjk-unified-ideographs/
    u16string u16 = wf_keyword_generator(0x4E00, 0x9FCC, 12);
    string u8 = cvt_utf16_utf8(u16);

    printf("-------test_wf_keyword_generator-------------------------------------------------------\n");
    cout << u8 << endl;
    utf16_hex(u16);
    printf("\n-------------------------------------------------------------------------------------\n\n");

    return 0;
}
