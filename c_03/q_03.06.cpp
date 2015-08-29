/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  スタック上のデータを小さい順に並べ替えるプログラムを書いてください
  (最も小さいアイテムがトップに来る)。
  データ保持のために追加のスタックを用いてもかまいませんが、
  スタック以外のデータ構造 (配列など) に
  スタック上のデータをコピーしてはいけません。
  また、スタックは以下の操作のみ使用できます。
  push, pop, peek, isEmpty (std::vector の push_back, pop_back, back, empty)
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

/**
 * スタックをソーティング
 * @param[in,out]	stack	ソーティング対象のスタック
 * @param[out]	buffer	作業領域
 * @note	計算量は O(n^2)。
 * @note	書籍では挿入ソートを説明していたが、ここでは選択ソートで実装する。
 */
template<typename TYPE>
void
sort_stack(std::vector<TYPE>& stack,
		   std::vector<TYPE>& buffer)
{
	int i, k;
	int h(0);	// 位置確定済み要素数
	int l(0);	// 要素の総数
	TYPE data, max;

	buffer.clear();

	do {
		i = 0;
		// 最大値の探索
		k = -1;
		while (h == 0 || i + h < l) {
			data = stack.back();
			stack.pop_back();
			if (k < 0 || max < data) {
				k = i;
				max = data;
			}
			buffer.push_back(data);
			if (h == 0) ++l;
			++i;
			if (stack.empty()) break;
		}
		// 最大値の格納
		stack.push_back(max);
		// その他要素の格納
		while (0 <= --i) {
			data = buffer.back();
			buffer.pop_back();
			if (k == i) continue;	// 最大値をスキップ
			stack.push_back(data);
		}
	} while (++h < l);
}

/**
 * スタック (配列) を表示
 * @param[in]	stack	表示対象のスタック
 */
template<typename TYPE>
void
print(const std::vector<TYPE>& stack)
{
	const size_t l = stack.size();
	for (size_t i(0); i < l; ++i) {
		if (0 < i) std::printf(", ");
		std::printf("%G", (double)stack[i]);
	}
	std::printf("\n");
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 0, 2, 4, 6, 8};
	std::vector<int> stack;
	std::vector<int> buffer;

	for (size_t i(0); i < sizeof(data)/sizeof(data[0]); ++i) {
		stack.push_back(data[i]);
	}

	print<int>(stack);
	sort_stack<int>(stack, buffer);
	print<int>(stack);

	return 0;
}
