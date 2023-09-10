#!/usr/bin/env make

CFLAGS  += -g3 -ggdb3 -Wall -Wextra
LDFLAGS += -g3 -ggdb3 -lc

BIN := demo_printf demo_malloc

demo: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

dbg: demo
	gdb demo_printf

dbg_env: pre-dbg.sh
	./pre-dbg.sh

clean:
	-rm -f $(BIN)

