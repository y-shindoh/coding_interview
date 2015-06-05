/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.10.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.10の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * タプルの全要素を使って降順にソーティング
 * @param[in,out]	data	タプルの配列
 * @param[in]	length	配列 @a data の要素数
 * @note	ソート条件の優先度はタプルの前方の値ほど強い。
 * @note	テンプレートの型 @a TYPE はタプルの値の型。
 * @note	テンプレートの整数 @a N はタプルの値の数。
 * @note	実体は手抜きのバブル・ソート。最悪計算量は O(n^2)。
 */
template<typename TYPE, size_t N>
void
sort_tuples(TYPE data[][N],
			size_t length)
{
	assert(data);
	assert(length);

	bool c;
	size_t h;
	TYPE tmp[N];

	for (size_t k(0); k < N; ++k) {
		for (size_t i(0); i < length; ++i) {
			h = length - i;
			c = false;
			for (size_t j(1); j < h; ++j) {
				if (data[j-1][k] >= data[j][k]) continue;
				c = true;
				std::memcpy((void*)tmp, (const void*)data[j], sizeof(TYPE) * N);
				std::memcpy((void*)data[j], (const void*)data[j-1], sizeof(TYPE) * N);
				std::memcpy((void*)data[j-1], (const void*)tmp, sizeof(TYPE) * N);
			}
			if (!c) break;
		}
	}
}

/**
 * タプルの配列の全要素を出力
 * @param[out]	file	出力先
 * @param[in]	data	タプルの配列
 * @param[in]	length	配列 @a data の要素数
 * @note	テンプレートの型 @a TYPE はタプルの値の型。
 * @note	テンプレートの整数 @a N はタプルの値の数。
 */
template<typename TYPE, size_t N>
void
print_tuples(FILE* file,
			 const TYPE data[][N],
			 size_t length)
{
	assert(file);
	assert(data);
	assert(length);

	for (size_t i(0); i < length; ++i) {
		std::fprintf(file, "[%lu: ", i);
		for (size_t j(0); j < N; ++j) {
			if (j) std::fprintf(file, ",");
			std::fprintf(file, "%G", (double)data[i][j]);
		}
		std::fprintf(file, "] ");
	}
	if (length) std::fprintf(file, "\n");
}

size_t buffer[1024];	///< メソッド @a find_tuples_sequence_routine のキャッシュ

/**
 * タプルの完全下位要素を連結
 * @param[in]	data	ソート済みタプルの配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	index	最後に繋げた要素
 * @param[in]	target	返却値に用いるタプルの値のインデックス
 * @return	連結したタプルの指定値の合計
 * @note	テンプレートの型 @a TYPE はタプルの値の型。
 * @note	テンプレートの整数 @a N はタプルの値の数。
 */
template<typename TYPE, size_t N>
TYPE
find_tuples_sequence_routine(const TYPE data[][N],
							 size_t length,
							 size_t index,
							 size_t target)
{
	assert(data);
	assert(length);
	assert(target < N);

	if (length <= index + 1) return 0;

	if (buffer[index] == ~(size_t)0) {
		buffer[index] = 0;
		bool flag;
		TYPE t;

		for (size_t i(index+1); i < length; ++i) {
			flag = true;
			for (size_t j(0); j < N; ++j) {
				if (data[index][j] > data[i][j]) continue;
				flag = false;
				break;
			}
			if (!flag) continue;
			t = find_tuples_sequence_routine<TYPE, N>(data, length, i, target);
			t += data[i][2];
			if (buffer[index] < t) buffer[index] = t;
		}
	}

	return buffer[index];
}

/**
 * タプルを連結し指定値の合計の最大値を算出
 * @param[in]	data	ソート済みタプルの配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	target	返却値に用いるタプルの値のインデックス
 * @return	連結したタプルの指定値の最大合計値
 * @note	テンプレートの型 @a TYPE はタプルの値の型。
 * @note	テンプレートの整数 @a N はタプルの値の数。
 * @todo	ソーティングした方が計算効率が良いか検討すること。
 */
template<typename TYPE, size_t N>
TYPE
find_tuples_sequence(const TYPE data[][N],
					 size_t length,
					 size_t target)
{
	assert(data);
	assert(length);
	assert(target < N);

	TYPE t;
	TYPE m(0);

	for (size_t i(0); i < length; ++i) {
		t = find_tuples_sequence_routine<TYPE, N>(data, length, i, target);
		t += data[i][target];
		if (m < t) m = t;
	}

	return m;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t boxes[][3] = {{1, 2, 3},
						 {2, 2, 4},
						 {5, 4, 5},
						 {2, 3, 4}};
	const size_t l = sizeof(boxes) / sizeof(boxes[0]);

	std::memset((void*)buffer, ~0, sizeof(buffer));

	print_tuples<size_t, 3>(stdout, boxes, l);
	sort_tuples<size_t, 3>(boxes, l);
	print_tuples<size_t, 3>(stdout, boxes, l);

	size_t k = find_tuples_sequence<size_t, 3>(boxes, l, 2);
	std::printf("=> %lu\n", k);

	return 0;
}
