/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  空の文字列が点在するソート済みの文字列配列があります。
  この配列の中から特定の文字列の位置を見つけるメソッドを書いてください。

  例:
  入力: find "ball" in {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""}
  出力: 4
 */

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include "utility.hpp"

/**
 * 空文字列を間に含むソート済み単語列から単語を検索
 * @param[in]	words	空文字列を間に含むソート済み単語列
 * @param[in]	length	配列 @a words の要素数 (空文字列を含む)
 * @param[in]	key	探索対象の単語
 * @return	配列 @a words 中の該当単語のインデックス (検索失敗時には @a INVALID_INDEX が返る)
 * @note	配列に空文字列がなければ最悪計算時間は O(log n)。あれば O(n)。
			ただし n は @a length に等しい。
 */
size_t
find_words(const char** words,
		   size_t length,
		   const char* key)
{
	assert(words);
	assert(0 < length);
	assert(key);

	size_t s(0);
	size_t e(length - 1);
	size_t i;
	size_t j(INVALID_INDEX);
	int r;

	while (s <= e) {
		i = (s + e) / 2;
		if (i == j) break;
		j = i;

		while (s < i && !words[i][0]) --i;
		while (i < e && !words[i][0]) ++i;

		if (!words[i][0]) return INVALID_INDEX;

		r = std::strcmp(key, words[i]);

		if (r < 0) {
			if (0 == i) break;
			e = i - 1;
			continue;
		}

		if (0 < r) {
			s = i + 1;
			continue;
		}

		return i;
	}

	return INVALID_INDEX;
}

/**
 * 動作確認用コマンド
 */
int
main()
{
	const char* words[] = {"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
	const char* key = words[4];
	size_t l = sizeof(words) / sizeof(words[0]);
	size_t i = find_words(words, l, key);

	if (i < INVALID_INDEX) {
		std::printf("%s: %lu\n", key, i);
	}
	else {
		std::printf("%s: -\n", key);
	}

	return 0;
}
