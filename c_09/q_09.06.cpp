/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>

/**
 * 整合性のある括弧の組み合わせ全てを出力
 * @param	buffer	作業領域 (引数 @a pairs の2倍+1の長さが必要)
 * @param[in]	pairs	括弧のペアの個数
 * @param[in]	left	使用済み開き括弧の総数
 * @param[in]	right	使用済み閉じ括弧の総数
 * @param[in]	l_char	開き括弧の文字
 * @param[in]	r_char	閉じ括弧の文字
 */
void
print_parens(char* buffer,
			 size_t pairs,
			 size_t left = 0,
			 size_t right = 0,
			 char l_char = '(',
			 char r_char = ')')
{
	assert(buffer);

	size_t i = left + right;

	if (i == pairs * 2) {
		buffer[i] = '\0';
		std::printf("%s\n", buffer);
		return;
	}

	if (left < pairs) {
		buffer[i] = l_char;
		print_parens(buffer, pairs, left + 1, right);
	}

	if (right < pairs && right < left) {
		buffer[i] = r_char;
		print_parens(buffer, pairs, left, right + 1);
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[7];
	print_parens(buffer, 3);

	return 0;
}
