/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cassert>
#include "utility.hpp"

/**
 * インサーション・ソートの実装
 * @param[in,out]	data	ソート対象の配列
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は O(n^2)。
 */
template<typename TYPE>
void
InsertionSort(TYPE* data,
			  size_t length)
{
	assert(data);
	assert(length);

	TYPE tmp;

	for (size_t i(1); i < length; ++i) {
		while (data[i-1] > data[i]) {
			tmp = data[i-1];
			data[i-1] = data[i];
			data[i] = tmp;
			if (--i == 0) break;
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

	InsertionSort<int>(data, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
