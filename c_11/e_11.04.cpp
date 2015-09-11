/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstring>
#include <cassert>
#include <utility>
#include "utility.hpp"

/**
 * マージ・ソートの実装
 * @param[in,out]	data	ソート対象の配列
 * @param	buffer	作業領域
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は O(n log n)。
 */
template<typename TYPE>
void
MergeSort(TYPE* data,
		  TYPE* buffer,
		  size_t length)
{
	assert(data);
	assert(buffer);
	assert(0 < length);

	if (length <= 2) {
		if (length == 2) {
			if (data[0] > data[1]) {
				TYPE tmp = data[0];
				data[0] = data[1];
				data[1] = tmp;
			}
		}
		return;
	}

	size_t center = length / 2;

	MergeSort<TYPE>(data, buffer, center);
	MergeSort<TYPE>(data + center, buffer, length - center);

	std::memcpy((void*)buffer, (const void*)data, sizeof(TYPE) * center);

	size_t i(0);
	size_t j(center);

	for (size_t k(0); k < length; ++k) {
		if (buffer[i] <= data[j] || j == length) {
			data[k] = buffer[i];
			if (++i == center) break;
		}
		else {
			data[k] = data[j];
			++j;
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
	int buffer[10];
	const size_t l = sizeof(data) / sizeof(data[0]);

	print_array<int>(data, l, "BEFORE");

	MergeSort<int>(data, buffer, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
