/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <utility>

/**
 * サイズ情報により配列をソート
 * @param[in]	data	サイズの組の配列
 * @param[in]	length	配列 @a data の要素数
 * @note	サイズ情報は2番目の要素を優先する。
 */
template<typename TYPE>
void
sort_pairs_array(std::pair<TYPE, TYPE>* data,
				 size_t length)
{
	bool flag;
	size_t k;

	for (size_t i(0); i < length; ++i) {
		k = length - i;
		flag = false;
		for (size_t j(1); j < k; ++j) {
			if (data[j-1].first >= data[j].first) continue;
			data[j-1].swap(data[j]);
			flag = true;
		}
		if (!flag) break;
	}

	for (size_t i(0); i < length; ++i) {
		k = length - i;
		flag = false;
		for (size_t j(1); j < k; ++j) {
			if (data[j-1].second >= data[j].second) continue;
			data[j-1].swap(data[j]);
			flag = true;
		}
		if (!flag) break;
	}
}

/**
 * 関数 @a find_longest_sequence の補助関数
 * @param[in]	data	サイズの組の配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	index	最後に参照した要素のインデックス
 * @return	連結したエッジの最大数
 * @note	テンプレートの型 @a TYPE は配列の要素の型。
 */
template<typename TYPE>
size_t
find_longest_sequence_routine(const std::pair<TYPE, TYPE>* data,
							  size_t length,
							  size_t index)
{
	size_t k;
	size_t m(0);

	for (size_t i(index+1); i < length; ++i) {
		if (data[index].first <= data[i].first) continue;
		if (data[index].second <= data[i].second) continue;
		k = find_longest_sequence_routine(data, length, i) + 1;
		if (m < k) m = k;
	}

	return m;
}

/**
 * 連結する要素の最大数を算出
 * @param[in]	data	サイズの組の配列
 * @param[in]	length	配列 @a data の要素数
 * @return	連結した要素の最大数
 * @note	テンプレートの型 @a TYPE は配列の要素の型。
 * @todo	動的計画法による実装に書き直すこと。
 */
template<typename TYPE>
size_t
find_longest_sequence(const std::pair<TYPE, TYPE>* data,
					  size_t length)
{
	size_t k;
	size_t m(0);

	for (size_t i(0); i < length; ++i) {
		k = find_longest_sequence_routine<TYPE>(data, length, i);
		if (m < k) m = k;
	}

	return m + 1;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	std::pair<size_t, size_t> people[] = {std::pair<size_t, size_t>(65, 100),
										  std::pair<size_t, size_t>(70, 150),
										  std::pair<size_t, size_t>(56, 90),
										  std::pair<size_t, size_t>(75, 190),
										  std::pair<size_t, size_t>(60, 95),
										  std::pair<size_t, size_t>(68, 110)};
	const size_t l = sizeof(people) / sizeof(people[0]);

	for (size_t i(0); i < l; ++i) {
		std::printf("[%lu] %lu, %lu\n", i, people[i].first, people[i].second);
	}

	sort_pairs_array<size_t>(people, l);

	std::printf("----\n");
	for (size_t i(0); i < l; ++i) {
		std::printf("[%lu] %lu, %lu\n", i, people[i].first, people[i].second);
	}

	size_t k = find_longest_sequence<size_t>(people, l);

	std::printf("=> %lu\n", k);

	return 0;
}
