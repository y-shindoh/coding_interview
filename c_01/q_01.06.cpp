/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  NxNの行列に描かれた、1つのピクセルが4バイト四方の画像があります。
  その画像を90度回転させるメソッドを書いてください。
  あなたはこれを追加の領域なしでできますか?
 */

#include <cstdio>
#include <cassert>

#define	WIDTH	((size_t)4)

typedef int Pixel;	///< 1ピクセルを表現する型

/**
 * 正方行列を表示 (動作確認用)
 * @param[in]	matrix	行列
 */
template<size_t N>
void
print_matrix(const Pixel matrix[N][N])
{
	assert(matrix);

	for (size_t i(0); i < N; ++i) {
		for (size_t j(0); j < N; ++j) {
			if (0 < j) std::printf(" ");
			std::printf("%02d", matrix[i][j]);
		}
		std::printf("\n");
	}
}

/**
 * 正方行列を時計方向に90度回転
 * @param[in,out]	matrix	正方行列
 * @note	計算量は O(n^2)。ただし n は引数 @a matrix の高さ・幅。
 * @note	行列内の要素の入れ替えは図示しないと分かりにくいので注意。
 */
template<size_t N>
void
rotate_matrix(Pixel matrix[N][N])
{
	assert(matrix);

	Pixel p;

	for (size_t i(0); i < N / 2; ++i) {
		for (size_t j(0); j < N / 2; ++j) {
			p = matrix[i][j];
			matrix[i][j] = matrix[N-j-1][i];
			matrix[N-j-1][i] = matrix[N-i-1][N-j-1];
			matrix[N-i-1][N-j-1] = matrix[j][N-i-1];
			matrix[j][N-i-1] = p;
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int matrix[WIDTH][WIDTH] = {{1, 2, 3, 4},
								{5, 6, 7, 8},
								{9, 10, 11, 12},
								{13, 14, 15, 16}};

	std::printf(">>>> before\n");
	print_matrix<WIDTH>(matrix);

	rotate_matrix<WIDTH>(matrix);

	std::printf(">>>> after\n");
	print_matrix<WIDTH>(matrix);

	return 0;
}
