/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.05.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/** 扱う色の種類 */
#define	COLOR	4

/**
 * マスター・マインド・ゲームのヒットおよびブローの算出
 * @param[in]	input	回答
 * @param[in]	answer	正解
 * @param	buffer	作業領域
 * @param[in]	length	配列 @a input, @a answer の長さ
 * @note	計算量は O(n)。ただし n は引数 @a length に等しい。
 * @note	算出結果は標準出力に書き出す。
 */
void check(const size_t* input,
		   const size_t* answer,
		   size_t buffer[COLOR],
		   size_t length)
{
	assert(input);
	assert(answer);
	assert(buffer);
	assert(length);

	memset((void*)buffer, 0, sizeof(size_t) * COLOR);
	size_t hit = 0;
	size_t blow = 0;
	size_t k;

	for (size_t i = 0; i < length; ++i) {
		k = answer[i];
		if (input[i] == k) {
			++hit;
		}
		else {
			buffer[k]++;
		}
	}

	for (size_t i = 0; i < length; ++i) {
		k = input[i];
		if (k == answer[i]) continue;
		if (!buffer[k]) continue;
		++blow;
		buffer[k]--;
	}

	/* 面倒くさいので標準出力に書き出す */
	printf("hit:\t%lu\n", hit);
	printf("blow:\t%lu\n", blow);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t input[] = { 0, 3, 3, 1 };
	size_t answer[] = { 0, 3, 1, 3 };
	size_t buffer[COLOR];

	check(input, answer, buffer, 4);

	return 0;
}
