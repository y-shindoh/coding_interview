/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>

/**
 * 配列の要素値と等しくなるインデックスを探索
 * @param[in]	array	昇順ソート済み配列
 * @param[in]	length	配列長
 * @return	0以上: 該当インデックス, 負の数: 見つからなかった
 * @note	最悪計算量はΘ(n)だが、配列中に重複があっても正常に動作する。
 */
template<typename TYPE>
int
search1(const TYPE* array,
		int length)
{
	assert(array);
	assert(length);

	for (TYPE i(0); i < (TYPE)length; ++i) {
		if (array[i] == (TYPE)i) return i;
	}

	return -1;
}

/**
 * 配列の要素値と等しくなるインデックスを探索
 * @param[in]	array	昇順ソート済み配列 (重複なし)
 * @param[in]	length	配列長
 * @return	0以上: 該当インデックス, 負の数: 見つからなかった
 * @note	最悪計算量はΘ(log n)だが、配列中に重複があると正常に動作しない。
 */
template<typename TYPE>
int
search2(const TYPE* array,
		int length)
{
	assert(array);
	assert(length);

	int s(0);
	int e(length - 1);

	if ((TYPE)s < array[s]) return -1;
	if (array[e] < (TYPE)e) return -1;

	int i = length / 2;

	while (array[i] != (TYPE)i) {
		if (array[i] < (TYPE)i) s = i + 1;
		else e = i - 1;
		if (e < s) break;
		i = (s + e) / 2;
	}

	if (array[i] != (TYPE)i) return -1;

	return i;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int a[][9] = {{-5, -4, -3, -2, 0, 4, 5, 7, 9},
				  {-5, -4, -3, -1, 0, 1, 2, 3, 4},
				  {5, 6, 7, 8, 9, 10, 11, 12, 13},
				  {-5, -5, -3, -2, 0, 4, 5, 8, 8},
				  {-1, -1, -1, -1, -1, 7, 7, 7, 7},
				  {7, 7, 7, 7, 7, 7, 7, 8, 8}};
	int h;

	for (size_t i(0); i < sizeof(a) / sizeof(a[0]); ++i) {
		std::printf("<%lu>\n", i);
		// 1st
		h = search1(a[i], sizeof(a[0]) / sizeof(a[0][0]));
		if (0 <= h) {
			std::printf("1:\ta[%d] = %d\n", a[i][h], h);
		}
		else {
			std::printf("1:\tnot found!\n");
		}
		// 2nd (重複ありに非対応)
		h = search2(a[i], sizeof(a[0]) / sizeof(a[0][0]));
		if (0 <= h) {
			std::printf("2:\ta[%d] = %d\n", a[i][h], h);
		}
		else {
			std::printf("2:\tnot found!\n");
		}
	}

	return 0;
}
