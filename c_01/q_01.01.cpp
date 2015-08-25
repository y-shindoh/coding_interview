/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ある文字列が、すべてユニークである (重複する文字がない) かどうかを
  判定するアルゴリズムを実装してください。
  また、それを実装するのに新たなデータ構造が使えない場合、
  どのようにすればよいですか?
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

#define	BUFFER_LENGTH	((size_t)0x100)

/**
 * 文字列中に同一文字があるか否かを確認
 * @param[out]	buffer	作業領域
 * @param[in]	string	確認対象の文字列
 * @return	true: 同一文字があった, false: なかった
 * @note	処理対象はUS-ASCIIに限定する。大文字小文字を区別する。
 * @note	最悪計算量は O(m)。ただし m は BUFFER_LENGTH か入力文字列の長さの大きい方。
 */
bool
check_duplicated_letter(bool buffer[BUFFER_LENGTH],
						const char* string)
{
	assert(buffer);
	assert(string);

	std::memset((void*)buffer, 0, sizeof(bool) * BUFFER_LENGTH);
	size_t i;

	while (*string) {
		i = (size_t)*string++;
		if (buffer[i]) return true;
		buffer[i] = true;
	}

	return false;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	bool buffer[BUFFER_LENGTH];
	const char sample[][1024] = {"AbCdBC.", "AbCdBc."};

	for (size_t i(0); i < sizeof(sample)/sizeof(sample[0]); ++i) {
		if (check_duplicated_letter(buffer, sample[i])) {
			std::printf("FOUND     ");
		}
		else {
			std::printf("NOT FOUND ");
		}
		std::printf("'%s'\n", sample[i]);
	}

	return 0;
}
