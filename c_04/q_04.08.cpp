/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.08.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.8の回答
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
	const int data_1[] = {0, 1, 2, 3, 4, 5, 6, 7};
	const int data_2[] = {0, 1, 2};
	BinarySearchTree<int>* tree_1 = new BinarySearchTree<int>(compare);
	BinarySearchTree<int>* tree_2 = new BinarySearchTree<int>(compare);

	// 下記 BinarySearchTree::has_subtree<f> が回答

	tree_1->prepare(data_1, sizeof(data_1)/sizeof(data_1[0]));
	tree_1->print(stdout);

	tree_2->prepare(data_2, sizeof(data_2)/sizeof(data_2[0]));
	tree_2->print(stdout);

	if (tree_1->has_subtree(*tree_2)) {
		std::printf("FOUND A SUBTREE!\n");
	}
	else {
		std::printf("NOT FOUND ANY SUBTREES!\n");
	}

	delete tree_1;
	delete tree_2;

	return 0;
}
