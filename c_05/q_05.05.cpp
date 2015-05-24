/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.5の回答
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
	unsigned int x(31);
	unsigned int y(14);

	print_bits<unsigned int>(stdout, x);
	print_bits<unsigned int>(stdout, y);

	print_bits<unsigned int>(stdout, x ^ y);
	std::printf("=> %lu\n", counts_bits<unsigned int>(x ^ y));

	return 0;
}
