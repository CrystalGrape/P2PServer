all:p2p.o p2p_node.o p2p_server.o
	g++ -o p2pserver p2p.o p2p_node.o p2p_server.o -I/opt/json/include -L/opt/json/lib -ljsoncpp
p2p.o:
	g++ -c p2p.cpp	-I/opt/json/include
p2p_node.o:
	g++ -c p2p_node.cpp -I/opt/json/include
p2p_server.o:
	g++ -c p2p_server.cpp -I/opt/json/include
clean:	
	-rm *.o
	-rm p2pserver
