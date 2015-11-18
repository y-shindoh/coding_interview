/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.08.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  片方の文字列が、もう片方の文字列の一部分になっているかどうかを
  調べるメソッド「isSubstring」が使えると仮定します。
  2つの文字列s1とs2が与えられたとき、
  isSubstringメソッドを一度だけ使ってs2がs1を回転させたものかどうかを
  判定するコードを書いてください
  (たとえば、「waterbottle」は「erbottlewat」を回転させたものになっています)。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * 文字列が他方の文字列の回転になっているかを確認
 * @param[in]	s1	文字列その1
 * @param[in]	s2	文字列その2
 * @param[out]	buffer	作業領域 (引数 @a s1 の長さの2倍+1の長さが必要)
 * @return	true: 回転になっている, false: 回転になっていない
 * @note	最悪計算量は O(mn)。ただし m, n はそれぞれ引数 @a s1, @a s2 の長さ。
			(実際には関数 @a std::strstr に依存する)
 */
bool
check_rotated(const char* s1,
			  const char* s2,
			  char* buffer)
{
	assert(s1);
	assert(s2);
	assert(buffer);

	if (std::strlen(s1) == std::strlen(s2)) {
		std::strcpy(buffer, s1);
		std::strcat(buffer, s1);
		if (std::strstr(buffer, s2)) return true;
	}

	return false;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const char strings[][16] = {"AAACCCabc",
								"ACCCabcAA",
								"ACCaCbcAA",
								"AACCCabcAA"};
	const size_t l = sizeof(strings) / sizeof(strings[0]);
	char buffer[16*2];

	for (size_t i(0); i < l; ++i) {
		for (size_t j(0); j < l; ++j) {
			if (i == j) continue;
			if (check_rotated(strings[i], strings[j], buffer)) {
				std::printf("ROTATED:     ");
			}
			else {
				std::printf("NOT ROTATED: ");
			}
			std::printf("'%s' => '%s'\n", strings[i], strings[j]);
		}
	}

	return 0;
}
