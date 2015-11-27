/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  0から1までの実数値がdouble型として与えられるとき、それを2進数表記で出力してください。
  32文字以内で正確に表現できない場合は "ERROR" と出力してください。
 */

#include <cstddef>
#include <cstdio>

/**
 * 0以上1未満の実数を2進数表現に変換 (0.25 => "01", 0.125 => "001")
 * @param[in]	value	0以上1未満の実数
 * @param[out]	buffer	変換結果の格納先
 * @param[in]	l	変換結果の格納文字数
 * @note	引数 @a buffer は引数 @a l の長さの文字列を扱える十分な広さの領域とすること。
 */
bool
convert_to_binary(double value,
				  char* buffer,
				  size_t l = 32)
{
	double divider = 1.0;

	for (size_t i(0); i < l; ++i) {
		divider /= 2.0;
		if (divider <= value) {
			value -= divider;
			buffer[i] = '1';
		}
		else {
			buffer[i] = '0';
		}
	}
	buffer[l] = '\0';

	return value == 0.0;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[33];
	double values[] = {0.625, 0.0001, 0.0322265625};

	for (size_t i(0); i < sizeof(values) / sizeof(values[0]); ++i) {
		if (convert_to_binary(values[i], buffer)) {
			std::printf("%G => '%s'\n", values[i], buffer);
		}
		else {
			std::printf("%G => ERROR (%s)\n", values[i], buffer);
		}
	}

	return 0;
}
