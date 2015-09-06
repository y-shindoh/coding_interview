/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ある集合の、すべての部分集合を返すメソッドを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <vector>

/**
 * 集合から全ての部分集合を生成
 * @param[in]	base	集合
 * @param[in,out]	buffer	作業領域 (初期呼び出し時は空にしておくこと)
 * @param[out]	subsets	集合 @a base の全ての部分集合
 * @note	計算量は O(2^n)。ただし n は引数 @a base の要素数。
 */
template<typename TYPE>
void
make_all_subsets_1(const std::vector<TYPE>& base,
				   std::vector<TYPE>& buffer,
				   std::vector< std::vector<TYPE> >& subsets,
				   size_t i = 0)
{
	if (base.size() <= i) {
		subsets.push_back(buffer);
		return;
	}

	make_all_subsets_1(base, buffer, subsets, i+1);

	buffer.push_back(base[i]);
	make_all_subsets_1(base, buffer, subsets, i+1);
	buffer.pop_back();
}

/**
 * 集合から全ての部分集合を生成
 * @param[in]	base	集合
 * @param[out]	subsets	集合 @a base の全ての部分集合
 * @note	計算量は O(2^n)。ただし n は引数 @a base の要素数。
 */
template<typename TYPE>
void
make_all_subsets_2(const std::vector<TYPE>& base,
				   std::vector< std::vector<TYPE> >& subsets)
{
	size_t n;

	subsets.resize(1);

	for (size_t i(0); i < base.size(); ++i) {
		n = subsets.size();
		for (size_t j(0); j < n; ++j) {
			subsets.push_back(subsets[j]);
			subsets.back().push_back(base[i]);
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	std::vector<int> base;
	std::vector<int> buffer;
	std::vector< std::vector<int> > subsets;

	for (size_t i(0); i < 4; ++i) base.push_back(i);

	std::vector< std::vector<int> >::const_iterator it;

	make_all_subsets_1<int>(base, buffer, subsets);

	for (it = subsets.begin(); it != subsets.end(); ++it) {
		std::printf("[");
		for (size_t i(0); i < it->size(); ++i) {
			if (0 < i) std::printf(", ");
			std::printf("%d", it->at(i));
		}
		std::printf("]\n");
	}

	std::printf("----\n");
	subsets.clear();

	make_all_subsets_2<int>(base, subsets);

	for (it = subsets.begin(); it != subsets.end(); ++it) {
		std::printf("[");
		for (size_t i(0); i < it->size(); ++i) {
			if (0 < i) std::printf(", ");
			std::printf("%d", it->at(i));
		}
		std::printf("]\n");
	}

	return 0;
}
