/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  二分木が二分探索木であるかどうかを調べる関数を実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <climits>
#include "binary_search_tree.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 7};
	Node<int>* head(0);

	// 下記 Node<TYPE>::check_condition<f> が回答

	head = Node<int>::Build(data, sizeof(data)/sizeof(data[0]));
	head->print(stdout);
	std::printf("=> %s\n", head->check_condition(INT_MIN, INT_MAX) ? "OK" : "NG");

	Node<int>* node = head->search(2);
	node->set_data(7);
	head->print(stdout);
	std::printf("=> %s\n", head->check_condition(INT_MIN, INT_MAX) ? "OK" : "NG");

	delete head;

	return 0;
}
