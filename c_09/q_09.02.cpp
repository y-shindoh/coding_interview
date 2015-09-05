/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  XY平面上の左上にロボットが座っています。
  ロボットは右と下の2つの方向にしか進むことができません。
  (0, 0) から (X, Y) まで移動するには何通りの進み方がありますか?

  発展問題
  ロボットが通ることのできない「立ち入り禁止」の地点があるとした場合、
  左上の地点から右下の地点まで移動する道順を見つけるアルゴリズムを設計してください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <set>

/**
 * 指定の大きさの平面における原点から対角への移動方法の総数を算出
 * @param[in]	width	平面の幅
 * @param[in]	hight	平面の高さ
 * @param[in]	rules	移動禁止箇所
 * @note	計算量は O(width * hight)。
			ただし std::set::find<f> の計算量を O(1) とした場合に限る。
 * @note	メモリ占有量は O(width)。
 * @note	テンプレートの型 @a TYPE は符号なし整数を適用すること。
 */
template<typename TYPE>
TYPE
count_route(size_t width,
			size_t hight,
			const std::vector< std::set<size_t> >& rules)
{
	assert(0 < width);
	assert(0 < hight);

	std::vector<TYPE> buffer[2];
	size_t h, k;

	// 算出領域の初期化
	for (size_t i(0); i < 2; ++i) {
		buffer[i].resize(width);
		std::memset((void*)&buffer[i][0], 0, sizeof(TYPE) * width);
	}
	buffer[1][0] = (TYPE)1;

	// 総数の算出
	for (size_t i(0); i < hight; ++i) {
		h = (i + 1) % 2;
		k = i % 2;
		for (size_t j(0); j < width; ++j) {
			buffer[k][j] += buffer[h][j];
			if (0 < j) buffer[k][j] += buffer[k][j-1];
			if (rules[i].find(j) != rules[i].end()) buffer[k][j] = 0;
		}
		std::memset((void*)&buffer[h][0], 0, sizeof(TYPE) * width);
	}

	h = (hight - 1) % 2;

	return buffer[h][width-1];
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t n;
	std::vector< std::set<size_t> > rules;

	rules.resize(5);
	rules[1].insert(1);	// 立入禁止

	for (size_t i(1); i < 5; ++i) {
		n = count_route<size_t>(i, i, rules);
		std::printf("%lu => %lu\n", i, n);
	}

	return 0;
}
