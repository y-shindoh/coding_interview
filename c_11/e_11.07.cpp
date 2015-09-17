/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cassert>
#include "utility.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	const size_t l = sizeof(data) / sizeof(data[0]);
	size_t i;

	print_array<int>(data, l, "DATA");

	for (int key(3); key < 9; ++key) {
		i = BinarySearch<int>(data, l, key);	// 二分探索
		if (i != INVALID_INDEX) {
			std::printf("data[%lu] = %d\n", i, key);
		}
		else {
			std::printf("data[-] = %d\n", key);
		}
	}

	return 0;
}
