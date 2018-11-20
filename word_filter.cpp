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

int main(int argc, char *argv[]) {
    int ret = -1;
    u16string utf16;
    string str, utf8;
    
    str = "嘿，你好;Hello;السلام عليكم;नमस्ते;今日は おっす;ਸਤਿ ਸ੍ਰੀ ਅਕਾਲ;안녕하십니까;chào bạn;வணக்கம் ;สวัสดี;નમસ્તે;မဂႆလာပၝ";
    cout << str << endl;

    utf16 = cvt_utf8_utf16(str);
    utf16_hex(utf16);
    
    utf8 = cvt_utf16_utf8(utf16);
    cout << utf8 << endl;

    return ret;
}
