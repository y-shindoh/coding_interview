/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ある整数AからBに変換するのに必要なビット数を決定する関数を書いてください。

  例:
  入力: 31, 14
  出力: 2
 */

#include <cstddef>
#include <cstdio>
#include "bits_operation.hpp"

/**
 * 2つの整数を互いへ変換する際に反転させるビットの数を算出
 * @param[in]	a	整数 (その1)
 * @param[in]	b	整数 (その2)
 * @return	引数 @a a から引数 @a b へ変換する際に反転させるビットの数
 * @note	ビット1を数え上げる処理はあえて簡易版で実装した。
 */
template<typename TYPE>
size_t
count_replacing_bit(TYPE a,
					TYPE b)
{
	size_t k(0);

	for (TYPE i(a ^ b); i; i &= i - (TYPE)1) ++k;

	return k;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	unsigned int x(31);
	unsigned int y(14);

	print_bits<unsigned int>(stdout, x);
	print_bits<unsigned int>(stdout, y);

	print_bits<unsigned int>(stdout, x ^ y);
	std::printf("=> %lu\n", count_replacing_bit<unsigned int>(x, y));

	return 0;
}
