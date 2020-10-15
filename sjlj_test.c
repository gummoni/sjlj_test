// sjlj_test.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <setjmp.h>


static int func1();
static int func2();

#define CO_START(state) if (0 == state) {
#define YIELD(state, ret) state = __LINE__; return ret; } else if (__LINE__ == state) {
#define CO_END(state, ret) } state = 0; return ret;

static int state1;

int func1()
{
	CO_START(state1);

	printf("-1-");

	YIELD(state1, 1);

	printf("-2-");

	YIELD(state1, 1);

	printf("-3-");

	CO_END(state1, 2);
}


static jmp_buf jbuf2;

#define CO_START2(jb) if (0 != *jb) longjmp(jb, 1);
#define YIELD2(jb, ret) if (0 == setjmp(jb)) return ret;
#define CO_END2(jb, ret) *jb = 0; return ret;
int func2()
{
	CO_START2(jbuf2);

	printf("-A-");

	YIELD2(jbuf2, 1);

	printf("-B-");

	YIELD2(jbuf2, 1);

	printf("-C-");

	CO_END2(jbuf2, 2);
}


int main()
{
	for (;;) {
		func1();
		func2();
	}
}



