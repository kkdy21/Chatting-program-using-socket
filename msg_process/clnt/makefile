sock.o : sock.h sock.cpp
	g++ -c sock.cpp

addr.o : addr.h addr.cpp
	g++ -c addr.cpp

clntsock.o : clntsock.h clntsock.cpp
	g++ -c clntsock.cpp

clnt.o : clntmain.h clnt.cpp
	g++ -c clnt.cpp

clntmain.o : clntmain.h clntmain.cpp
	g++ -c clntmain.cpp

clntsend.o : clntsend.h clntsend.cpp
	g++ -c clntsend.cpp

clntrecv.o : clntrecv.h clntmain.cpp
	g++ -c clntrecv.cpp



start : sock.o addr.o clntsock.o clnt.o clntrecv.o clntsend.o clntmain.o
	g++ -o start sock.o addr.o clntsock.o clnt.o clntrecv.o clntsend.o clntmain.o