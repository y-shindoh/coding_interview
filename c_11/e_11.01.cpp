/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cassert>
#include <utility>
#include "utility.hpp"

/**
 * バブル・ソートの実装
 * @param[in,out]	data	ソート対象の配列
 * @param[in]	length	配列 @a data の長さ
 * @note	最悪計算量は O(n^2)。
 */
template<typename TYPE>
void
BubbleSort(TYPE* data,
		   size_t length)
{
	assert(data);
	assert(0 < length);
	assert(length < ~(size_t)0);

	size_t h(~(size_t)0);
	size_t k(length);

	while (k < h) {
		h = k;
		for (size_t i(1); i < h; ++i) {
			if (data[i-1] <= data[i]) continue;	// 小さい順
			std::swap(data[i-1], data[i]);
			k = i;
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
	const size_t l = sizeof(data) / sizeof(data[0]);

	print_array<int>(data, l, "BEFORE");

	BubbleSort<int>(data, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
