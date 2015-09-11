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
 * @note	計算量は O(n^2)。
 */
template<typename TYPE>
void
BubbleSort(TYPE* data,
		   size_t length)
{
	assert(data);
	assert(length);

	TYPE tmp;
	bool flag;

	for (size_t i(0); i < length; ++i) {
		flag = true;
		for (size_t j(1); j < length - i; ++j) {
			if (data[j-1] <= data[j]) continue;	// 小さい順
			tmp = data[j-1];
			data[j-1] = data[j];
			data[j] = tmp;
			flag = false;
		}
		if (flag) break;
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
