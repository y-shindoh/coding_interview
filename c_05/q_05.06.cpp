/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include "bits_operation.hpp"

/**
 * 2n と 2n+1 の位置のビットを交換
 */
unsigned int
change_adjoining_bits(unsigned int bits)
{
	return (((unsigned int)0xAAAAAAAA & bits) >> 1) | (((unsigned int)0x55555555 & bits) << 1);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	unsigned int x(0xCF15DE20);

	print_bits<unsigned int>(stdout, x);
	print_bits<unsigned int>(stdout, change_adjoining_bits(x));

	return 0;
}
