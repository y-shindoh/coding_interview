/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstring>
#include <cstdio>

/**
 * @class	行列において0が出現した行・列を全て0に置換するクラス
 * @note	テンプレートの @a TYPE には行列の要素の型を適用する。
 * @note	テンプレートの @a H には行列の行数を適用する。
 * @note	テンプレートの @a W には行列の列数を適用する。
 */
template<typename TYPE, size_t H, size_t W>
class ReplaceMatrix
{
private:

	bool line_[H];		///< 行に関する0の出現状況
	bool column_[W];	///< 列に関する0の出現状況

public:

	/**
	 * 行列において0が出現した行・列を全て0に置換
	 * @param[in]	matrix	置換対象の行列
	 * @note	最悪計算量はO(HW)になる。
	 */
	void
	execute(TYPE matrix[H][W])
		{
			std::memset((void*)line_, 0, sizeof(line_));
			std::memset((void*)column_, 0, sizeof(column_));

			size_t count_l(0);
			size_t count_c(0);

			for (size_t i(0); i < H; ++i) {
				for (size_t j(0); j < W; ++j) {
					if ((TYPE)0 != matrix[i][j]) continue;
					if (!line_[i]) {
						line_[i] = true;
						++count_l;
						if (H <= count_l) break;
					}
					if (!column_[j]) {
						column_[j] = true;
						++count_c;
						if (W <= count_c) break;
					}
				}
			}

			////////////////////////////////////////////////////////////
			// ここで「H <= count_l && W <= count_c」が
			// 常に「false」になることに注意。

			if (count_c < W) {
				for (size_t i(0); i < H; ++i) {
					if (!line_[i]) continue;
					for (size_t j(0); j < W; ++j) {
						matrix[i][j] = (TYPE)0;
					}
				}
			}

			if (count_l < H) {
				for (size_t j(0); j < W; ++j) {
					if (!column_[j]) continue;
					for (size_t i(0); i < H; ++i) {
						matrix[i][j] = (TYPE)0;
					}
				}
			}
		}
};

/**
 * 行列を表示
 */
template<size_t H, size_t W>
void
print_matrix(int matrix[H][W])
{
	for (size_t i(0); i < H; ++i) {
		for (size_t j(0); j < W; ++j) {
			std::printf("%d ", matrix[i][j]);
		}
		std::printf("\n");
	}
}

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
