/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_07.01.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第7章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/**
 * 素数かどうか確認
 * @param[in]	number	素数候補
 * @return	true: 素数, false: 素数でない
 * @note	引数 @a number に2未満の数値は入れないこと。
 */
_Bool
is_prime(size_t number)
{
	assert(1 < number);

	if (2 < number && number % 2 == 0) return false;

	for (size_t i = 3; i < number; i +=2) {
		if (number % i) continue;
		return false;
	}

	return true;
}

/**
 * 動作確認用関数
 */
void
print_number(size_t number)
{
	printf("%lu: %s\n", number, is_prime(number) ? "prime" : "not prime");
}

/**
 * 動作確認用コマンド
 */
int main()
{
	print_number(2);
	print_number(3);
	print_number(4);
	print_number(199);

	return 0;
}
