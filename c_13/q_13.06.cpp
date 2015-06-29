/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>

class A
{
public:

	~A()
		{
			std::printf("Call the destructor of class A\n");
		}
};

class B : public A
{
public:

	~B()
		{
			std::printf("Call the destructor of class B\n");
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	A* object = new B;

	delete object;	// call the destructor of A! (occur memory leak!)
}
