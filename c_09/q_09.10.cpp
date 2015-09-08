/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.10.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.10の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  幅 wi、高さ hi、奥行き di の、n個の箱の山があります。
  個々の箱は回転させることができず、
  それぞれの箱は幅、高さ、奥行きのすべてが大きい箱の上に積むことしかできません。
  積み上げた箱の高さができるだけ大きくなるように、箱を積むメソッドを実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * タプルの全要素を使って降順にソーティング
 * @param[in,out]	data	タプルの配列
 * @param[in]	length	配列 @a data の要素数
 * @note	ソート条件の優先度はタプルの後方の値ほど強い。
 * @note	実体は手抜きのバブル・ソート。最悪計算量は O(n^2)。
 */
template<typename TYPE, size_t N>
void
sort_tuples(TYPE data[][N],
			size_t length)
{
	assert(data);
	assert(0 < length);
	assert(0 < N);

	size_t h;
	bool f;
	TYPE tmp[N];

	for (size_t k(0); k < N; ++k) {
		for (size_t i(0); i < length; ++i) {
			h = length - i;
			f = true;
			for (size_t j(1); j < h; ++j) {
				if (data[j-1][k] >= data[j][k]) continue;
				std::memcpy((void*)tmp, (const void*)data[j-1], sizeof(tmp));
				std::memcpy((void*)data[j-1], (const void*)data[j], sizeof(tmp));
				std::memcpy((void*)data[j], (const void*)tmp, sizeof(tmp));
				f = false;
			}
			if (f) break;
		}
	}
}

/**
 * タプルの配列の全要素を出力
 * @param[out]	file	出力先
 * @param[in]	data	タプルの配列
 * @param[in]	length	配列 @a data の要素数
 */
template<typename TYPE, size_t N>
void
print_tuples(FILE* file,
			 const TYPE data[][N],
			 size_t length)
{
	assert(file);
	assert(data);
	assert(0 < length);

	for (size_t i(0); i < length; ++i) {
		std::fprintf(file, "[%lu: ", i);
		for (size_t j(0); j < N; ++j) {
			if (j) std::fprintf(file, ",");
			std::fprintf(file, "%G", (double)data[i][j]);
		}
		std::fprintf(file, "] ");
	}
	if (0 < length) std::fprintf(file, "\n");
}

size_t buffer[1024];	///< メソッド @a find_tuples_sequence_routine のキャッシュ

/**
 * タプルの完全下位要素を連結
 * @param[in]	data	ソート済みタプルの配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	index	最後に繋げた要素
 * @param[in]	target	返却値に用いるタプルの値のインデックス
 * @param[in,out]	buffer	DP用作業領域
 * @note	最悪計算量は O(n^2)。
 */
template<typename TYPE, size_t N>
void
find_tuples_sequence_routine(const TYPE data[][N],
							 size_t length,
							 size_t index,
							 size_t target,
							 size_t* buffer)
{
	assert(data);
	assert(0 < length);
	assert(target < N);

	if (index < length && buffer[index] == 0) {
		TYPE r(0);
		bool f;

		for (size_t i = index + 1; i < length; ++i) {
			f = false;
			for (size_t j(0); j < N; ++j) {
				if (data[index][j] > data[i][j]) continue;
				f = true;
				break;
			}
			if (f) continue;
			if (0 == buffer[i]) {	// 探索済みなら絶対に正の数が入っている
				find_tuples_sequence_routine<TYPE, N>(data, length, i, target, buffer);
			}
			if (r < buffer[i]) r = buffer[i];
		}

		buffer[index] = r + data[index][target];
	}
}

/**
 * タプルを連結し指定値の合計の最大値を算出
 * @param[in]	data	ソート済みタプルの配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	target	返却値に用いるタプルの値のインデックス
 * @param[in,out]	buffer	DP用作業領域 (0埋めしておくこと)
 * @return	連結したタプルの指定値の最大合計値
 * @note	最悪計算量は O(n^2)。
 */
template<typename TYPE, size_t N>
TYPE
find_tuples_sequence(const TYPE data[][N],
					 size_t length,
					 size_t target,
					 size_t* buffer)
{
	assert(data);
	assert(0 < length);
	assert(target < N);

	for (size_t i(0); i < length; ++i) {
		find_tuples_sequence_routine<TYPE, N>(data, length, i, target, buffer);
	}

	size_t h(0);

	for (size_t i(1); i < length; ++i) {
		if (buffer[h] >= buffer[i]) continue;
		h = i;
	}

	return buffer[h];
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t boxes[][3] = {{1, 2, 3},
						 {2, 2, 4},
						 {5, 4, 5},
						 {2, 3, 4},
						 {3, 1, 10}};
	const size_t l = sizeof(boxes) / sizeof(boxes[0]);

	print_tuples<size_t, 3>(stdout, boxes, l);
	sort_tuples<size_t, 3>(boxes, l);
	print_tuples<size_t, 3>(stdout, boxes, l);

	size_t buffer[sizeof(boxes) / sizeof(boxes[0])];

	std::memset((void*)buffer, 0, sizeof(buffer));
	size_t k = find_tuples_sequence<size_t, 3>(boxes, l, 2, buffer);
	std::printf("=> %lu\n", k);

	return 0;
}
