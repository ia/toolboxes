
#include <stdio.h>

/*
st s
s.j
s.k

st *s
s->j = 10

st s
s.i 
*s.i
*/
struct st {
	int j;
	int *i;
	char *string;
	int k;
};

/*
int ptr_chr2(char *string)
{
	string = malloc(10);
	memset(string, '0', 9);
	return 0;
}
*/
//int ptr_chr(long *string)
int ptr_chr(char **string)
{
	//printf("%s\n", string);
	*string = malloc(32);
	memset(*string, '0', 31);
	printf("0x%lX\t0x%X\n", *string, (char)*string);
	return 0;
}

int ptr(int *a)
{
	*a = 12;
	return 0;
}

int ptr_st(struct st *s)
{
	//printf("%d\n", *s->i);
	//ptr(s->i);
	printf("\nPTR\n");
	printf("ctx addr: %x\n", s);
	printf("ctx.clen addr: %x\n", &(s->i));
	//ptr( &(s->i) );
	ptr(s->i);
	ptr_chr(&(s->string));
	printf("%s\n", s->string);
	return 0;
}

int test()
{
	int num = 10;
	struct st s;
	s.i = &num;
	//char *str = "alsdkf";
	//s.string = str;
	printf("ctx addr: %x\n", &s);
	printf("ctx.clen addr: %x\n", s.i);
	printf("ctx.clen lval: %d\n", *s.i);

	ptr_st(&s);
	printf("%d\n", *s.i);

/*
	int a = 10;
	ptr(&a);
	printf("%d\n", a);
*/
	return 0;
}

int main(int argc, char const* argv[])
{
	test();
	/*
	struct st s;
	s.i = 10;
	ptr_st(&s);
	printf("%d\n", s.i);
	*/

	int a = 10;
	ptr(&a);
	printf("%d\n", a);

	int *b;
	*b = 20;
	printf("%d\n", *b);
	return 0;
}
