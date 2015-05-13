/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * 文字列を破壊的に反転
 * @param[in,out]	string	入力文字列・出力文字列 (空文字列は認めない)
 * @param[in]	to	空白文字を置換する文字列 (空文字列は認めない)
 * @note	引数 @a string で利用可能なメモリ領域は置換後の文字列長より広いと仮定する。
 */
void
replace_ws(char* string,
		   const char* to)
{
	const int sl = (int)std::strlen(string);
	const int tl = (int)std::strlen(to);
	int c(0);

	assert(0 < sl);
	assert(0 < tl);

	for (int i(0); i < sl; ++i) {
		if (string[i] != ' ') continue;
		++c;
	}

	int j = sl + c * (tl - 1) - 1;
	string[j+1] = '\0';

	for (int i(sl - 1); 0 <= i && 0 <= j; --i) {
		if (string[i] != ' ') {
			string[j] = string[i];
			--j;
		}
		else {
			for (int k(tl-1); 0 <= k; --k) {
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

	std::printf("BEFORE:\t'%s'\n", buffer);
	replace_ws(buffer, "%20");
	std::printf("AFTER:\t'%s'\n", buffer);

	return 0;
}
