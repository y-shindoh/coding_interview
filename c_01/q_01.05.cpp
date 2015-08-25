/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  文字の連続する数を使って基本的な文字圧縮を行うメソッドを実装してください。
  たとえば、「aabcccccaaa」は「a2b1c5a3」のようにしてください。
  もし、圧縮変換された文字列が元の文字列よりも短くならなかった場合は、
  元の文字列を返してください。
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

/**
 * 圧縮後の文字列長を算出
 * @param[in]	s	圧縮対象の文字列
 * @note	処理対象は US-ASCII。
 * @note	最悪計算量は O(n)。ただし n は引数 @a s の長さ。
 */
size_t
compressed_length(const char* s)
{
	assert(s);

	size_t c(0);
	size_t n(0);
	char p = '\0';

	while (*s) {
		if (*s != p) {
			p = *s;
			if (0 < c) {
				++n;
				while (0 < c) {
					++n;
					c /= 10;
				}
			}
			c = 1;
		}
		else {
			++c;
		}
		++s;
	}

	if (0 < c) {
		++n;
		while (0 < c) {
			++n;
			c /= 10;
		}
	}

	return n;
}

/**
 * 文字列を圧縮
 * @param[in,out]	s	処理対象の文字列
 * @param[out]	buffer_c	作業領域
 * @param[out]	buffer_i	作業領域
 * @note	圧縮後の文字列長が圧縮前のそれより長い場合はなにもしない。
 * @note	処理対象は US-ASCII。
 * @note	最悪計算量は O(n)。ただし n は引数 @a s の長さ。
 * @note	最悪メモリ使用量は O(n)。ただし n は引数 @a s の長さ。
 * @note	バッファ未使用でも実装できそうだが、処理が非常に複雑になる。
 */
void
compress_string(char* s,
				std::vector<char>& buffer_c,
				std::vector<size_t>& buffer_i)
{
	assert(s);

	size_t l = std::strlen(s);

	if (l < compressed_length(s)) return;

	char c = '\0';

	buffer_c.clear();
	buffer_i.clear();

	for (size_t i(0); i < l; ++i) {
		if (c != s[i]) {
			c = s[i];
			buffer_c.push_back(c);
			buffer_i.push_back(1);
		}
		else {
			buffer_i.back()++;
		}
	}

	l = buffer_c.size();
	std::memset((void*)s, 0, sizeof(char) * (l + 1));

	for (size_t i(0); i < l; ++i) {
		sprintf(s, "%c%lu", buffer_c[i], buffer_i[i]);
		while (*s) ++s;
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[][1024] = {"aabcccccaaa",
						   "aabcccccaaaeeeeeeeeeed",
						   "ababaa"};
	size_t l1, l2;

	std::vector<char> buffer_c;
	std::vector<size_t> buffer_i;

	for (size_t i(0); i < sizeof(buffer)/sizeof(buffer[0]); ++i) {
		l1 = std::strlen(buffer[i]);
		l2 = compressed_length(buffer[i]);
		std::printf("'%s' [%lu=>%lu]\n", buffer[i], l1, l2);

		compress_string(buffer[i], buffer_c, buffer_i);
		std::printf("=> '%s'\n", buffer[i]);
	}

	return 0;
}
