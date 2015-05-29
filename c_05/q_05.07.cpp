/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include "bits_operation.hpp"

unsigned int
get_number(unsigned int bits)
{
	unsigned int v(0);

	for (size_t j(0); j < sizeof(unsigned int) * 8; ++j) {
		// v |= A[i][j] << j に該当
		if (!(bits & ((unsigned int)1 << j))) continue;
		v |= (unsigned int)1 << j;
	}

	return v;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	// n = 15と仮定 (重複を許す)
	bool flags[16];	// bucket
	unsigned int A[] = {0, 0, 1, 2, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	unsigned int k;

	std::memset((void*)flags, 0, sizeof(flags));

	// O(n) の数値群算出
	for (size_t i(0); i < sizeof(A)/sizeof(A[0]); ++i) {
		k = get_number(A[i]);	// O(1) の数値算出
		flags[k] = true;
	}

	// O(n) の探索
	for (k = 0; k < sizeof(flags)/sizeof(flags[0]); ++k) {
		if (flags[k]) continue;
		std::printf("NOT FOUND: %u\n", k);
	}

	// 重複がなければ、
	// 抜けのない場合の合計値から実際の合計値を引くば算出できる。

	return 0;
}
