/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  n組の括弧の、括弧の対応が撮れた並び順すべてを表示するアルゴリズムを実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>

/**
 * 指定数の括弧の整合性のある全ての並びを出力
 * @param[out]	file	出力先
 * @param[in,out]	buffer	作業領域 (括弧の並ぶ文字列を書き出すのに十分な長さが必要)
 * @param[in]	number	括弧のペアの数
 * @param[in]	open	使用済み開き括弧の数
 * @param[in]	close	使用済み閉じ括弧の数
 * @note	計算量は O(2^number)。
 */
void
display_parens(FILE* file,
			   char* buffer,
			   size_t number,
			   size_t open = 0,
			   size_t close = 0)
{
	assert(file);
	assert(buffer);

	if (number <= open && number <= close) {
		buffer[open+close] = '\0';
		std::fprintf(file, "%s\n", buffer);
		return;
	}

	if (open < number) {
		buffer[open+close] = '(';
		display_parens(file, buffer, number, open+1, close);
	}

	if (close < open) {
		buffer[open+close] = ')';
		display_parens(file, buffer, number, open, close+1);
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[7];
	display_parens(stdout, buffer, 3);

	return 0;
}
