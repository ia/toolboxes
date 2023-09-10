#!/usr/bin/make -f

CFLAGS:=$(CFLAGS) -Wall -Wextra -Wl,--as-needed

all: compile library demo tests

tests: test-base64 test-aes test-rsa

compile: ssl_bio_base64.c ssl_bio_aes.c ssl_evp_aes.c
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_bio_base64.c -o ssl_bio_base64.o
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_bio_aes.c    -o ssl_bio_aes.o
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_evp_aes.c    -o ssl_evp_aes.o
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_rsa_pem.c    -o ssl_rsa_pem.o

library: compile
	$(CC) $(CFLAGS) $(LDFLAGS) ssl_bio_base64.o ssl_bio_aes.o ssl_evp_aes.o ssl_rsa_pem.o -shared -o libsslapi.so -lcrypto

demo: compile library
	$(CC) $(CFLAGS) $(LDFLAGS) sslapi.c -o sslapi -L. -lsslapi

test-base64:
	@echo
	@echo "BASE64 test:"
	@echo "===="
	LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH} ./sslapi bio_base64
	@echo "===="

test-aes:
	@echo
	@echo "AES test:"
	@echo "===="
	LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH} ./sslapi evp_aes
	openssl enc -d -aes-256-cbc -nosalt -in file.enc -out file.txt -k a && cat file.txt
	@echo "===="

test-rsa:
	@echo
	@echo "RSA test:"
	@echo "===="
	LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH} ./sslapi rsa_pem
	openssl rsautl -decrypt -inkey sec.pem -in file.bin -out plainfile.txt && cat plainfile.txt
	@echo "===="

clean:
	-rm -rf *.o
	-rm -rf *.so
	-rm -rf sslapi
	-rm -rf file.txt file.enc file.enc.txt file_.txt
	-rm -rf plainfile.txt file.bin
	-rm -rf file_ssl.txt pub.pem sec.pem

#.PHONY: all test clean
