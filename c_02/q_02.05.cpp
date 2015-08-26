/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  各ノードの要素が1桁の数である連結リストで表された2つの数があります。
  一の位がリストの先頭になるように、各位の数は逆順に並んでいます。
  このとき2つの数の和を求め、それを連結リストで表したものを返す関数を書いてください。
 */

#include <cstddef>
#include <cstdio>
#include "list.hpp"

/**
 * digitのリストから整数を生成
 * @param[in]	node	digitのリスト
 * @param[in]	direction	リストの先頭が1の位か否か
 * @return	リストから生成した整数
 * @note	計算量は O(n)。ただし n は引数 @a node のノード数。
 */
template<typename TYPE>
size_t
List2Integer(const Node<TYPE>* node,
			 bool direction)
{
	size_t r(0);

	if (direction) {
		size_t b(1);
		while (node) {
			r += (size_t)node->get_data() * b;
			node = node->get_next();
			b *= 10;
		}
	}
	else {
		while (node) {
			r = r * 10 + (size_t)node->get_data();
			node = node->get_next();
		}
	}

	return r;
}

/**
 * 整数からdigitのリストを生成
 * @param[in]	number	整数
 * @param[in]	direction	リストの先頭が1の位か否か
 * @return	digitのリスト (呼び出し側で解放すること)
 * @note	計算量は O(n)。ただし n は引数 @a number の桁数。
 */
template<typename TYPE>
Node<TYPE>*
Integer2List(size_t number,
			 bool direction)
{
	Node<TYPE>* c(0);

	if (direction) {
		Node<TYPE>* p(0);
		Node<TYPE>* r(0);

		do {
			c = new Node<TYPE>(number % 10);
			if (p) p->set_next(c);
			if (!r) r = c;
			p = c;
			number /= 10;
		} while (0 < number);

		return r;
	}
	else {
		do {
			c = new Node<TYPE>(number % 10, c);
			number /= 10;
		} while (0 < number);

		return c;
	}
}

/**
 * digitのリスト2つから、その和を表すdigitのリストを生成
 * @param[in]	input_1	digitのリスト (その1)
 * @param[in]	input_2	digitのリスト (その2)
 * @param[in]	direction	リストの先頭が1の位か否か
 * @return	和を表すdigitのリスト
 * @note	計算量は O(n)。ただし n は引数 @a input_1 と @a input_2 のノード数の最大値。
 */
template<typename TYPE>
Node<TYPE>*
ListSum(const Node<TYPE>* input_1,
		const Node<TYPE>* input_2,
		bool direction = true)
{
	size_t n1 = List2Integer<TYPE>(input_1, direction);
	size_t n2 = List2Integer<TYPE>(input_2, direction);

	return Integer2List<TYPE>(n1 + n2, direction);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char data_1[] = {1, 3, 5};
	char data_2[] = {2, 4, 6};

	Node<char>* input_1 = Node<char>::MakeLinkedList(data_1, sizeof(data_1)/sizeof(data_1[0]));
	Node<char>* input_2 = Node<char>::MakeLinkedList(data_2, sizeof(data_2)/sizeof(data_2[0]));

	Node<char>::PrintLinkedList(input_1);
	Node<char>::PrintLinkedList(input_2);

	Node<char>* output = ListSum<char>(input_1, input_2, true);
	std::printf("=> ");
	Node<char>::PrintLinkedList(output);
	Node<char>::DeleteLinkedList(output);

	output = ListSum<char>(input_1, input_2, false);
	std::printf("=> ");
	Node<char>::PrintLinkedList(output);
	Node<char>::DeleteLinkedList(output);

	Node<char>::DeleteLinkedList(input_1);
	Node<char>::DeleteLinkedList(input_2);

	return 0;
}
