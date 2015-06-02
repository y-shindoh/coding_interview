/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <utility>

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
	for (size_t i(0); i < length; ++i) {
		h = i;
		for (size_t j(i+1); j < length; ++j) {
			if (data[h] <= data[j]) continue;
			h = j;
		}
		if (i != h) std::swap<TYPE>(data[i], data[h]);
	}
}

/**
 * 配列の表示
 */
template<typename TYPE>
void
print_array(const TYPE* data,
			size_t length,
			const char* prefix = 0)
{
	if (prefix) std::printf("%s:\t", prefix);
	for (size_t i(0); i < length; ++i) {
		if (0 < i) std::printf(", ");
		std::printf("%G", (double)data[i]);
	}
	std::printf("\n");
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
