all: server client

server: server.cpp
	g++ -o server `pkg-config --cflags --libs dbus-1` server.cpp

client: client.cpp
	g++ -o client `pkg-config --cflags --libs dbus-1` client.cpp

clean:
	rm client server
