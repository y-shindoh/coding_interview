/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <set>
#include "list.hpp"

/**
 * リスト中の重複するキーのノードを削除
 * @param[in]	head	リストの先頭ノード
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	最悪計算量はO(n^2)となる。
 */
template<typename TYPE>
void
DeleteDuplicatedKeySlowly(Node<TYPE>* head)
{
	Node<TYPE>* current;
	Node<TYPE>* previous;
	Node<TYPE>* target;
	TYPE key;

	while (head) {
		key = head->get_key();
		current = head->get_next();
		previous = head;

		while (current) {
			target = 0;
			if (key == current->get_key()) target = current;
			if (!target) previous = current;
			current = current->get_next();
			if (target) {
				previous->set_next(current);
				delete target;
			}
		}

		head = head->get_next();
	}
}

/**
 * リスト中の重複するキーのノードを削除
 * @param[in]	head	リストの先頭ノード
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	最悪計算量はO(n log n)となる。
 */
template<typename TYPE>
void
DeleteDuplicatedKeyFast(Node<TYPE>* node)
{
	Node<TYPE>* previous(0);
	TYPE key;
	std::set<TYPE> used_keys;

	while (node) {
		key = node->get_key();
		if (used_keys.find(key) == used_keys.end()) {
			used_keys.insert(key);
			previous = node;
			node = node->get_next();
		}
		else {
			previous->set_next(node->get_next());
			delete node;
			node = previous->get_next();
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};

	Node<int>* list = Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::Print(stdout, list);
	DeleteDuplicatedKeySlowly<int>(list);
	Node<int>::Print(stdout, list);
	Node<int>::DeleteList(list);

	list = Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::Print(stdout, list);
	DeleteDuplicatedKeyFast<int>(list);
	Node<int>::Print(stdout, list);
	Node<int>::DeleteList(list);

	return 0;
}
