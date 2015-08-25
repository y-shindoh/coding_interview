/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  MxNの行列について、要素が0であれば、
  その行と列をすべて0にするようなアルゴリズムを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * 行列を表示 (動作確認用)
 * @param[in]	matrix	行列
 */
template<size_t H, size_t W>
void
print_matrix(const int matrix[H][W])
{
	assert(matrix);

	for (size_t i(0); i < H; ++i) {
		for (size_t j(0); j < W; ++j) {
			if (0 < j) std::printf(" ");
			std::printf("%d", matrix[i][j]);
		}
		std::printf("\n");
	}
}

/**
 * 行列の0要素を見つけてその行と列の全要素を0に置換するクラス
 */
template<typename TYPE, size_t H, size_t W>
class ReplaceMatrix
{
private:

	bool row_[H];		///< 0のあった行
	bool column_[W];	///< 0のあった列

	/**
	 * 行列を置換する準備 (補助メソッド)
	 * @param[in]	matrix	行列
	 * @note	計算量は O(mn)。ただし m, n はそれぞれ引数 @a の高さと幅。
	 */
	void
	prepare(const TYPE matrix[H][W])
		{
			assert(matrix);

			std::memset((void*)row_, 0, sizeof(bool) * H);
			std::memset((void*)column_, 0, sizeof(bool) * W);

			for (size_t i(0); i < H; ++i) {
				for (size_t j(0); j < W; ++j) {
					if (matrix[i][j]) continue;
					row_[i] = true;
					column_[j] = true;
				}
			}
		}

	/**
	 * 行列を置換 (補助メソッド)
	 * @param[in,out]	matrix	行列
	 * @note	事前にメソッド @a prepare を実施しておくこと。
	 * @note	最悪計算量は O(mn)。ただし m, n はそれぞれ引数 @a の高さと幅。
	 */
	void
	replace(TYPE matrix[H][W]) const
		{
			assert(matrix);

			for (size_t i(0); i < H; ++i) {
				if (!row_[i]) continue;
				for (size_t j(0); j < W; ++j) {
					matrix[i][j] = 0;
				}
			}

			for (size_t j(0); j < W; ++j) {
				if (!column_[j]) continue;
				for (size_t i(0); i < H; ++i) {
					matrix[i][j] = 0;
				}
			}
		}

public:

	/**
	 * 行列を置換
	 * @param[in,out]	matrix	行列
	 * @note	計算量は O(mn)。ただし m, n はそれぞれ引数 @a の高さと幅。
	 */
	void
	execute(TYPE matrix[H][W])
		{
			assert(matrix);

			prepare(matrix);
			replace(matrix);
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	int matrix[4][3] = {{1, 2, 3},
						{4, 5, 6},
						{7, 8, 9},
						{0, 1, 2}};

	ReplaceMatrix<int, 4, 3>* object = new ReplaceMatrix<int, 4, 3>();

	std::printf(">>>> before\n");
	print_matrix<4, 3>(matrix);
	object->execute(matrix);	// 1st replacing
	std::printf(">>>> after[1]\n");
	print_matrix<4, 3>(matrix);
	object->execute(matrix);	// 2nd replacing
	std::printf(">>>> after[2]\n");
	print_matrix<4, 3>(matrix);

	delete object;

	return 0;
}
