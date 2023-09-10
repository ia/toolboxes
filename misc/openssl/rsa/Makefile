#!/usr/bin/make -f

CFLAGS:=$(CFLAGS) -Wall -Wextra -Wl,--as-needed

all: rsa test

rsa: rsa-keygen.c rsa-demo.c
	$(CC) $(CFLAGS) $(LDFLAGS) rsa-keygen.c -o rsa-keygen -lcrypto
	$(CC) $(CFLAGS) $(LDFLAGS) rsa-demo.c   -o rsa-demo   -lcrypto

test:
	@echo " ==== "
	@echo "input: secret"
	@echo " ==== "
	@echo "secret" > file.txt
	./rsa-demo -g 4096
	./rsa-demo -c file.txt file.bin
	openssl rsautl -decrypt -inkey sec.pem -in file.bin -out file_ssl.txt
	@echo " ==== "
	@echo -n "output: "
	@cat file_ssl.txt
	@echo " ==== "

clean:
	-rm -f pub.pem sec.pem rsa-demo rsa-keygen file.txt file.bin file_ssl.txt

