/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.6の回答
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

	const BinarySearchNode<int>* node = tree->search(data[0]);

	std::printf("**in-order tracing**\n");
	while (node) {
		std::printf("%d\n", node->get_key());
		node = BinarySearchNode<int>::GetNextNode(node);	// 問題の回答
	}

	node = tree->search(data[l-1]);

	std::printf("**in-order tracing (reverse)**\n");
	while (node) {
		std::printf("%d\n", node->get_key());
		node = BinarySearchNode<int>::GetNextNode(node, 1);
	}

	delete tree;

	return 0;
}
