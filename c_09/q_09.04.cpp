/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * 全ての部分集合を生成
 * @note	テンプレートの型 @a TYPE は符号なし整数。
 */
template<typename TYPE>
class SubsetMaker
{
private:

	std::vector<TYPE> buffer_;					///< 部分集合生成の作業領域
	std::vector<std::vector<TYPE> >* storage_;	///< 部分集合の集合 (返却値)

	/**
	 * メソッド @a execute の再帰処理部分
	 * @param[in]	n	集合の要素数 (集合は1〜nの要素を含むとみなす)
	 * @param[in]	i	追加検討対象の要素
	 * @param[in]	flag	部分集合確定状態 (true: 確定, false: 確定してない)
	 */
	void
	execute_routine(TYPE n,
					TYPE i,
					bool flag)
		{
			if (flag) storage_->push_back(buffer_);
			if (n < i) return;
			buffer_.push_back(i);
			execute_routine(n, i + 1, true);
			buffer_.pop_back();
			execute_routine(n, i + 1, false);
		}

public:

	/**
	 * 全ての部分集合を生成
	 * @param[in]	n	集合の要素数 (集合は1〜nの要素を含むとみなす)
	 * @return	全ての部分集合
	 * @note	生成失敗時は @a 0 が返却される。
	 * @note	返却値は本メソッド利用者の責任で削除すること。
	 * @note	計算量・メモリ占有量ともに O(2^n)。
	 */
	std::vector<std::vector<TYPE> >*
	execute_1(TYPE n)
		{
			try {
				storage_ = new std::vector<std::vector<TYPE> >();
			}
			catch (...) {
				return 0;
			}

			buffer_.clear();
			buffer_.reserve(n);
			execute_routine(n, 1, true);

			return storage_;
		}

	/**
	 * 全ての部分集合を生成
	 * @param[in]	n	集合の要素数 (集合は1〜nの要素を含むとみなす)
	 * @return	全ての部分集合
	 * @note	生成失敗時は @a 0 が返却される。
	 * @note	返却値は本メソッド利用者の責任で削除すること。
	 * @note	計算量・メモリ占有量ともに O(2^n)。
	 */
	std::vector<std::vector<TYPE> >*
	execute_2(TYPE n)
		{
			try {
				storage_ = new std::vector<std::vector<TYPE> >();
			}
			catch (...) {
				return 0;
			}

			storage_->resize(1);

			size_t m;
			for (TYPE i(1); i <= n; ++i) {
				m = storage_->size();
				for (size_t j(0); j < m; ++j) {
					storage_->push_back(storage_->at(j));
					storage_->back().push_back(i);	// 遅い?
				}
			}

			return storage_;
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{

	SubsetMaker<unsigned int> maker;
	std::vector<std::vector<unsigned int> >* subsets = maker.execute_1(3);

	size_t m = subsets->size();
	size_t n;
	for (size_t i(0); i < m; ++i) {
		std::printf("[%lu] ", i);
		n = subsets->at(i).size();
		for (size_t j(0); j < n; ++j) {
			if (0 < j) std::printf(", ");
			std::printf("%u", subsets->at(i)[j]);
		}
		std::printf("\n");
	}

	delete subsets;

	return 0;
}
