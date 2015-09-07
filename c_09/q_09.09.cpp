/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.09.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.9の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  8x8のチェス盤上に、
  縦・横・斜めの直線上に2つ以上並ばないように8つのクイーンを配置する
  すべての場合を出力するアルゴリズムを書いてください
  (「斜め」はチェス盤の対角線という意味ではなく、すべての斜めの線のことです)。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>

/**
 * N-queenの探索器 (補助メソッド)
 * @param[in]	w	チェス盤の幅・高さ
 * @param[in]	d	すでにクイーンを置いてある行数
 * @param[in]	v	クイーンを置けない場所 (水平方向)
 * @param[in]	l	クイーンを置けない場所 (左斜め上方向)
 * @param[in]	r	クイーンを置けない場所 (右斜め上方向)
 * @return	各時点でのパターン (バリエーション解) の総数
 * @note	引数の「クイーンを置けない場所」は、
			メソッド呼び出し時の状況を表現すれば良い。
*/
template<typename TYPE>
TYPE
nqueen(TYPE w,
	   TYPE d,
	   TYPE v,
	   TYPE l,
	   TYPE r)
{
	if (w <= d) return (TYPE)1;	// 解を1つ発見

	// クイーンの置けない場所を調整
	l >>= 1;
	r <<= 1;

	TYPE t = (~(v | (l | r))) & ~(~((TYPE)0) << w);
	TYPE i;
	TYPE n(0);

	while (t != 0) {
		i = (t ^ (t & (t - (TYPE)1)));	// 置き場所を1つ抽出
		n += nqueen<TYPE>(w, d + (TYPE)1, v | i, l | i, r | i);
		t ^= i;
	}

	return n;
}

/**
 * N-queenの探索器
 * @param[in]	w	チェス盤の幅・高さ
 * @return	パターン (バリエーション解) の総数
 * @note	題意と異なるが、今回は盤の状態を出力しない実装とした。
 */
template<typename TYPE>
TYPE
nqueen(TYPE w)
{
	assert(w <= sizeof(TYPE) * 8);

	TYPE n(0);
	TYPE v;

	for (TYPE i(0); i < w / 2; ++i) {
		v = (TYPE)1 << i;
		n += nqueen<TYPE>(w, (TYPE)1, v, v, v);
	}

	n *= 2;	// 左右対称

	if (w % 2 != 0) {
		v = (TYPE)1 << (w / 2);
		n += nqueen<TYPE>(w, (TYPE)1, v, v, v);
	}

	return n;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t r;

	for (size_t n(1); n <= 10; ++n) {
		r = nqueen<size_t>(n);
		std::printf("%lu-queen: %lu\n", n, r);
	}

	return 0;
}
