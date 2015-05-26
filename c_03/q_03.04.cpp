/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <vector>
#include <string>

/**
 * ハノイの塔の問題解決器
 */
class HanoiSolver
{
private:

	size_t count_;	///< おもりの移動回数
	std::vector<unsigned int> towers_[3];	///< 3つの塔

public:

	/**
	 * ハノイの塔の問題を解決
	 * @param[in]	n	おもりの数
	 */
	void
	execute(int n)
		{
			count_ = 0;

			for (int i(0); i < 3; ++i) {
				towers_[i].resize(n);
				towers_[i].clear();
			}

			int j;
			for (int i(0); i < n; ++i) {
				j = n - i;
				towers_[0].push_back(j);
			}

			execute(n, 0, 1, 2);

			print();

			std::printf("=> %lu\n", count_);
		}

	/**
	 * ハノイの塔の問題を解決
	 * @param[in]	n	先の再帰処理の回数
	 * @param[in]	f	移動元の塔
	 * @param[in]	w	作業用の塔
	 * @param[in]	d	移動先の塔
	 */
	void
	execute(int n,
			int f,
			int w,
			int d)
		{
			if (n <= 0) {
				std::printf("----\n");
				return;
			}

			execute(n - 1, f, d, w);

			print();
			++count_;

			int v = towers_[f].back();
			towers_[f].pop_back();
			towers_[d].push_back(v);

			execute(n - 1, w, f, d);
		}

	/**
	 * ハノイの塔の状態を出力
	 */
	void
	print()
		{
			for (size_t i(0); i < 3; ++i) {
				std::printf("[%lu] ", i);
				size_t l = towers_[i].size();
				for (size_t j(0); j < l; ++j) {
					if (0 < j) std::printf(", ");
					std::printf("%d", towers_[i][j]);
				}
				std::printf("\n");
			}
		}
};

/**
 * 動作確認コマンド
 */
int main(void)
{
	HanoiSolver solver;

	solver.execute(8);

    return 0;
}
