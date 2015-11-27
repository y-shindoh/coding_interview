/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  最大32ビットの整数NとM、ビットの位置を指す値iとjが与えられています。
  このとき、Nのjビット目からiビット目にMを挿入するメソッドを書いてください。
  ただし、jとiの幅はMのビット数と一致していると仮定してかまいません。
  つまり、M=10011であればjとiの幅は5と仮定してかまいません。
  j=3, i=2のような、Mの幅と合わないような場合は考えなくてもかまわないということです。
 */

#include <cstddef>
#include <cstdio>
#include "bits_operation.hpp"

/**
 * 整数をあるビットからあるビットまで他の整数のビットで置換
 * @param[in]	base	置換元の整数
 * @param[in]	add	置換先の整数
 * @param[in]	i	置換開始ビットのインデックス (0始まり)
 * @param[in]	j	置換終了ビットのインデックス (0始まり)
 * @return	置換後の整数
 */
unsigned int
replace_bits(unsigned int base,
			 unsigned int add,
			 size_t i,
			 size_t j)
{
	base &= ~(~(size_t)0 << i) | (~(size_t)0 << (j + 1));
	return base | ((add << i) & ~(~(size_t)0 << (j + 1)));	// 最後のマスクは不要
}

/**
 * 動作確認用コマンド
 */
int main()
{
	unsigned int base(0xFF884433);
	unsigned int add(0x19);

	size_t i (8);
	size_t j (12);

	unsigned int value = replace_bits(base, add, i, j);

	print_bits<unsigned int>(stdout, base, "N:");
	print_bits<unsigned int>(stdout, add, "M:");
	std::printf("i = %lu, j = %lu\n", i, j);
	print_bits<unsigned int>(stdout, value, "=>");

	return 0;
}
