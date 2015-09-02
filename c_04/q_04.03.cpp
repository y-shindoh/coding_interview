/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  昇順にソートされた配列が与えられたとき、
  高さが最小になる二分探索木を作るアルゴリズムを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include "binary_search_tree.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	const int keys[] = {5, 21, 0};
	Node<int>* node;

	// 下記 Node<TYPE>::Build<f> が回答

	node = Node<int>::Build(data, sizeof(data)/sizeof(data[0]));
	node->print(stdout);

	for (size_t i(0); i < sizeof(keys)/sizeof(keys[0]); ++i) {
		if (node->search(keys[i])) {
			std::printf("[%d]\ttrue\n", keys[i]);
		}
		else {
			std::printf("[%d]\tfalse\n", keys[i]);
		}
	}

	delete node;

	return 0;
}
