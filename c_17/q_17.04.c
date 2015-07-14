/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.04.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>

/**
 * 整数の符号情報を抽出
 * @param[in]	x	抽出対象の整数
 * @return	1: 引数 @a x は0以上, 0: 引数 @a x は負の数
 */
int sign(int x)
{
	return 1 ^ ((x >> (sizeof(x) * 8 - 1)) & 1);
}

/**
 * 2つの整数から大きなものを選出
 * @param[in]	a	整数 (その1)
 * @param[in]	b	整数 (その2)
 * @reurn	引数 @a a と @a b のうち大きい方
 * @note	条件分岐および比較演算子を使わないという制約がある。
 */
int myMax(int a, int b)
{
	int sa = sign(a);	// a >= 0 ⇒ sa = 1, a < 0 ⇒ sa = 0
	int sb = sign(b);	// b >= 0 ⇒ sb = 1, b < 0 ⇒ sb = 0

	/*
	  1. a >= 0, b >= 0
		- a >= b ⇒ sc = 1
		- b > a ⇒ sc = 0
	  2. a < 0, b < 0
		- a <= b ⇒ sc = 0
		- b < a ⇒ sc = 1
	  3. a >=0, b < 0 【不要】
	  4. a < 0, b >= 0 【不要】

	  ※ 3, 4の場合のみ a - b にオーバーフローの可能性がある。
	 */
	int sc = sign(a - b);

	/*
	  1. a と b が異なる符号を持つ場合 ⇒ p = 1, q = 0
	  2. a と b が同じ符号を持つ場合 ⇒ p = 0, q = 1
	 */
	int p = sa ^ sb;
	int q = 1 ^ p;

	/*
	  1. a と b が異なる符号を持つ場合 k = sa を考える。
		- a >= 0 ⇒ k = 1, h = 0
		- b >= 0 ⇒ k = 0, h = 1
	  2. a と b が同じ符号を持つ場合 k = sc を考える。
		- a > b ⇒ k = 1, h = 0
		- a < b ⇒ k = 0, h = 1
		- a == b ⇒ k = 1, h = 0 または k = 0, h = 1
	 */
	int k = p * sa + q * sc;
	int h = 1 ^ k;

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
