/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "list.hpp"

/**
 * リストを並び替え (引数 @a key より小さいものを前方に、それ以外を後方に置く)
 * @param[in]	node	削除対象の要素 (リストの先頭と末尾を除く)
 * @param[in]	key	並び替えの条件
 * @return	並び替えたリスト
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	計算量はO(n)となる。
 */
template<typename TYPE>
Node<TYPE>*
RestructureList(Node<TYPE>* node,
				const TYPE& key)
{
	assert(node);

	Node<TYPE>* first(0);
	Node<TYPE>* second(0);
	Node<TYPE>* last_f(0);
	Node<TYPE>* last_s(0);

	while (node) {
		if (node->get_key() < key) {
			if (!first) {
				first = node;
				last_f = node;
			}
			else {
				last_f->set_next(node);
				last_f = node;
			}
		}
		else {
			if (!second) {
				second = node;
				last_s = node;
			}
			else {
				last_s->set_next(node);
				last_s = node;
			}
		}
		node = node->get_next();
	}

	if (first) {
		last_f->set_next(second);
		if (last_s) last_s->set_next(0);
		return first;
	}
	else {
		return second;
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};
	int devisor[] = {5, 3, 0, 10};
	Node<int>* list = Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));

	Node<int>::Print(stdout, list);

	for (size_t i(0); i < sizeof(devisor)/sizeof(devisor[0]); ++i) {
		std::printf("devisor: %d\n", devisor[i]);
		list = RestructureList<int>(list, devisor[i]);
		Node<int>::Print(stdout, list);
	}

	Node<int>::DeleteList(list);

	return 0;
}
