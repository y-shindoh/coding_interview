/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "list.hpp"

/**
 * リストから数値を生成
 * @param[in]	node	処理対象のリスト (すべての要素は1桁)
 * @param[in]	from_high	リストの並び (true: 上位桁から, false: 下位桁から)
 * @return	生成した数値
 * @note	テンプレートの型 @a TYPE はリストのキーの型。整数型。
 * @note	計算量はO(n)となる。
 */
template<typename TYPE>
TYPE
MakeNumberFromList(const Node<TYPE>* node,
				   bool from_high = true)
{
	assert(node);

	TYPE value((TYPE)0);

	if (from_high) {
		while (node) {
			assert(node->get_key() < (TYPE)10);
			value *= (TYPE)10;
			value += node->get_key();
			node = node->get_next();
		}
	}
	else {
		TYPE times((TYPE)1);
		while (node) {
			assert(node->get_key() < (TYPE)10);
			value += node->get_key() * times;
			node = node->get_next();
			times *= (TYPE)10;
		}
	}

	return value;
}

/**
 * 数値からリストを生成
 * @param[in]	number	処理対象の0以上の数値
 * @param[in]	from_high	リストの並び (true: 上位桁から, false: 下位桁から)
 * @return	生成したリスト
 * @note	テンプレートの型 @a TYPE はリストのキーの型。整数型。
 * @note	計算量はO(n)となる。ただしnは引数 @a number の桁数。
 */
template<typename TYPE>
Node<TYPE>*
MakeListFromNumber(TYPE number,
				   bool from_high = true)
{
	assert((TYPE)0 <= number);

	Node<TYPE>* head(0);
	Node<TYPE>* current(0);
	Node<TYPE>* other;
	TYPE key;

	while ('-') {
		key = number % (TYPE)10;
		other = current;
		current = new Node<TYPE>(key);
		if (from_high) {
			head = current;
			current->set_next(other);
		}
		else {
			if (!head) head = current;
			if (other) other->set_next(current);
		}
		if (number < (TYPE)10) break;
		number /= (TYPE)10;
	}

	return head;
}

/**
 * 数値を示す2つのリストから合計した数値を示すリストを生成
 * @param[in]	node_1	処理対象のリスト (すべての要素は1桁)
 * @param[in]	node_2	処理対象のリスト (すべての要素は1桁)
 * @param[in]	from_high	リストの並び (true: 上位桁から, false: 下位桁から)
 * @return	生成したリスト ([1, 2] + [4, 5] => [5, 7] or [7, 5]
 * @note	テンプレートの型 @a TYPE はリストのキーの型。整数型。
 * @note	計算量はO(n1+n2)となる。ただしn1とn2はそれぞれnode_1とnode_2の長さ。
 */
template<typename TYPE>
Node<TYPE>*
MakeNumberFrom2Lists(const Node<TYPE>* node_1,
					 const Node<TYPE>* node_2,
					 bool from_high = true)
{
	TYPE number_1 = MakeNumberFromList<TYPE>(node_1, from_high);
	TYPE number_2 = MakeNumberFromList<TYPE>(node_2, from_high);

	return MakeListFromNumber<TYPE>(number_1 + number_2, from_high);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data_1[] = {1, 3, 5, 7, 9};
	int data_2[] = {5, 3, 0, 5};
	Node<int>* list_1 = Node<int>::MakeList(data_1, sizeof(data_1)/sizeof(data_1[0]));
	Node<int>* list_2 = Node<int>::MakeList(data_2, sizeof(data_2)/sizeof(data_2[0]));
	Node<int>* list_3 = MakeNumberFrom2Lists<int>(list_1, list_2, true);	// 発展問題
	Node<int>* list_4 = MakeNumberFrom2Lists<int>(list_1, list_2, false);	// 通常問題

	Node<int>::Print(stdout, list_1);
	Node<int>::Print(stdout, list_2);
	Node<int>::Print(stdout, list_3);
	Node<int>::Print(stdout, list_4);

	Node<int>::DeleteList(list_1);
	Node<int>::DeleteList(list_2);
	Node<int>::DeleteList(list_3);
	Node<int>::DeleteList(list_4);

	return 0;
}
