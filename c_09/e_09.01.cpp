/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_09.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第9章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <vector>

/**
 * フィボナッチ数字列の算出クラス
 * @note	テンプレートの型 @a TYPE は符号なし整数を指定すること。
 */
template<typename TYPE>
class FibonacciNumber
{
private:

	std::vector<TYPE> numbers_;	///< キャッシュ領域

public:

	/**
	 * コンストラクタ
	 */
	FibonacciNumber()
		{
			numbers_.push_back(0);
			numbers_.push_back(1);
		}

	/**
	 * フィボナッチ数を算出 (完全キャッシュ版DP)
	 */
	TYPE
	calculate(TYPE index)
		{
			if (numbers_.capacity() <= index + 1) {
				numbers_.reserve(index + 1);
			}

			size_t l;
			TYPE v;

			while ('-') {
				l = numbers_.size();
				if (index < l) break;
				v = numbers_[l-2] + numbers_[l-1];
				numbers_.push_back(v);
			}

			return numbers_[index];
		}

	/**
	 * フィボナッチ数を算出 (簡易版DP)
	 */
	static TYPE
	Calculate(TYPE index)
		{
			if (index < 0) return index;

			TYPE v(0);
			TYPE w(1);
			TYPE t;

			for (TYPE i(2); i < index; ++i) {
				t = v + w;
				v = w;
				w = t;
			}

			return v + w;
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t i = 1000000LU;
#ifndef	USE_CACHE
	size_t v = FibonacciNumber<size_t>::Calculate(i);
#else	// USE_CACHE
	FibonacciNumber<size_t> fib;
	size_t v = fib.calculate(i);
#endif	// USE_CACHE

	std::printf("%lu => %lG\n", i, (double)v);

	return 0;
}
