/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <utility>
#include "utility.hpp"

/**
 * 乱択クイック・ソートの実装
 * @param[in,out]	data	ソート対象の配列
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は平均 O(n log n)。最悪 O(n^2)。
 */
template<typename TYPE>
void
QuickSort(TYPE* data,
		  size_t length,
		  bool flag = true)
{
	assert(data);
	assert(length);

	if (length <= 1) return;

	if (flag) std::srand((unsigned)std::time(0));

	const size_t h = (size_t)std::rand() % length;	// 乱択
	size_t k(1);
	TYPE tmp;

	if (h != 0) {
		tmp = data[h];
		data[h] = data[0];
		data[0] = tmp;
	}

	for (size_t i(1); i < length; ++i) {
		if (data[0] <= data[i]) continue;
		if (k != i) {
			tmp = data[i];
			data[i] = data[k];
			data[k] = tmp;
		}
		++k;
	}

	if (1 < k) {
		tmp = data[0];
		data[0] = data[k-1];
		data[k-1] = tmp;
	}

	if (2 < k) QuickSort<TYPE>(data, k - 1, false);
	if (k + 1 < length) QuickSort<TYPE>(data + k, length - k, false);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
	const size_t l = sizeof(data) / sizeof(data[0]);

	print_array<int>(data, l, "BEFORE");

	QuickSort<int>(data, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
