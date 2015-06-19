/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
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
 * @param[in]	h	探索終了インデックス (行)
 * @param[in]	w	探索終了インデックス (列)
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
	assert(i <= h);
	assert(j <= w);
	assert(h <= N);
	assert(w <= N);

	std::printf("<%lu:%lu => %lu:%lu>\n", i, j, h, w);

	const size_t g(i);
	const size_t k(j);

	size_t x;
	size_t s(0);
	size_t e(h - i);
	if (w - j < e) e = w - j;

	// 対角線上を二分探索
	while (s < e) {
		x = (s + e) / 2;
		if (value < matrix[i+x][j+x]) {
			if (e == x) break;
			e = x;
		}
		else if (value > matrix[i+x][j+x]) {
			if (s == x) break;
			s = x;
		}
		else {
			return std::pair<size_t, size_t>(i+x, j+x);
		}
	}

	i += e;
	j += e;

	std::pair<size_t, size_t> result(N, N);

	// 右上を探索
	if (k < j && j < w) {
		result = find_in_matrix<TYPE, N>(matrix, value, g, j, i, w);
		if (result.first < N) return result;
	}

	// 左下を探索
	if (g < i && i < h) {
		result = find_in_matrix<TYPE, N>(matrix, value, i, k, h, j);
		if (result.first < N) return result;
	}

	return result;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int matrix[4][4] = {{15, 20, 70, 85},
						{20, 35, 80, 95},
						{30, 55, 95, 105},
						{40, 80, 100, 120}};
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
