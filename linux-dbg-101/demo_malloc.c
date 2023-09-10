
#include <stdio.h>
#include <stdlib.h>

struct mm_buf {
	size_t size;
	unsigned char *buf;
};

struct mm_buf *mm_malloc(size_t size)
{
	struct mm_buf *mbuf = malloc(sizeof(struct mm_buf));
	if (!mbuf) {
		return NULL;
	}
	
	mbuf->buf = malloc(size);
	if (!mbuf->buf) {
		free(mbuf);
		return NULL;
	}
	
	mbuf->size = size;
	return (struct mm_buf *) mbuf;
}

void mm_free(struct mm_buf *mbuf)
{
	free(mbuf);
}

int main(int argc, const char *argv[])
{
	struct mm_buf *mbuf = mm_malloc(8);
	printf("size = %zd\n", mbuf->size);
	mm_free(mbuf);
	return 0;
}

