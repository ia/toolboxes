#!/usr/bin/make -f

ant: ant-run

ant-run:
	ant run

bash: compile move jar

compile:
	echo " - compiling ..."
	cd src/example && javac *.java

move:
	echo " - moving files ..."
	-mkdir -p bin/example
	mv src/example/*.class bin/example/

jar:
	echo " - creating jar ..."
	cd bin/ && jar cfe demo.jar example.Main example

lib:
	echo " - creating lib ..."
	cd src/library && javac *.java
	-mkdir -p bin/library
	mv src/library/*.class bin/library
	cd bin/ && jar cf library.jar library

run:
	java -jar bin/demo.jar

run-lib:
	java -cp "bin/*" example.Main

clean:
	-ant clean
	-rm -rf bin/
