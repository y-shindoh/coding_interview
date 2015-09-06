/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ある配列 A[0...n-1] について A[i] = i となるインデックスiをマジックインデックスとします。
  異なる整数で昇順にソートされた配列が与えられたとき、
  マジックインデックスが存在するとすれば、それを探し出すメソッドを書いてください。

  発展問題:
  配列の値が異なる整数でない場合はどのようにすればよいですか?
 */

#include <cstddef>
#include <cstdio>
#include <cassert>

/**
 * マジック・インデックスを探索
 * @param[in]	array	探索対象の配列 (重複する値を持たないこと)
 * @param[in]	length	引数 @a array の要素数
 * @return	マジック・インデックス (探索失敗時は負の数値が返る)
 * @note	最悪計算量は O(log length)。
 * @note	重複する値を持つ配列に対しては、最悪計算量 O(length) の探索しかない。
			つまり線形探索と同程度の最悪計算量のアルゴリズムしか適用できない。
 * @note	テンプレートの型 @a TYPE には符号あり整数を与えること。
 */
template<typename TYPE>
TYPE
search_magic_index(const TYPE* array,
				   size_t length)
{
	assert(array);

	TYPE s(0);
	TYPE e((TYPE)length - 1);
	TYPE i;

	while (s <= e) {
		i = (s + e) / 2;
		if (array[i] < i) {
			s = i + 1;
		}
		else if (i < array[i]) {
			e = i - 1;
		}
		else {
			return i;
		}
	}

	return (TYPE)-1;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int a[][9] = {{-5, -4, -3, -2, 0, 4, 5, 7, 9},
				  {-5, -4, -3, -1, 0, 1, 2, 3, 4},
				  {5, 6, 7, 8, 9, 10, 11, 12, 13},
				  {0, 2, 4, 6, 8, 10, 12, 13, 14},
				  {-8, -6, -4, -2, 0, 2, 4, 6, 8}};
	int h;

	for (size_t i(0); i < sizeof(a) / sizeof(a[0]); ++i) {
		std::printf("<%lu>\n", i);
		// 1st
		h = search_magic_index<int>(a[i], sizeof(a[0]) / sizeof(a[0][0]));
		if (0 <= h) {
			std::printf("1:\ta[%d] = %d\n", a[i][h], h);
		}
		else {
			std::printf("1:\tnot found!\n");
		}
	}

	return 0;
}
