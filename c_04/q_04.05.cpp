/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#define	__BINARY_SEARCH_TREE_GET_RAW_DATA__ 1
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
	const int data[] = {0, 1, 2, 3, 4, 5, 6};
	BinarySearchTree<int>* tree = new BinarySearchTree<int>(compare);

	// 下記 BinarySearchTree::is_correct<f> が回答

	tree->prepare(data, sizeof(data)/sizeof(data[0]));
	tree->print(stdout);
	std::printf("=> %s\n", tree->is_correct() ? "OK" : "NG");

	BinarySearchNode<int>* node = tree->search(0);
	node->set_key(2);
	tree->print(stdout);
	std::printf("=> %s\n", tree->is_correct() ? "OK" : "NG");

	delete tree;

	return 0;
}
