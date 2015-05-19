/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.1の回答
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

	// 下記 BinarySearchTree::is_balanced<f> が回答

	tree->prepare(data, sizeof(data)/sizeof(data[0]));
	tree->print(stdout);
	std::printf("=> %s\n", tree->is_balanced() ? "balanced" : "unbalanced");
	tree->add(-1);
	tree->print(stdout);
	std::printf("=> %s\n", tree->is_balanced() ? "balanced" : "unbalanced");
	tree->add(8);
	tree->print(stdout);
	std::printf("=> %s\n", tree->is_balanced() ? "balanced" : "unbalanced");

	delete tree;

	return 0;
}
