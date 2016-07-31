LIB = -lpthread -lmysqlclient
.PHONY:all
all:p2p.o p2p_node.o p2p_server.o p2p_msg.o p2p_handle.o p2p_parse.o p2p_nodemap.o sql.o
	g++ -o p2pserver $^ -ljsoncpp $(LIB)
p2p.o:
	g++ -c p2p.cpp
p2p_node.o:
	g++ -c p2p_node.cpp
p2p_server.o:
	g++ -c p2p_server.cpp
p2p_msg.o:
	g++ -c p2p_msg.cpp
p2p_handle.o:
	g++ -c p2p_handle.cpp
p2p_parse.o:
	g++ -c p2p_parse.cpp
p2p_nodemap.o:
	g++ -c p2p_nodemap.cpp
sql.o:
	g++ -c sql.cpp
.PHONY:clean
clean:	
	-rm *.o
	-rm p2pserver
