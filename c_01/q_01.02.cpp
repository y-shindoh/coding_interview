/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>

/**
 * 文字列を破壊的に反転
 * @param[in,out]	str	入力文字列・出力文字列
 */
void
reverse(char* str)
{
	size_t j = std::strlen(str);
	if (!j--) return;

	char c;
	for (size_t i(0); i < j; ++i, --j) {
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[] = "01234 56789.";

	printf("BEFORE:\t'%s'\n", buffer);
	reverse(buffer);
	printf("AFTER:\t'%s'\n", buffer);

	return 0;
}
