/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "list.hpp"

/**
 * リストの末尾からn番目の要素を取得
 * @param[in]	head	リストの先頭ノード
 * @param[in]	n	指定する位置 (1以上)
 * @return	リストの末尾からn番目の要素
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	テンプレートの数値 @a N は引数 @a n より大きな数字。
 * @note	計算量はO(n)となる。ただしこのnはリストの長さとする。
 */
template<typename TYPE, size_t N>
const Node<TYPE>*
DeleteTailNode(const Node<TYPE>* node,
			   size_t n = 1)
{
	const Node<TYPE>* pointers[N];
	size_t l(0);
	size_t i;

	assert(n <= N);
	assert(0 < n);

	while (node) {
		i = l++ % n;
		pointers[i] = node;
		node = node->get_next();
	}

	if (l < n) return 0;

	i = l % n;

	return pointers[i];
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};
	Node<int>* list = Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));
	const Node<int>* (*function)(const Node<int>*, size_t) =  DeleteTailNode<int, 32>;
	const Node<int>* node;

	Node<int>::Print(stdout, list);
	for (size_t i(1); i < sizeof(data)/sizeof(data[0]); i += 3) {
		node = function(list, i);
		if (node) {
			std::printf("[%lu]\t%d\n", i, node->get_key());
		}
	}

	Node<int>::DeleteList(list);

	return 0;
}
