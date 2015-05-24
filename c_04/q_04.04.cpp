/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.4の回答
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
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7};
	BinarySearchTree<int>* tree = new BinarySearchTree<int>(compare);
	std::vector<std::vector<const BinarySearchNode<int>*> > array;

	// 下記 BinarySearchTree::get_nodes_with_same_depth<f> が回答

	tree->prepare(data, sizeof(data)/sizeof(data[0]));
	tree->print(stdout);
	tree->get_nodes_with_same_depth(array);

	const size_t l = array.size();
	size_t m;
	for (size_t i(0); i < l; ++i) {
		m = array[i].size();
		std::printf("[%lu] ", i);
		for (size_t j(0); j < m; ++j) {
			if (0 < j) std::printf(", ");
			std::printf("%d", array[i][j]->get_key());
		}
		std::printf("\n");
	}

	delete tree;

	return 0;
}
