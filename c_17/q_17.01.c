/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.01.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>

/**
 * 動作確認用コマンド
 */
int main()
{
	int a = 10;
	int b = -5;

	printf("[ORIGINAL]\n");
	printf("a = %d\n", a);
	printf("b = %d\n", b);

	a = a - b;	// 差分
	b += a;		// b = b + (a - b) = a
	a = b - a;	// a = a - (a - b) = b

	printf("[1]\n");
	printf("a = %d\n", a);
	printf("b = %d\n", b);

	a = 10;
	b = -5;

	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	printf("[2]\n");
	printf("a = %d\n", a);
	printf("b = %d\n", b);

	printf("a ^ a = %d\n", a ^ a);
	printf("a ^ b = %d\n", a ^ b);

	float c = 10;
	float d = -5;

	printf("[ORIGINAL]\n");
	printf("c = %f\n", c);
	printf("d = %f\n", d);

	c = c - d;	// 差分
	d += c;
	c = d - c;

	printf("[1]\n");
	printf("c = %f\n", c);
	printf("d = %f\n", d);

	return 0;
}
