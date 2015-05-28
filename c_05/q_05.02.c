/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.02.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define	N	32
#define	STEP	0.5

/**
 * 浮動小数点の数値をバイナリ表現した文字列に変換
 * @param[out]	buffer	文字列の出力先 (事前に0で埋めておくこと)
 * @param[in]	number	浮動小数点の数値 (0.0より大きく、1.0より小さい)
 * @return	true: 変換成功, false: 変換失敗
 * @note	長さ @a N ビットまでで表現できなかった場合、変換失敗する。
 * @note	変換例: 0.625 => (1/2)^1 * 1 + (1/2)^2 * 0 + (1/2)^3 * 1 => 101
 */
_Bool
make_binary_string(char* buffer,
				   double number)
{
	assert(buffer);

	if (number <= 0.0) return false;
	if (1.0 <= number) return false;

	size_t i = 0;

	while (0.0 < number) {
		if (N <= i) return false;
		number /= STEP;
		if (1.0 <= number) {
			buffer[i] = '1';
			number -= 1.0;
		}
		else {
			buffer[i] = '0';
		}
		++i;
	}

	return true;
}

/**
 * 浮動小数点をバイナリ表現した文字列から数値に変換
 * @param[in]	buffer	文字列の出力先 (終端は0)
 * @return	浮動小数点の数値
 */
double
make_real_number(const char* buffer)
{
	assert(buffer);

	size_t i = 0;
	double value = 0.0;
	double base = 1.0;

	for (size_t i = 0; buffer[i]; ++i) {
		base *= STEP;
		if (buffer[i] != '1') continue;
		value += base;
	}

	return value;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[N+1];
	double number = 0.6875;

	memset((void*)buffer, 0, sizeof(buffer));

	if (make_binary_string(buffer, number)) {
		number = make_real_number(buffer);
		printf("%lf => .%s\n", number, buffer);
	}
	else {
		printf("Can not convert from %lf\n", number);
	}

	return 0;
}
