/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  行と列がそれぞれソートされたMxNの行列があります。
  この行列からある要素を見つけるメソッドを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <utility>

/**
 * 行と列ともに昇順ソートされた正方行列から値を位置を探索
 * @param[in]	matrix	探索対象の正方行列
 * @param[in]	value	探索対象の値
 * @param[in]	i	探索開始インデックス (行)
 * @param[in]	j	探索開始インデックス (列)
 * @param[in]	h	探索終端インデックス (行, 1つ前のインデックスまで探索)
 * @param[in]	w	探索終端インデックス (列, 1つ前のインデックスまで探索)
 * @return	探索結果の行と列のインデックス (探索失敗時は @a N の組が返る)
 * @note	テンプレートの整数 @a N は正方行列の高さ・幅。
 * @note	最悪計算量は O(n log n) となる。
 */
template<typename TYPE, size_t N>
std::pair<size_t, size_t>
find_in_matrix(const TYPE matrix[N][N],
			   TYPE value,
			   size_t i = 0,
			   size_t j = 0,
			   size_t h = N,
			   size_t w = N)
{
	assert(matrix);
	assert(i < h);
	assert(j < w);
	assert(h <= N);
	assert(w <= N);

	size_t s(0);	// 小さい要素のインデックスの最大値 (初期値に注意)
	size_t e = h - i < w - j ? h - i : w - j;	// 探索幅
	size_t k;

	while (s < e) {
		k = (s + e) / 2;
		if (matrix[k+i][k+j] < value) {
			if (s == k) break;	// sとeが隣接
			s = k;
		}
		else if (matrix[k+i][k+j] > value) {
			e = k;
		}
		else {
			return std::pair<size_t, size_t>(k+i, k+j);
		}
	}

	////////////////////////////////////////////////////////////
	// メモ:
	// - 探索範囲の全ての要素が探索対象より大きい場合、
	//   e == 0 が成立する。
	// - 探索範囲の全ての要素が探索対象より小さい場合、
	//   j + e == w か i + e == h のいずれか or 両方が成立する。

	std::pair<size_t, size_t> result(N, N);

	if (s < e) {
		// 右上
		if (j + e < w) {
			result = find_in_matrix<TYPE, N>(matrix, value, i, j + e, i + e, w);
			if (result.first != N && result.second != N) return result;
		}

		// 左下
		if (i + e < h) {
			result = find_in_matrix<TYPE, N>(matrix, value, i + e, j, h, j + e);
			if (result.first != N && result.second != N) return result;
		}
	}

	return result;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int matrix[4][4] = {{15,  20,  70,  85},
						{20,  35,  80,  95},
						{30,  55,  95, 105},
						{40,  80, 100, 120}};
	int value(40);

	std::pair<size_t, size_t> result = find_in_matrix<int, 4>(matrix, value);

	if (result.first < 4) {
		std::printf("FOUND: matrix[%lu][%lu] = %d\n", result.first, result.second, value);
	}
	else {
		std::printf("NOT FOUND: %d\n", value);
	}

	return 0;
}
