/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * @class	FindRoute
 * @brief	平面座標の(0, 0)から(W, H)に移動するパターンの総数を算出
 * @note	上か右にしか移動できない前提。
 * @note	テンプレートの型 @a TYPE は総数算出に用いる符号なし整数の型。
 * @note	テンプレートの整数 @a H , @a W は移動先の座標を示す。
 * @note	処理速度を無視すれば、フィールド @a counts_ は2行でも処理できる。
 */
template<typename TYPE, size_t H, size_t W>
class FindRoute
{
private:

	TYPE counts_[H+1][W+1];		///< パターン数の算出テーブル (DP処理)
	bool obstacles_[H+1][W+1];	///< 移動できない座標
	bool done_;	///< 算出処理完了済みフラグ

public:

	/**
	 * パターンの総数算出の準備
	 */
	void
	prepare()
		{
			std::memset((void*)counts_, 0, sizeof(counts_));
			std::memset((void*)obstacles_, 0, sizeof(obstacles_));
			done_ = false;
		}

	/**
	 * 移動できない座標を設定
	 * @param[in]	i	座標のyの値
	 * @param[in]	j	座標のxの値
	 * @note	メソッド @a prepare の後に実施する。
	 * @note	メソッド @a calculate の前に実施する。
	 * @note	本メソッドは複数回実行可能。
	 */
	void
	set_obstacle(size_t i,
				 size_t j)
		{
			obstacles_[i][j] = true;
		}

	/**
	 * パターンの総数算出
	 * @return	パターンの総数
	 * @note	DP処理により実装。
	 */
	TYPE
	calculate()
		{
			if (!done_) {
				if (!obstacles_[0][0]) counts_[0][0] = (TYPE)1;

				for (size_t i(0); i <= H; ++i) {
					for (size_t j(0); j <= W; ++j) {
						if (obstacles_[i][j]) continue;
						if (i < H) counts_[i+1][j] += counts_[i][j];
						if (j < W) counts_[i][j+1] += counts_[i][j];
					}
				}

				done_ = true;
			}

			return counts_[H][W];
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	FindRoute<unsigned int, 10, 10> finder;

	finder.prepare();
	unsigned int n = finder.calculate();

	std::printf("%u\n", n);

	return 0;
}
