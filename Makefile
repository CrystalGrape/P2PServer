LIB = -lpthread
all:p2p.o p2p_node.o p2p_server.o p2p_msg.o p2p_handle.o p2p_parse.o
	g++ -o p2pserver $^ -I/opt/json/include -L/opt/json/lib -ljsoncpp $(LIB)
p2p.o:
	g++ -c p2p.cpp	-I/opt/json/include
p2p_node.o:
	g++ -c p2p_node.cpp -I/opt/json/include
p2p_server.o:
	g++ -c p2p_server.cpp -I/opt/json/include
p2p_msg.o:
	g++ -c p2p_msg.cpp -I/opt/json/include
p2p_handle.o:
	g++ -c p2p_handle.cpp -I/opt/json/include
p2p_parse.o:
	g++ -c p2p_parse.cpp -I/opt/json/include
clean:	
	-rm *.o
	-rm p2pserver
