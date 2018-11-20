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

//0x4E00 ~ 0x9FCC: https://unicode-table.com/en/blocks/cjk-unified-ideographs/
//#define UNICODE_KEYWORD_RANGE_MIN 0x4E00
//#define UNICODE_KEYWORD_RANGE_MAX 0x9FCC
#define UNICODE_KEYWORD_RANGE_MIN 0x564F
#define UNICODE_KEYWORD_RANGE_MAX 0x565F

u16string wf_keyword_generator(int keyword_len_max)
{
    int i;
    int gen_num = 2 + rnd_gen(0, keyword_len_max - 1);
    u16string u16;
    //printf("gen_num: %d\n", gen_num);
    for (i=0; i<gen_num; i++) {
        u16 += (char16_t)rnd_gen(UNICODE_KEYWORD_RANGE_MIN, UNICODE_KEYWORD_RANGE_MAX);
    }
    return u16;
}

int test_wf_keyword_generator()
{
    u16string u16 = wf_keyword_generator(5);
    string u8 = cvt_utf16_utf8(u16);

    printf("-------test_wf_keyword_generator-------------------------------------------------------\n");
    cout << u8 << endl;
    utf16_hex(u16);
    printf("-------------------------------------------------------------------------------------\n\n");

    return 0;
}


DfaMap::DfaMap(int level)
:level(level)
,is_end(0)
{

}

DfaMap::~DfaMap()
{

}

int DfaMap::add(std::u16string &keyword)
{

    return 0;
}

int DfaMap::get(std::u16string &keyword)
{

    return 0;
}

void DfaMap::dump()
{

}

int DfaMap::isEnd()
{

    return 0;
}

DfaMap* DfaMap::gen(
    int num_keywords, int keyword_len_max
    , std::vector<u16string> &picked_up
    , int picked_up_num)
{
    int i, pos;
    DfaMap *root_map = new DfaMap(0);
    u16string u16;
    string u8;
    map<int,int> picked_up_pos;

    printf("-------DfaMap::gen-------------------------------------------------------\n");
    //generate the position of random pick up keyword
    for (i=0; i<picked_up_num; i++) {
        //guarantee we won't be duplicated
        while(1) {
            pos = rnd_gen(0, num_keywords - 1); 
            if (picked_up_pos[pos]) {
                printf("%d duplicated\n", pos);
                continue;
            }
            break;
        }
        picked_up_pos[pos] = 1;
    }

    //generate the num_keywords of random u16 string
    for (i=0; i<num_keywords; i++) {
        u16 = wf_keyword_generator(keyword_len_max);
        u8 = cvt_utf16_utf8(u16);
        printf("gen %d/%d=%s %s\n", i, num_keywords, u8.c_str(), picked_up_pos[i] ? "PICKED" : "");
        if (picked_up_pos[i]) {
            picked_up.push_back(u16);
        }
    }

    printf("-------------------------------------------------------------------------------------\n\n");
    return root_map;
}


