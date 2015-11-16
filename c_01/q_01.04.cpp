/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  文字列内に出現するすべての空白文字を "%20" で置き換えるメソッドを書いてください。
  ただし、文字列の後ろには新たに文字を追加するためのスペースが十分にある
  (バッファのサイズは気にしなくてもよい) ことと、
  その追加スペースを除いた文字列の真の長さが与えられます

  例:
  入力: "Mr John Smith"
  出力: "Mr%20John%20Smith"
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * 文字列中に文字「 」が出現した回数を算出
 * @param[in]	s	処理対象の文字列
 * @return	文字「 」が出現した回数
 * @note	処理対象は US-ASCII および UTF-8。
 * @note	計算量は O(n)。ただし n は引数 @a s の長さ。
 */
size_t
count_ws(const char* s)
{
	assert(s);

	size_t n(0);

	while (*s) {
		if (*s++ != ' ') continue;
		++n;
	}

	return n;
}

/**
 * 文字列中の文字「 」を指定文字列に置換
 * @param[in,out]	s	置換対象の文字列
 * @param[in]	r	置換に用いる文字列
 * @note	処理対象は US-ASCII および UTF-8。
 * @note	最悪計算量は O(mn)。ただし m と n はそれぞれ引数 @a s と @a r の長さ。
 */
void
replace_ws(char* s,
		   const char* r)
{
	assert(s);
	assert(r);

	const int l = (int)std::strlen(r);
	int i = (int)std::strlen(s);
	int j = i + (l - 1) * (int)count_ws(s);

	while (0 <= i) {
		if (s[i] != ' ') {
			s[j] = s[i];
			--j;
		}
		else {
			for (int h(l-1); 0 <= h; --h) {
				s[j] = r[h];
				--j;
			}
		}
		--i;
	}

	assert(i == j);
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char buffer[1024] = "012 34 5 6789.";

	printf("BEFORE:\t'%s'\n", buffer);
	replace_ws(buffer, "%20");
	printf("AFTER:\t'%s'\n", buffer);

	return 0;
}
