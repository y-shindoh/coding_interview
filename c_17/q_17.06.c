/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.06.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <assert.h>

/**
 * ソートすべき部分配列の始点インデックスを探索
 * @param[in]	data	探索対象の配列
 * @param[in]	length	引数 @a data の要素数
 * @return	開始インデックス
 * @note	計算量は O(n)。ただし n は引数 @a length と等しい。
 */
size_t search_left(const int* data,
					size_t length)
{
	assert(data);
	assert(length);

	size_t k = length - 1;
	int min = data[k];
	size_t j;

	for (size_t i = 1; i < length; ++i) {
		j = length - i - 1;
		if (min >= data[j]) {
			min = data[j];
		}
		else {
			k = j;
		}
	}

	return k;
}

/**
 * ソートすべき部分配列の終点インデックスを探索
 * @param[in]	data	探索対象の配列
 * @param[in]	length	引数 @a data の要素数
 * @return	終点インデックス
 * @note	計算量は O(n)。ただし n は引数 @a length と等しい。
 */
size_t search_right(const int* data,
					size_t length)
{
	assert(data);
	assert(length);

	size_t k = 0;
	int max = data[k];

	for (size_t i = 1; i < length; ++i) {
		if (max <= data[i]) {
			max = data[i];
		}
		else {
			k = i;
		}
	}

	return k;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
	size_t length = sizeof(data) / sizeof(data[0]);
	size_t k;	// ソートすべき始点・終点インデックス

	k = search_left(data, length);
	printf("left: data[%lu] = %d\n", k, data[k]);

	k = search_right(data, length);
	printf("right: data[%lu] = %d\n", k, data[k]);

	return 0;
}
