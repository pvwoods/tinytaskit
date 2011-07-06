default: tinytaskit

install: tinytaskit
	cp tinytaskit /usr/local/bin

tinytaskit:
	gcc -o tinytaskit main.c -I/opt/local/include -L/opt/local/lib -lsha1
