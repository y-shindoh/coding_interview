/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  偶数ビットと奇数ビットをできるだけ少ない操作で入れ替えるプログラムを書いてください
  (たとえば、0ビット目と1ビット目、2ビット目と3ビット目を入れ替えます)。
 */

#include <cstddef>
#include <cstdio>
#include "bits_operation.hpp"

/**
 * 偶数ビットと奇数ビットを交換
 * @param[in]	value	交換対象の整数
 * @return	交換後の整数
 */
template<typename TYPE>
TYPE
change_adjoining_bits(TYPE value)
{
	return (((TYPE)0xAAAAAAAAAAAAAAAA & value) >> 1) | (((TYPE)0x5555555555555555 & value) << 1);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	unsigned int x(0xCF15DE20);

	print_bits<unsigned int>(stdout, x);
	print_bits<unsigned int>(stdout, change_adjoining_bits<unsigned int>(x));

	return 0;
}
