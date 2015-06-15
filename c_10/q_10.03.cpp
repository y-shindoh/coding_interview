/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_10.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題10.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstring>
#include <cstdio>

/**
 * @class	ビット・バケット
 * @note	テンプレートの整数については、
			内部的に使用する配列の幅を @a M, 高さを @a N で表している。
 */
template<size_t M, size_t N>
class Bucket
{
private:

	const size_t L_;			///< 配列 @a vector_ の1要素が持つメモリ領域のビット数
	unsigned int* vector_[N];	///< ビット・ベクトル

public:

	/**
	 * コンストラクタ
	 */
	Bucket()
		: L_(M * sizeof(unsigned int) * 8)
		{
			std::memset((void*)vector_, 0, sizeof(vector_));

			for (size_t i(0); i < N; ++i) {
				vector_[i] = new unsigned int[M];
				std::memset((void*)vector_[i], 0, sizeof(unsigned int) * M);
			}
		}

	/**
	 * デストラクタ
	 */
	virtual
	~Bucket()
		{
			for (size_t i(0); i < N; ++i) {
				if (!vector_[i]) continue;
				delete [] vector_[i];
			}
		}

	/**
	 * ビットを1に更新
	 * @param[in]	i	ビットの位置
	 */
	void
	set(size_t i)
		{
			size_t j = i / L_;
			size_t k = i % L_ / (sizeof(unsigned int) * 8);
			size_t h = i % (sizeof(unsigned int) * 8);

			vector_[j][k] |= 1u << h;
		}

	/**
	 * ビットを0に更新
	 * @param[in]	i	ビットの位置
	 */
	void
	reset(size_t i)
		{
			size_t j = i / L_;
			size_t k = i % L_ / (sizeof(unsigned int) * 8);
			size_t h = i % (sizeof(unsigned int) * 8);

			vector_[j][k] &= ~(1u << h);
		}

	/**
	 * ビットの状態を取得
	 * @param[in]	i	ビットの位置
	 * @return	ビットの状態
	 */
	bool
	get(size_t i)
		{
			size_t j = i / L_;
			size_t k = i % L_ / (sizeof(unsigned int) * 8);
			size_t h = i % (sizeof(unsigned int) * 8);

			return (bool)(vector_[j][k] & (1u << h));
		}


	/**
	 * ビットの状態を表示
	 * @param[out]	file	表示先
	 */
	void
	print(FILE* file)
		{
			int c;

			for (size_t i(0); i < N; ++i) {
				for (size_t j(0); j < M; ++j) {
					if (0 < j) std::printf(" ");
					for (size_t k(0); k < sizeof(unsigned int) * 8; ++k) {
						c = (vector_[i][j] & (1u << k)) != 0;
						std::printf("%d", c);
					}
				}
				std::printf("\n");
			}
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	Bucket<2, 4> bucket;

	bucket.print(stdout);
	std::printf("----\n");
	bucket.set(97);
	bucket.print(stdout);
	std::printf("----\n");
	bucket.set(64);
	bucket.print(stdout);

	return 0;
}
