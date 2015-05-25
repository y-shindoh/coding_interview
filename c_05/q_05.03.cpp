/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include "bits_operation.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	unsigned int x(0xFF884433);
	unsigned int y = next_same_bit_counts<unsigned int>(x);		// 回答
	unsigned int z = previous_same_bit_counts<unsigned int>(x);	// 回答

	std::printf("%u:\t", x);
	print_bits<unsigned int>(stdout, x);
	std::printf("%u:\t", y);
	print_bits<unsigned int>(stdout, y);
	std::printf("%u:\t", z);
	print_bits<unsigned int>(stdout, z);

	return 0;
}
