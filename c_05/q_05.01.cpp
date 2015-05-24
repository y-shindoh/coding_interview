/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include "bits_operation.hpp"

unsigned int
replace_bits(unsigned int base,
			 unsigned int add,
			 size_t i,
			 size_t j)
{
	base = clear_low_bits<unsigned int>(base, i) | clear_high_bits<unsigned int>(base, j);
	add = clear_high_bits<unsigned int>(add, i - j + 1);
	return base | (add << j);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	unsigned int base(0xFF884433);
	unsigned int add(0x00000CC0);
	unsigned int value = replace_bits(base, add, 23, 8);

	print_bits<unsigned int>(stdout, base);
	print_bits<unsigned int>(stdout, add);
	print_bits<unsigned int>(stdout, value);

	return 0;
}
