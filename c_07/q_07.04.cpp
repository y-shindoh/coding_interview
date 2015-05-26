/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_07.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題7.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>

/**
 * 整数の符号だけ変更
 * @param[in]	x	元の整数
 * @param[in]	negative	true: 負にする, false: 正にする
 * @return	符号を変更した整数
 * @note	テンプレートの型 @a TYPE は整数を指定すること。
 */
template<typename TYPE>
TYPE
change_sign(TYPE x,
			bool negative = false)
{
	TYPE v(0);

	if (!negative) {
		if (0 <= x) return x;
		for (TYPE i(x); i < 0; ++i) {
			v += 1;
		}
	}
	else {
		assert((TYPE)-1 < 0);	// 負を扱えない型
		if (x <= 0) return x;
		for (TYPE i(0); i < x; ++i) {
			v += -1;
		}
	}

	return v;
}

/**
 * 乗算
 * @param[in]	x	左の項
 * @param[in]	y	右の項
 * @return	積
 * @note	テンプレートの型 @a TYPE は整数を指定すること。
 */
template<typename TYPE>
TYPE
mul(TYPE x, TYPE y)
{
	TYPE v(0);

	if (0 <= y) {
		// yは0以上
		for (TYPE i(0); i < y; i += 1) {
			v += x;
		}
	}
	else if (0 <= x) {
		// xは0以上
		for (TYPE i(0); i < x; i += 1) {
			v += y;
		}
	}
	else {
		// x, yは負
		TYPE w = change_sign<TYPE>(x);
		for (TYPE i(y); i < 0; i += 1) {
			v += w;
		}
	}

	return v;
}

/**
 * 減算
 * @param[in]	x	左の項
 * @param[in]	y	右の項
 * @return	差
 * @note	テンプレートの型 @a TYPE は整数を指定すること。
 */
template<typename TYPE>
TYPE
sub(TYPE x, TYPE y)
{
	if (y < 0) return x + change_sign<TYPE>(y);	// yは負

	// yは0以上
	for (TYPE i(0); i < y; ++i) {
		x += -1;
	}

	return x;
}

/**
 * 除算
 * @param[in]	x	左の項
 * @param[in]	y	右の項
 * @return	商
 * @note	テンプレートの型 @a TYPE は整数を指定すること。
 * @note	振る舞いをRubyの整数の除算と等しくした。
 */
template<typename TYPE>
TYPE
div(TYPE x, TYPE y)
{
	assert(y);

	TYPE v(0);
	TYPE s;

	if (0 <= x) {
		if (0 <= y) {
			// x, yは0以上
			while (y <= x) {
				for (TYPE i(0); i < y; ++i) {
					x += -1;
				}
				v += 1;
			}
		}
		else {
			// xは0以上, yは負
			do {
				x += y;
				v += -1;
			} while (0 < x);
		}
	}
	else {
		if (0 <= y) {
			// xは負, yは0以上
			x = change_sign<TYPE>(x);
			s = change_sign<TYPE>(y, true);
			do {
				x += s;
				v += -1;
			} while (0 < x);
		}
		else {
			// x, yは負
			x = change_sign<TYPE>(x);
			s = change_sign<TYPE>(y);
			while (s <= x) {
				x += y;
				v += 1;
			}
		}
	}

	return v;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int x(5), y(-3);
	int v;

	v = mul<int>(x, y);
	std::printf("%d * %d = %d\n", x, y, v);

	v = sub<int>(x, y);
	std::printf("%d - %d = %d\n", x, y, v);

	v = div<int>(x, y);
	std::printf("%d / %d = %d\n", x, y, v);

	return 0;
}
