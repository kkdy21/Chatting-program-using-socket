sock.o : sock.h sock.cpp
	g++ -c sock.cpp

addr.o : addr.h addr.cpp
	g++ -c addr.cpp

clntsock.o : clntsock.h clntsock.cpp
	g++ -c clntsock.cpp

clntmain.o : clntmain.h send.h recv.h clntmain.cpp
	g++ -c clntmain.cpp -lpthread

clntsend.o : clntsend.h send.h clntsend.cpp
	g++ -c clntsend.cpp

clntrecv.o : clntrecv.h recv.h clntrecv.cpp
	g++ -c clntrecv.cpp

clnt.o : clntmain.h clnt.cpp
	g++ -c clnt.cpp 



start : sock.o addr.o clntsock.o clntsend.o clntrecv.o clntmain.o clnt.o 
	g++ -o start sock.o addr.o clntsock.o clntsend.o clntrecv.o clntmain.o clnt.o -lpthread