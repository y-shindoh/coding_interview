/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.04.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>

int flip(int x)
{
	return 1 ^ x;
}

int sign(int x)
{
	return flip((x >> (sizeof(x) * 8 - 1)) & 1);
}

int myMax(int a, int b)
{
	int sa = sign(a);	// a >= 0 => 1, otherwise => 0
	int sb = sign(b);	// b >= 0 => 1, otherwise => 0

	/*
	  1. a >= 0, b >= 0
		- オーバーフローした => ない
		- a >= b => 1
		- b > a => 0
	  2. a >=0, b < 0 【不要】
		- オーバーフローした => 0
		- オーバーフローしていない => 1
	  3. a < 0, b >= 0 【不要】
		- オーバーフローした => 1
		- オーバーフローしていない => 0
	  4. a < 0, b < 0
		- オーバーフローした => ない
		- a <= b => 0
		- b < a => 1
	 */
	int sc = sign(a - b);

	int p = sa ^ sb;	// aとbが異なる符号を持つ場合、k = sign(a)
	int q = flip(p);	// aとbが同じ符号を持つ場合、k = sign(a-b)

	int k = p * sa + q * sc;
	int h = flip(k);

	return a * k + b * h;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int a = 5;
	int b = -6;
	int c = myMax(a, b);

	printf("%d vs. %d => %d\n", a, b, c);

	return 0;
}
