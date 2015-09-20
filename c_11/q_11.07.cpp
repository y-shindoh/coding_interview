/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  サーカスで、人の肩の上に立つようにしてタワーを作っています。
  実際的な理由と美的な理由で、
  タワーで上に乗る人は下の人よりも背が低く、体重も軽くなければなりません。
  タワーを作る人たちの身長と体重がわかっているとき、
  条件を満たすタワーを作ることのできる最大の人数を計算するメソッドを書いてください。
 */

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <utility>

/**
 * 指定要素を起点とした連結する要素の最大数を算出
 * @param[in]	data	サイズの組の配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	index	起点要素のインデックス
 * @param[out]	buffer	計算領域
 * @return	連結した要素の最大数
 * @note	テンプレートの型 @a TYPE は配列の要素の型。
 * @note	最悪計算量は O(n^2)。ただし n は @a length に等しい。
 */
template<typename TYPE>
void
find_longest_sequence(const std::pair<TYPE, TYPE>* data,
					  size_t length,
					  size_t index,
					  size_t* buffer)
{
	assert(data);
	assert(0 < length);
	assert(index < length);
	assert(buffer);

	if (0 < buffer[index]) return;

	for (size_t i(0); i < length; ++i) {
		if (i == index) continue;
		if (data[index].first <= data[i].first) continue;
		if (data[index].second <= data[i].second) continue;
		find_longest_sequence<TYPE>(data, length, i, buffer);
		if (buffer[index] < buffer[i]) buffer[index] = buffer[i];
	}

	++buffer[index];
}

/**
 * 連結する要素の最大数を算出
 * @param[in]	data	サイズの組の配列
 * @param[in]	length	配列 @a data の要素数
 * @param[out]	buffer	計算領域
 * @return	連結した要素の最大数
 * @note	テンプレートの型 @a TYPE は配列の要素の型。
 * @note	最悪計算量は O(n^2)。ただし n は @a length に等しい。
 * @note	ソーティング後の配列を処理した方が効率的だが、
			今回は未ソートの配列を対象にした。
 */
template<typename TYPE>
size_t
find_longest_sequence(const std::pair<TYPE, TYPE>* data,
					  size_t length,
					  size_t* buffer)
{
	assert(data);
	assert(0 < length);
	assert(buffer);

	std::memset((void*)buffer, 0, sizeof(size_t) * length);

	size_t k(0);

	for (size_t i(0); i < length; ++i) {
		find_longest_sequence<TYPE>(data, length, i, buffer);
		if (buffer[k] < buffer[i]) k = i;
	}

	return buffer[k];
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const std::pair<size_t, size_t> people[] = {std::pair<size_t, size_t>(65, 100),
												std::pair<size_t, size_t>(70, 150),
												std::pair<size_t, size_t>(56, 90),
												std::pair<size_t, size_t>(75, 190),
												std::pair<size_t, size_t>(60, 95),
												std::pair<size_t, size_t>(66, 160),
												std::pair<size_t, size_t>(68, 110)};
	const size_t l = sizeof(people) / sizeof(people[0]);
	size_t buffer[sizeof(people) / sizeof(people[0])];

	for (size_t i(0); i < l; ++i) {
		std::printf("[%lu] %lu, %lu\n", i, people[i].first, people[i].second);
	}

	size_t k = find_longest_sequence<size_t>(people, l, buffer);

	std::printf("=> %lu\n", k);

	return 0;
}
