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
#include <random>
#include <codecvt>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <locale>

using namespace std;

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
    printf("dump %lu of utf-16 to hex\n", utf16.size());
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
    printf("\n");
}

int test_cvt_utf8_utf16() {
    u16string utf16;
    string str, utf8;
    
    printf("-------test_cvt_utf8_utf16-------------------------------------------------------\n");
    str = "嘿，你好;Hello;السلام عليكم;नमस्ते;今日は おっす;ਸਤਿ ਸ੍ਰੀ ਅਕਾਲ;안녕하십니까;chào bạn;வணக்கம் ;สวัสดี;નમસ્તે;မဂႆလာပၝ";
    cout << str << endl;

    utf16 = cvt_utf8_utf16(str);
    utf16_hex(utf16);
    
    utf8 = cvt_utf16_utf8(utf16);
    cout << utf8 << endl;

    printf("-------------------------------------------------------------------------------------\n\n");
    return strcmp(str.c_str(), utf8.c_str());
}

//C++11 built-in random function
//http://chino.taipei/note-2016-1020C-11-%E7%9A%84-Random-library-%E4%BD%A0%E9%82%84%E5%9C%A8%E7%94%A8rand-%E5%97%8E/
int rnd_gen(int min, int max)
{   
    static std::random_device rd;
    static std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

int test_rnd_gen() {
    static int max_count = 10000;
    static int max_num = 100;
    int *dist = (int *) calloc(1, sizeof(int) * max_num);
    int i;
    printf("-------test_rnd_gen-------------------------------------------------------\n");
    for (i=0; i<max_count; i++) {
        dist[rnd_gen(0, max_num)]++;
    }
    for (i=0; i<max_num; i++) {
        if ((i%16)== 0) {
            printf("0x%08X ", i);
        }
        printf("%02d=%03d ", i, dist[i]);
        if ((i+1)%16 == 0) {
            printf("\n");
        }
    }
    printf("\n-------------------------------------------------------------------------------------\n\n");
    free(dist);
    return 0;
}
