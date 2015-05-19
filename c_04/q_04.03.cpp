/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include "binary_search_tree.hpp"

/**
 * 比較関数
 */
int
compare(const int& left,
		const int& right)
{
	if (left < right) {
		return -1;
	}
	else if (left > right) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	const int keys[] = {5, 21, 0};
	BinarySearchTree<int>* tree = new BinarySearchTree<int>(compare);

	// 下記 BinarySearchTree::prepare<f> が回答

	tree->prepare(data, sizeof(data)/sizeof(data[0]));
	tree->print(stdout);

	for (size_t i(0); i < sizeof(keys)/sizeof(keys[0]); ++i) {
		if (tree->search(keys[i])) {
			std::printf("[%d]\ttrue\n", keys[i]);
		}
		else {
			std::printf("[%d]\tfalse\n", keys[i]);
		}
	}

	delete tree;

	return 0;
}
