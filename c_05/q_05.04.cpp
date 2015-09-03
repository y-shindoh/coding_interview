/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/**
   問題:
   コード ((n & (n - 1)) == 0) について説明してください。
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
	unsigned int z(0x00000000);

	// 1のビットのうち最下位をクリア
	std::printf("<<x>>\n");
	print_bits<unsigned int>(stdout, x, "x =          ");
	print_bits<unsigned int>(stdout, x - 1u, "x - 1 =      ");
	print_bits<unsigned int>(stdout, x & (x - 1u), "x & (x - 1) =");

	// 1のビットが1つしかないと0になる
	std::printf("<<y>>\n");
	print_bits<unsigned int>(stdout, y, "y =          ");
	print_bits<unsigned int>(stdout, y - 1u, "y - 1 =      ");
	print_bits<unsigned int>(stdout, y & (y - 1u), "y & (y - 1) =");

	// 1のビットが1つもないと0になる
	std::printf("<<z>>\n");
	print_bits<unsigned int>(stdout, z, "z =          ");
	print_bits<unsigned int>(stdout, z - 1u, "z - 1 =      ");
	print_bits<unsigned int>(stdout, z & (z - 1u), "z & (z - 1) =");

	return 0;
}
