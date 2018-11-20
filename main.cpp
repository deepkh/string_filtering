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

int main(int argc, char *argv[]) {
    int ret = -1;
    unsigned int i;
    string u8;
    std::vector<std::u16string> picked_up;
    DfaMap *root_map;

    if (test_cvt_utf8_utf16()) {
        printf("failed to test_cvt_utf8_utf16\n");
        goto finally;
    }

    test_rnd_gen();
    test_wf_keyword_generator();

    root_map = DfaMap::gen(100/*000*/, 5, picked_up, 5);
    for (i=0; i<picked_up.size(); i++) {
        u8 = cvt_utf16_utf8(picked_up[i]);
        printf("picked_up[%d]=%s\n", i, u8.c_str());
    }
   
    printf("press any key to exit.\n");
    getchar();
    delete root_map;

    ret = 0;
finally:
    return ret;
}
