/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.4の回答
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
	unsigned int x(0xF0F0F0F0);
	unsigned int y(0x08000000);

	// 1のビットのうち最下位をクリア
	print_bits<unsigned int>(stdout, x);
	print_bits<unsigned int>(stdout, x - 1);
	print_bits<unsigned int>(stdout, x & (x - 1));

	// 1のビットが1つしかないと0になる
	print_bits<unsigned int>(stdout, y);
	print_bits<unsigned int>(stdout, y - 1);
	print_bits<unsigned int>(stdout, y & (y - 1));

	return 0;
}
