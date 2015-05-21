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
 * 回文チェッカー (双方向リストを利用)
 * @param[in]	head	処理対象のリスト
 * @return	true: 回文, false: 回文でない
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	ループが見つからない場合は @a 0 が返却される。
 * @note	計算量はO(n)となる。
 */
template<typename TYPE>
bool
CheckPalindrome1(const Node<TYPE>* head)
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
 * 回文チェッカー (単方向リストを利用)
 * @param[in]	head	処理対象のリスト
 * @return	true: 回文, false: 回文でない
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	ループが見つからない場合は @a 0 が返却される。
 * @note	計算量はO(n)となる。ノード生成するので少し効率が悪い。
 */
template<typename TYPE>
bool
CheckPalindrome2(const Node<TYPE>* head)
{
	assert(head);

	const Node<TYPE>* fast(head);
	const Node<TYPE>* slow(head);
	Node<TYPE>* reverse(0);	// スタックで表現しても良い

	while (fast) {	// リスト長が偶数
		fast = fast->get_next();
		if (!fast) {
			slow = slow->get_next();
			break;	// リスト長が奇数
		}
		fast = fast->get_next();
		reverse = new Node<TYPE>(slow->get_key(), 0, reverse);	// 単方向リスト扱い
		slow = slow->get_next();
	}

	Node<TYPE>* node(reverse);

	while (slow && node) {
		if (slow->get_key() != node->get_key()) break;
		slow = slow->get_next();
		node = node->get_next();
	}

	Node<TYPE>::DeleteList(reverse);

	return !node;
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

		if (CheckPalindrome1<int>(list)) {
			std::printf("palindrome.\n");
		}
		else {
			std::printf("not palindrome.\n");
		}

		if (CheckPalindrome2<int>(list)) {
			std::printf("palindrome.\n");
		}
		else {
			std::printf("not palindrome.\n");
		}

		Node<int>::DeleteList(list);
	}

	return 0;
}
