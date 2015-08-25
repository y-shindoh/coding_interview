/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  2つの文字列が与えられたとき、
  片方がもう片方の並び替えになっているかどうかを決定するメソッドを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

#define	BUFFER_LENGTH	((size_t)0x100)

/**
 * 2つの文字列が並び替えの関係にあるか確認
 * @param[out]	buffer	作業領域
 * @param[in]	s1	確認対象の文字列
 * @param[in]	s2	確認対象の文字列
 * @return	true: 並び替えの関係にある, false: ない
 * @note	処理対象はUS-ASCIIに限定する。大文字小文字を区別する。
 * @note	最悪計算量は O(n)。ただし n は BUFFER_LENGTH かそれぞれの入力文字列の長さの最大値。
 */
bool
check_anagram(int buffer[BUFFER_LENGTH],
			  const char* s1,
			  const char* s2)
{
	std::memset((void*)buffer, 0, sizeof(int) * BUFFER_LENGTH);
	size_t i;
	int n(0);

	while (*s1) {
		i = (size_t)*s1++;
		buffer[i]++;
		n++;
	}

	while (*s2) {
		i = (size_t)*s2++;
		buffer[i]--;
		n--;
	}

	if (!n) return false;	// 長さが異なる

	for (size_t j(0); j < BUFFER_LENGTH; ++j) {
		if (buffer[j]) return false;
	}

	return true;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int buffer[BUFFER_LENGTH];
	char sample[][16] = {"AbCdBC.", "AbcdBC.", "CdB.bCA"};
	const size_t l = sizeof(sample) / sizeof(sample[0]);

	for (size_t i(0); i < l; ++i) {
		std::printf("%lu: '%s'\n", i, sample[i]);
	}

	for (size_t i(0); i < l; ++i) {
		for (size_t j(i+1); j < l; ++j) {
			if (check_anagram(buffer, sample[i], sample[j])) {
				std::printf("%lu == %lu\n", i, j);
			}
			else {
				std::printf("%lu != %lu\n", i, j);
			}
		}
	}

	return 0;
}
