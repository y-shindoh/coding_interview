/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_10.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題10.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  40億個の整数からなる入力ファイルが与えられたとき、
  ファイルの中にない整数を見つけるアルゴリズムを考えてください。
  作業には1GBのメモリが使用できるとします。
  (訳注: 整数は32bit)

  発展問題:
  10MBのメモリしか使用できないとすれば、どのようにしますか?
 */

/*
  回答 (問題, 計算量 O(n)):
  後述のクラス Bucket を用いれば、
  該当整数 (符号なしと自然にみなせる) の有無がチェックできる。
  このとき、インスタンスのメモリ占有量は約0.5GBとなる。
  (M = 12500, N = 10000を想定)

  回答 (発展問題, 計算量 0(kn)):
  0〜79,999,999, 80,000,000〜159,999,999, ... などと分けて処理すれば、
  (単に各ブロック時にブロック外の数値を無視するだけ+オフセット処理)
  上記の問題と同じ要領で解くことができる。
  このとき計算量は分割数に比例して増える。

  回答 (発展問題, 計算量 O(n log n)):
  200万個の整数毎にソートしその結果をファイルに出力。
  そして合計2000個のファイルが生成されるので、
  それをマージ・ソートの要領で処理する (ファイル全体はメモリに置かない)。
  その際、スキップされる要素が検出できる。
 */

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>

/**
 * ビット列による 0〜M*N*sizeof(unsigned int)*8 の整数に対応するバケット
 */
template<size_t M, size_t N>
class Bucket
{
private:

	static const size_t L_ = sizeof(unsigned int) * (size_t)8;	///< インデックス計算用定数
	unsigned int* vector_[M];	///< ビット・バケット本体

public:

	/**
	 * コンストラクタ
	 */
	Bucket()
		{
			std::memset((void*)vector_, 0, sizeof(vector_));

			for (size_t i(0); i < M; ++i) {
				vector_[i] = new unsigned int[N];
				std::memset((void*)vector_[i], 0, sizeof(unsigned int) * N);
			}
		}

	/**
	 * デストラクタ
	 */
	~Bucket()
		{
			for (size_t i(0); i < M; ++i) {
				if (vector_[i]) delete [] vector_[i];
			}
		}

	/**
	 * 指定ビットを1に設定
	 * @param[in]	h	指定するビット位置
	 */
	void
	set(size_t h)
		{
			size_t i = h / (L_ * N);
			size_t j = h % (L_ * N) / L_;
			size_t k = h % L_;

			assert(i < M);
			assert(j < N);

			vector_[i][j] |= 1u << k;
		}

	/**
	 * 指定ビットを取得
	 * @param[in]	h	指定するビット位置
	 * @return	指定ビットの値
	 */
	bool
	get(size_t h) const
		{
			size_t i = h / (L_ * N);
			size_t j = h % (L_ * N) / L_;
			size_t k = h % L_;

			assert(i < M);
			assert(j < N);

			return (bool)(vector_[i][j] & (1u << k));
		}

	/**
	 * ビット・バケットの状態を出力
	 * @param[out]	file	出力先
	 */
	void
	print(FILE* file = stdout) const
		{
			for (size_t i(0); i < M; ++i) {
				std::fprintf(file, "[%lu]\t", i * L_ * N);
				for (size_t j(0); j < N; ++j) {
					if (0 < j) std::fprintf(file, " ");
					for (size_t k(0); k < sizeof(unsigned int) * (size_t)8; ++k) {
						std::fprintf(file, "%d", (bool)(vector_[i][j] & (1u << k)));
					}
				}
				std::fprintf(file, "\n");
			}
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	Bucket<4, 2> bucket;

	bucket.print();
	std::printf("----\n");
	bucket.set(64);
	bucket.set(97);
	bucket.set(200);
	bucket.print();

	for (size_t i(0); i < 4 * 2 * sizeof(unsigned int) * 8; ++i) {
		if (!bucket.get(i)) continue;
		std::printf("%lu: found\n", i);	// 今回は見つかった整数を表示
	}

	return 0;
}
