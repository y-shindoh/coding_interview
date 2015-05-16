/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#define	USE_DOUBLY_LINKED_LIST	1	// 双方向リストを使う
#include "list.hpp"

/**
 * 回文チェッカー
 * @param[in]	head	処理対象のリスト
 * @return	true: 回文, false: 回文でない
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	ループが見つからない場合は @a 0 が返却される。
 * @note	計算量はO(n)となる。
 */
template<typename TYPE>
bool
CheckPalindrome(const Node<TYPE>* head)
{
	assert(head);

	const Node<TYPE>* tail = Node<int>::GetEndNode(head);

	while ('-') {
		if (head == tail) break;				// 長さが奇数
		if (head->get_next() == tail) break;	// 長さが偶数
		if (head->get_key() != tail->get_key()) return false;
		head = head->get_next();
		tail = tail->get_previous();
	}

	return true;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[][9] = {{1, 3, 5, 7, 9, 2, 4, 6, 8},
						   {1, 2, 4, 8, 16, 8, 4, 2, 1}};

	for (size_t i(0); i < sizeof(data)/sizeof(data[0]); ++i) {
		Node<int>* list = Node<int>::MakeList(data[i], sizeof(data[0])/sizeof(data[0][0]));

		Node<int>::Print(stdout, list);

		if (CheckPalindrome<int>(list)) {
			std::printf("palindrome.\n");
		}
		else {
			std::printf("not palindrome.\n");
		}

		Node<int>::DeleteList(list);
	}

	return 0;
}
