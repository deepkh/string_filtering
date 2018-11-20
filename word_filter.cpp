#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

//ref from: https://stackoverflow.com/questions/7153935/how-to-convert-utf-8-stdstring-to-utf-16-stdwstring
wstring cvt_utf8_utf16x(string &utf8) {
    vector<unsigned long> unicode;
    size_t i = 0;
    while (i < utf8.size())
    {
        unsigned long uni;
        size_t todo;
        bool error = false;
        unsigned char ch = utf8[i++];
        if (ch <= 0x7F)
        {
            uni = ch;
            todo = 0;
        }
        else if (ch <= 0xBF)
        {
            throw std::logic_error("not a UTF-8 string");
        }
        else if (ch <= 0xDF)
        {
            uni = ch&0x1F;
            todo = 1;
        }
        else if (ch <= 0xEF)
        {
            uni = ch&0x0F;
            todo = 2;
        }
        else if (ch <= 0xF7)
        {
            uni = ch&0x07;
            todo = 3;
        }
        else
        {
            throw std::logic_error("not a UTF-8 string");
        }
        for (size_t j = 0; j < todo; ++j)
        {
            if (i == utf8.size())
                throw std::logic_error("not a UTF-8 string");
            unsigned char ch = utf8[i++];
            if (ch < 0x80 || ch > 0xBF)
                throw std::logic_error("not a UTF-8 string");
            uni <<= 6;
            uni += ch & 0x3F;
        }
        if (uni >= 0xD800 && uni <= 0xDFFF)
            throw std::logic_error("not a UTF-8 string");
        if (uni > 0x10FFFF)
            throw std::logic_error("not a UTF-8 string");
        unicode.push_back(uni);
    }
    std::wstring utf16;
    for (size_t i = 0; i < unicode.size(); ++i)
    {
        unsigned long uni = unicode[i];
        if (uni <= 0xFFFF)
        {
            utf16 += (wchar_t)uni;
        }
        else
        {
            uni -= 0x10000;
            utf16 += (wchar_t)((uni >> 10) + 0xD800);
            utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
        }
    }
    return utf16;
}

void wstr_hex(const wchar_t *str, int len) {
	int i;
	printf("-------dump %d of utf-16 to hex-------------------------------------------------------\n", len);
	for (i=0; i<len; i++) {
		printf("%02X%02X "
			, (str[i] >> 8) & 0xFF
			, str[i] & 0xFF);
		if ((i+1)%16 == 0) {
			printf("\n");
		}
	}
	printf("\n-------------------------------------------------------------------------------------\n");
}

int main(int argc, char *argv[]) {
	string str = "嘿你好";
	wstring wstr= cvt_utf8_utf16x(str);
	cout << str << endl;
	wstr_hex(wstr.c_str(), wstr.size());
	return 0;
}
