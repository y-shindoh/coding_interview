/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.08.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * 2つの文字列が回転の関係にあるかどうかを確認
 * @param[in]	string_1	文字列その1
 * @param[in]	string_2	文字列その
 * @param	buffer	作業領域。 @a first の2倍以上の長さが必要。
 * @return	true: 回転の関係, false: 回転の関係でない
 * @note	最悪計算量は @a std::strstr<f> に準じる。
 */
_Bool
check_rotated(const char* string_1,
			  const char* string_2,
			  char* buffer)
{
	const size_t l1 = strlen(string_1);
	const size_t l2 = strlen(string_2);

	if (l1 != l2) return false;

	strcpy(buffer, string_1);
	strcat(buffer, string_2);

	// 問題文にある「is_substring<f>」を「strstr<f>」で代替。
	// (see http://www.c-tipsref.com/reference/string/strstr.html )
	return strstr(buffer, string_2) != NULL;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const char strings[][16] = {"AAACCCabc",
								"ACCCabcAA",
								"AACCCabcAA"};
	const size_t l = sizeof(strings) / sizeof(strings[0]);
	char buffer[16*2];
	size_t i, j;

	for (i = 0; i < l; ++i) {
		for (j = 0; j < l; ++j) {
			if (i == j) continue;
			if (check_rotated(strings[i], strings[j], buffer)) {
				printf("ROTATED:     ");
			}
			else {
				printf("NOT ROTATED: ");
			}
			printf("'%s' => '%s'\n", strings[i], strings[j]);
		}
	}

	return 0;
}
