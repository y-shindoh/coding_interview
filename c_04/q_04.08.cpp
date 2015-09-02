/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.08.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  数百万のノードを持つT1と、数百のノードを持つT2の、2つの二分木があります。
  このとき、T2がT1の部分木になっているかどうかを判定するアルゴリズムを作ってください。
  T2がT1の部分木であるということは、T1上のあるノードnについて、
  n以下の部分木がT2と同じであるということです。
 */

#include <cstddef>
#include <cstdio>
#include "binary_search_tree.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data_1[] = {0, 1, 2, 3, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7};
	const int data_2[] = {0, 1, 2, 3};
	Node<int>* head_1;
	Node<int>* head_2;

	// 下記 Node<TYPE>::have_subtree<f> が回答

	head_1 = Node<int>::Build(data_1, sizeof(data_1) / sizeof(data_1[0]));
	head_1->print(stdout);

	head_2 = Node<int>::Build(data_2, sizeof(data_2) / sizeof(data_2[0]));
	head_2->print(stdout);

	if (head_1->have_subtree(head_2)) {
		std::printf("FOUND A SUBTREE!\n");
	}
	else {
		std::printf("NOT FOUND ANY SUBTREES!\n");
	}

	delete head_1;
	delete head_2;

	return 0;
}
