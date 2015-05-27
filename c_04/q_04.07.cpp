/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#define	__BINARY_SEARCH_TREE_GET_RAW_DATA__	1
#define	__BINARY_SEARCH_TREE_ENABLE_PARENT__	1
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
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	const size_t l = sizeof(data)/sizeof(data[0]);
	BinarySearchTree<int>* tree = new BinarySearchTree<int>(compare);

	tree->prepare(data, l);
	std::printf("**tree**\n");
	tree->print(stdout, 0);

	// 下記の BinarySearchNode<int>::FindSameParent が問題の回答

	const BinarySearchNode<int>* node_1 = tree->search(3);
	const BinarySearchNode<int>* node_2 = tree->search(8);
	if (node_1 && node_2) {
		const BinarySearchNode<int>* node = BinarySearchNode<int>::FindSameParent(node_1, node_2);
		if (node) {
			std::printf(">>>> %d, %d => %d\n",
						node_1->get_key(), node_2->get_key(), node->get_key());
		}
	}

	delete tree;

	return 0;
}
