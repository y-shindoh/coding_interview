/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include "binary_search_tree.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 2, 3, 4, 5, 6};
	BinarySearchTree<int>* tree = new BinarySearchTree<int>();

	// 下記 BinarySearchTree::print<f> が回答

	tree->prepare(data, sizeof(data)/sizeof(data[0]));
	std::printf("**in-order**\n");
	tree->print(stdout, 0);
	std::printf("**pre-order**\n");
	tree->print(stdout, -1);
	std::printf("**post-order**\n");
	tree->print(stdout, 1);

	delete tree;

	return 0;
}
