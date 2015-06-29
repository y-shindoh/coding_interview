/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>

class A
{
public:

	virtual
	~A()
		{
			;
		}

	virtual void
	function1()
		{
			std::printf("A::function1\n");
		}

	void
	function2()
		{
			std::printf("A::function2\n");
		}
};

class B : public A
{
public:

	~B()
		{
			;
		}

	void
	function1()
		{
			std::printf("B::function1\n");
		}

	void
	function2()
		{
			std::printf("B::function2\n");
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	A* object = new B;

	object->function1();	// B
	object->function2();	// A

	delete object;
}
