/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  正の整数が与えられたとき、2時表現したときの1の個数が同じ整数の中で、
  1つ後の数と前の数を求めてください。
 */

#include <cstddef>
#include <cstdio>
#include "bits_operation.hpp"

/**
 * ビット1の数が同じで次に大きい整数を算出
 * @param[in]	value	正の整数
 * @return	引数 @a value に対しビット1の数が同じで次に大きい整数
 * @note	書籍にはより良い (が分かりにくい) 解が掲載されている。
 * @note	little endian用の実装であることに注意。
 */
template<typename TYPE>
TYPE
find_next(TYPE value)
{
	size_t o(0), i(0);

	// ビット"01"の並びを探索
	while (!(value & ((TYPE)1 << o))) ++o;	// 先頭のビット0
	while (value & ((TYPE)1 << (o + i))) ++i;	// 先頭に準ずるビット1

	assert(o + i < 32);

	value |= (TYPE)1 << (o + i);
	--i, ++o;	// 上記で移動したビット1の分を調整 (oは理解のため)
	value &= (~(TYPE)0 << (o + i));
	value |= ((TYPE)1 << i) - (TYPE)1;

	return value;
}

/**
 * ビット1の数が同じで次に小さい整数を算出
 * @param[in]	value	正の整数
 * @return	引数 @a value に対しビット1の数が同じで次に小さい整数
 * @note	書籍にはより良い (が分かりにくい) 解が掲載されている。
 * @note	little endian用の実装であることに注意。
 */
template<typename TYPE>
TYPE
find_previous(TYPE value)
{
	assert(0 < value);
	assert(value < ~(TYPE)0);

	size_t i(0), o(0);

	// ビット"10"の並びを探索
	while (value & ((TYPE)1 << i)) ++i;	// 先頭のビット1
	while (!((value) & ((TYPE)1 << (i + o)))) ++o;	// 先頭に準ずるビット0

	assert(i + o < 32);

	value &= ~((TYPE)1 << (i + o));
	--o, ++i;	// 上記で移動したビット0の分を調整 (iは理解のため)
	value |= ((TYPE)1 << (i + o)) - (TYPE)1;
	value &= ~(TYPE)0 << o;

	return value;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	unsigned int x(0xFF884607);
	unsigned int y;

	print_bits<unsigned int>(stdout, x, "[original]");

	y = find_next<unsigned int>(x);
	print_bits<unsigned int>(stdout, y, "[next]    ");

	y = find_previous<unsigned int>(x);
	print_bits<unsigned int>(stdout, y, "[previous]");

	return 0;
}
