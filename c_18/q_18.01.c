/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_18.01.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題18.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>

/**
 * 2つの正の整数を加算 (演算子「+」「-」「*」「/」「%」は使わない)
 * @param[in]	x	正の整数
 * @param[in]	y	正の整数
 * @return	2つの整数の和
 */
size_t MyAdd(size_t x, size_t y)
{
	// 一方の整数が0ならもう一方の整数が和
	if (y == 0) return x;
	if (x == 0) return y;

	// 「x ^ y」は繰り上がりを無視した和の値。
	// 「(x & y) << 1」は繰り上がりだけを抽出した和の値。
	// 「(x ^ y) + ((x & y) << 1)」が求めたい値
	return MyAdd(x ^ y, (x & y) << 1);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t x = 759;
	size_t y = 674;

	printf("x = 0x%05lX\ny = 0x%05lX\n", x, y);
	printf("x + y = 0x%05lX\n", x + y);
	printf("x + y = 0x%05lX\n", MyAdd(x, y));

	return 0;
}
