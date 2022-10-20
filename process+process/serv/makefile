sock.o : sock.h sock.cpp
	g++ -c sock.cpp

addr.o : addr.h addr.cpp
	g++ -c addr.cpp

servsock.o : servsock.h servsock.cpp
	g++ -c servsock.cpp

servermain.o : servermain.h servermain.cpp useroverlap.h recv.h send.h
	g++ -c servermain.cpp
useroverlap.o : useroverlap.h useroverlap.cpp
	g++ -c useroverlap.cpp

serv.o : servermain.h serv.cpp
	g++ -c serv.cpp

start : sock.o addr.o servsock.o servermain.o serv.o useroverlap.o
	g++ -o start sock.o addr.o servsock.o servermain.o serv.o useroverlap.o