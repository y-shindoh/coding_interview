/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstring>
#include <cassert>
#include "utility.hpp"

/**
 * 基数ソートの実装 (直接基数法)
 * @param[in,out]	data	ソート対象の配列
 * @param[out]	buffer	作業領域 (引数 @a data 以上の広さが必要)
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は平均 O(kn)。ただし k = log_N M (Mは @a data の最大値)。
 * @note	テンプレートの型 @a TYPE は符号なし整数を指定すること。
 * @note	テンプレートの整数 @a N はバケットの大きさ。
 */
template<typename TYPE, size_t N>
void
RadixSort(TYPE* data,
		  TYPE* buffer,
		  size_t length)
{
	assert(data);
	assert(buffer);
	assert(0 < length);

	TYPE* array[] = {data, buffer};
	bool flag;
	size_t counts[N+1];
	size_t h(0);
	size_t k, j;
	TYPE d(1);

	while ('-') {
		std::memset((void*)counts, 0, sizeof(size_t) * (N+1));
		k = 1 - h;

		flag = true;
		for (size_t i(0); i < length; ++i) {
			j = (size_t)(array[h][i] / d % N + 1);
			counts[j]++;
			if (N <= array[h][i] / d) flag = false;
		}

		for (size_t i(2); i < N; ++i) {
			counts[i] += counts[i-1];
		}

		for (size_t i(0); i < length; ++i) {
			j = (size_t)(array[h][i] / d % N);
			j = counts[j]++;
			array[k][j] = array[h][i];
		}

		if (flag) break;

		h = k;
		d *= N;
	}

	if (h == 0) std::memcpy((void*)data, (const void*)buffer, sizeof(TYPE) * length);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
	int buffer[1024];
	const size_t l = sizeof(data) / sizeof(data[0]);

	print_array<int>(data, l, "BEFORE");

	RadixSort<int, 4>(data, buffer, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
