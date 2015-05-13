/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstdio>
#include <cstring>
#include <vector>

/**
 * 文字列圧縮後の長さの算出
 * @param[in]	string	圧縮対象の文字列
 * @note	圧縮方法は "aaabbcaaa" => "a3b2c1a3" というもの。
 * @note	対象は US-ASCII のみとする。
 */
size_t
replaced_string_length(const char* string)
{
	const size_t l = std::strlen(string);
	size_t n(0);

	if (0 < l) {
		char c('\0');
		size_t m(1);

		for (size_t i(0); i <= l; ++i) {
			if (c == string[i]) {
				++m;
			}
			else {
				if (c) {
					n += 2;
					while (m /= 10) ++n;
					m = 1;
				}
				c = string[i];
			}
		}
	}

	return n;
}


/**
 * 文字列圧縮
 * @param[in,out]	string	圧縮対象の文字列
 * @note	圧縮方法は "aaabbcaaa" => "a3b2c1a3" というもの。
 * @note	先頭・末尾からの逐次上書きは "ababccccccccccccccabab" などで失敗する。
 * @note	対象は US-ASCII のみとする。
 */
void
replaced_string(char* string)
{
	const size_t l = std::strlen(string);

	if (l <= replaced_string_length(string)) return;

	char c('\0');
	size_t m(1);
	std::vector<char> letters;	// 逐次上書きを避ける
	std::vector<int> counts;	// 逐次上書きを避ける
	letters.reserve(l / 2);
	counts.reserve(l / 2);

	for (size_t i(0); i <= l; ++i) {
		if (c == string[i]) {
			++m;
		}
		else {
			if (c) {
				letters.push_back(c);
				counts.push_back(m);
				m = 1;
			}
			c = string[i];
		}
	}

	const size_t n = letters.size();
	string[0] = '\0';
	m = 0;

	for (size_t i(0); i < n; ++i) {
		while (string[m]) ++m;
		string[m++] = letters[i];
		std::sprintf(string+m, "%d", counts[i]);
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[][1024] = {"aabcccccaaa",
						   "aabcccccaaaeeeeeeeeeed"};
	size_t length;

	for (size_t i(0); i < sizeof(buffer)/sizeof(buffer[0]); ++i) {
		length = std::strlen(buffer[i]);
		std::printf("'%s' [%lu]\n", buffer[i], length);

		length = replaced_string_length(buffer[i]);
		replaced_string(buffer[i]);
		std::printf("=> '%s' [%lu]\n", buffer[i], length);
	}

	return 0;
}
