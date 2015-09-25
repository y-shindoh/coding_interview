/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  C++で、仮想関数はどのように動作しますか?
 */

#include <cstddef>
#include <cstdio>

class Parent
{
public:

	virtual
	~Parent()
		{
			;
		}

	virtual void
	method_1() const
		{
			std::printf("method_1 in Parent\n");
		}

	void
	method_2() const
		{
			std::printf("method_2 in Parent\n");
		}
};

class Child : public Parent
{
public:

	~Child()
		{
			;
		}

	void
	method_1() const
		{
			std::printf("method_1 in Child\n");
		}

	void
	method_2() const
		{
			std::printf("method_2 in Child\n");
		}
};

class GroundChild : public Child
{
public:

	~GroundChild()
		{
			;
		}

	void
	method_1() const
		{
			std::printf("method_1 in GroundChild\n");
		}

	void
	method_2() const
		{
			std::printf("method_2 in GroundChild\n");
		}
};

int
main()
{
	Parent* p = new Child;
	Child* c = new GroundChild;

	p->method_1();	// 仮想関数テーブルにより子クラスのメソッドを呼ぶ
	p->method_2();	// 親クラスのメソッドを呼ぶ
	c->method_1();	// 仮想関数テーブルにより子クラスのメソッドを呼ぶ
	c->method_2();	// 親クラスのメソッドを呼ぶ

	delete p;
	delete c;

	return 0;
}
