/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  古典的なハノイの塔の問題では、
  3つの塔とN枚のサイズの異なる円盤を用いて塔の間を移動させます。
  最初は円盤が下から上に向かって小さくなるように
  (どの円盤も自身より大きな円盤の上に乗っているように) なっています。
  そして以下のような制約を持ちます。
  (1) 一度に1枚の円盤しか動かせない。
  (2) 塔の一番上にある円盤を他の塔に移動させる。
  (3) 円盤を置くときは、それ自身より大きなものの上にしか置けない。
  スタックを用いて、最初の塔に積み上がっている円盤を
  最初の塔に移動させるプログラムを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <vector>

/**
 * ハノイの塔の問題解決器
 */
class HanoiSolver
{
private:

	size_t count_;	///< おもりの移動回数
	std::vector<unsigned int> towers_[3];	///< 3つの塔 (スタック)

	/**
	 * ハノイの塔の問題を解決 (補助関数)
	 * @param[in]	n	移動させるおもりの数
	 * @param[in]	f	移動元の塔
	 * @param[in]	w	作業用の塔
	 * @param[in]	d	移動先の塔
	 * @note	呼び出し時に各nに対して塔が初期状態 (説明が難しい) であれば、
				関数が返るときには、
				@a f の塔から @a d の塔に @a n 個の重りが移動している。
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

			// fからwにn-1枚を移動
			execute(n - 1, f, d, w);

			print();
			++count_;

			// nに対して残りの1枚を移動
			unsigned int v = towers_[f].back();
			towers_[f].pop_back();
			towers_[d].push_back(v);

			// wからdにn-1枚を移動
			execute(n - 1, w, f, d);
		}

	/**
	 * ハノイの塔の状態を出力
	 */
	void
	print() const
		{
			for (size_t i(0); i < 3; ++i) {
				std::printf("[%lu] ", i);
				size_t l = towers_[i].size();
				for (size_t j(0); j < l; ++j) {
					if (0 < j) std::printf(", ");
					std::printf("%u", towers_[i][j]);
				}
				std::printf("\n");
			}
		}

public:

	/**
	 * ハノイの塔の問題を解決
	 * @param[in]	n	おもりの数
	 * @note	計算量は O(2^n)。ただし n はおもりの数。
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
};

/**
 * 動作確認コマンド
 */
int main(void)
{
	HanoiSolver solver;

	solver.execute(4);

	return 0;
}
