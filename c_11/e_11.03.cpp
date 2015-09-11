/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cassert>
#include "utility.hpp"

/**
 * セレクション・ソートの実装
 * @param[in,out]	data	ソート対象の配列
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は O(n^2)。
 */
template<typename TYPE>
void
SelectionSort(TYPE* data,
			  size_t length)
{
	assert(data);
	assert(length);

	size_t h;
	TYPE tmp;

	for (size_t i(0); i < length; ++i) {
		h = i;
		for (size_t j(i+1); j < length; ++j) {
			if (data[h] <= data[j]) continue;
			h = j;
		}
		if (i == h) continue;
		tmp = data[h];
		data[h] = data[i];
		data[i] = tmp;
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

	SelectionSort<int>(data, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
