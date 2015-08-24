/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  CかC++で、void reverse(char* str) という
  '\0' 端末の文字列を逆に並び変える関数を実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * 文字列を破壊的に反転
 * @param[in,out]	s	入力文字列・出力文字列 (s/str/s/g)
 */
void
reverse(char* s)
{
	assert(s);

	int i(0);
	int j = (int)std::strlen(s) - 1;	// 符号あり整数の方が安全
	char c;

	while (i < j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		++i, --j;
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[] = "01234 56789.";

	std::printf("BEFORE:\t'%s'\n", buffer);
	reverse(buffer);
	std::printf("AFTER:\t'%s'\n", buffer);

	return 0;
}
