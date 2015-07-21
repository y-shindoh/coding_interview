/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.08.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <assert.h>

/**
 * 部分列の最大合計値を算出
 * @param[in]	data	元の整数の配列
 * @param[in]	length	引数 @a data の要素数
 * @return	合計値
 * @note	空の部分列に対する合計値を @a 0 とする。
 * @note	計算量は O(n) になる。ただし n は元の配列の要素数。
 */
int search_maxsum(const int* data,
				  size_t length)
{
	int max = 0;
	int sum = 0;

	for (size_t i = 0; i < length; ++i) {
		if (0 <= sum + data[i]) {
			// 既存部分列を使った方が良い
			sum += data[i];
		}
		else {
			// 既存部分列を破棄した方が良い
			sum = 0;
		}
		if (max < sum) max = sum;
	}

	return max;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {2, 3, -8, -1, 2, 4, -2, 3};
	size_t l = sizeof(data) / sizeof(data[0]);

	int n = search_maxsum(data, l);

	for (size_t i = 0; i < l; ++i) {
		if (0 < i) printf(", ");
		printf("%d", data[i]);
	}
	printf("\n=> %d\n", n);

	return 0;
}
