/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_18.03.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題18.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

_Bool flag = false;	///< ランダム処理の初期化状態

/**
 * 0以上指定値未満の整数をランダムに生成
 * @param[in]	l	指定値
 * @return	ランダムに生成された整数
 * @note	完全な等確率で各数値が出力されると仮定する。
 */
size_t MyRand(size_t l)
{
	if (!flag) {
		flag = true;
		srand((unsigned)time(NULL));
		rand();	// 初算出の偏りの対処 (おまじないレベル)
	}

	return (size_t)((double)l * (double)rand() / ((double)RAND_MAX + 1.0));
}

/**
 * 指定個数の要素をランダムに選択し配列の先頭に移動
 * @param[in,out]	data	配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	times	移動させたい要素数
 */
void shuffle(int data[],
			 size_t length,
			 size_t times)
{
	if (length < times) times = length;

	size_t j;
	int t;

	for (size_t i = 0; i < times; ++i) {
		j = MyRand(length - i) + i;
		if (i == j) continue;
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
	shuffle(data, l, 5);
	print(data, 5);

	return 0;
}
