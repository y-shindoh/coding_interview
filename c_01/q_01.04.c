/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.04.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * 文字列の空白文字を置換
 * @param[in,out]	string	入力文字列・出力文字列 (空文字列は認めない)
 * @param[in]	to	空白文字を置換する文字列 (空文字列は認めない)
 * @note	引数 @a string で利用可能なメモリ領域は置換後の文字列長より広いと仮定する。
 */
void
replace_ws(char* string,
		   const char* to)
{
	const int sl = (int)strlen(string);
	const int tl = (int)strlen(to);

	assert(0 < sl);
	assert(0 < tl);

	int c = 0;
	for (int i = 0; i < sl; ++i) {
		if (string[i] != ' ') continue;
		++c;
	}

	int j = sl + c * (tl - 1) - 1;
	string[j+1] = '\0';

	for (int i = sl - 1; 0 <= i; --i) {
		if (string[i] != ' ') {
			string[j] = string[i];
			--j;
		}
		else {
			for (int k = tl - 1; 0 <= k; --k) {
				string[j] = to[k];
				--j;
			}
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[1024] = "012 34 5 6789.";

	printf("BEFORE:\t'%s'\n", buffer);
	replace_ws(buffer, "%20");
	printf("AFTER:\t'%s'\n", buffer);

	return 0;
}