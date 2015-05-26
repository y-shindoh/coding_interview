/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_07.02.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第7章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * エラトステネスのふるい
 * @param[in,out]	numbers	入力数値列 (2, 3, 4, 5, 6, 7, ...)
 * @param[in]	length	引数 @a numbers の長さ
 * @note	引数 @a numbers は
			2, 3, 5, 7, 9, ... のように2を超える偶数を除いて良い。
 * @note	素数でなかった数値は0に置換される。
 */
void
prime_number_filter(size_t* numbers,
					size_t length)
{
	size_t d;
	for (size_t i = 0; i < length; ++i) {
		if (!numbers[i]) continue;
		d = numbers[i];
		for (size_t j = i + 1; j < length; ++j) {
			if (!numbers[j]) continue;
			if (numbers[j] % numbers[i]) continue;
			numbers[j] = 0;
		}
	}
}

void
print_array(size_t* numbers,
			size_t length)
{
	_Bool flag = false;
	for (size_t i = 0; i < length; ++i) {
		if (!numbers[i]) continue;
		if (flag) printf(", ");
		printf("%lu", numbers[i]);
		flag = true;
	}
	printf("\n");
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t a[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11 ,12, 13};
	size_t l = sizeof(a) / sizeof(a[0]);

	print_array(a, l);
	prime_number_filter(a, l);
	print_array(a, l);

	return 0;
}
