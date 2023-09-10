
#include <stdio.h>

struct st {
	int j;
	int *i;
	char *string;
	int k;
};

struct st2 {
	int a;
	int *b;
	char c;
	char *s;
	struct st st1;
	struct st *st2ptr;
};

int ptr_chr(char **string)
{
	printf("ptr_chr ->\n");
	//printf("%s\n", string);
	*string = malloc(16);
	memset(*string, '0', 16);
	printf("0x%lX\t0x%X\n", *string, (char)*string);
	printf("ptr_chr <-\n");
	return 0;
}

int ptr_int(int *a)
{
	printf("ptr_int ->\n");
	int i = 16;
	*a = i;
	printf("ptr_int <-\n");
	return 0;
}

int ptr_st(struct st *s)
{
	//printf("%d\n", *s->i);
	//ptr(s->i);
	int c = 0;
	s->i = &c;
	printf("ptr_st ->\n");
	printf("s   addr: %x\n", s);
	printf("s.i addr: %x\n", &(s->i));
	
	//ptr( &(s->i) );
	
	ptr_int(s->i);
	ptr_chr(&(s->string));
	
	printf("s.s lval: %s\n", s->string);
	printf("s.i lval: %d\n", *s->i);
	
	printf("ptr_st <-\n");
	return 0;
}

int test()
{
	//int num = 10;
	
	struct st s;
	//s.i = &num;
	
	printf("s   addr: %x\n", &s);
	printf("s.i addr: %x\n", s.i);
	printf("s.i lval: %d\n", *s.i);
	
	ptr_st(&s);
	
	printf("s.i lval: %d\n", *s.i);
	
	
	int i = 0;
	for (i = 0; i < *s.i; i++) {
		printf("%.2x ", s.string[i]);
	}
	printf("\n");
	
	struct st2 st;

	return 0;
}

int main(int argc, char const* argv[])
{
	test();
	return 0;
}
