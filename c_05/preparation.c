/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	preparation.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第5章の準備
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>

typedef unsigned int TYPE;

void
print_bits(TYPE bits)
{
	TYPE h, k;
	for (size_t i = 0; i < sizeof(bits); ++i) {
		if (0 < i) printf(" ");
		h = sizeof(bits) - i - 1;	// for little endian
		for (size_t j = 0; j < 8; ++j) {
			k = 8 - j - 1;
			if (bits & ((TYPE)1 << (h * 8 + k))) printf("1");
			else printf("0");
		}
	}
	printf(" [0x%lX]\n", (size_t)bits);
}

TYPE
get_bit(TYPE bits,
		size_t i)
{
	return bits & ((TYPE)1 << i);
}

TYPE
set_bit(TYPE bits,
		size_t i)
{
	return bits | ((TYPE)1 << i);
}

TYPE
clear_bit(TYPE bits,
		  size_t i)
{
	return bits & ~((TYPE)1 << i);
}

TYPE
clear_high_bits(TYPE bits,
				size_t i)
{
	return bits & (((TYPE)1 << i) - 1);
}

TYPE
clear_low_bits(TYPE bits,
			   size_t i)
{
	return bits & ~(((TYPE)1 << (i+1)) - 1);
}

/**
 * 動作確認用コマンド
 */
int main(void)
{
	TYPE bits = 0xC840;
	TYPE value;

	print_bits(bits);

	value = get_bit(bits, 11);
	print_bits(value);

	value = set_bit(bits, 4);
	print_bits(value);

	value = clear_bit(bits, 14);
	print_bits(value);

	value = clear_high_bits(bits, 15);
	print_bits(value);

	value = clear_low_bits(bits, 6);
	print_bits(value);

	return 0;
}
