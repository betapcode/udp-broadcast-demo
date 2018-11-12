LINK=g++

all: client server

client: client.cpp
	$(LINK) client.cpp -o client

server: server.cpp
	$(LINK) server.cpp -o server

clean:
	rm -rf client server