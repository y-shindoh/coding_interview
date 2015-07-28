/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_18.02.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題18.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

_Bool flag = false;	///< ランダム処理の初期化

/**
 * 0以上指定値未満の整数をランダムに生成
 * @param[in]	l	指定値
 * @return	ランダムに生成された整数
 */
size_t MyRand(size_t l)
{
	if (!flag) srand((unsigned) time(NULL));

	return (size_t)rand() % l;
}

/**
 * 配列を確率的な偏りなく完全にシャッフル
 * @param[in,out]	data	配列
 * @param[in]	length	配列 @a data の要素数
 */
void shuffle(int data[],
			 size_t length)
{
	size_t j;
	int t;
	for (size_t i = 0; i < length; ++i) {
		j = MyRand(length - i) + i;	// 完全な等確率と仮定
		t = data[i];
		data[i] = data[j];
		data[j] = t;
	}
}

/**
 * 配列を標準出力に書き出し
 * @param[in]	data	配列
 * @param[in]	length	配列 @a data の要素数
 */
void print(const int data[],
		   size_t length)
{
	for (size_t i = 0; i < length; ++i) {
		if (0 < i) printf(" ");
		printf("[%lu]%d", i, data[i]);
	}
	printf("\n");
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	const size_t l = sizeof(data) / sizeof(data[0]);

	print(data, l);
	shuffle(data, l);
	print(data, l);

	return 0;
}
