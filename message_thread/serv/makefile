sock.o : sock.h sock.cpp
	g++ -c sock.cpp

addr.o : addr.h addr.cpp
	g++ -c addr.cpp

servsock.o : servsock.h servsock.cpp
	g++ -c servsock.cpp

serv.o : servermain.h serv.cpp
	g++ -c serv.cpp

servermain.o : servermain.h recv.h servermain.cpp
	g++ -c servermain.cpp -lpthread

msgmain.o : msgmain.h send.h recv.h useroverlap.h sendmsg.h msgmain.cpp
	g++ -c msgmain.cpp

useroverlap.o : useroverlap.h useroverlap.cpp
	g++ -c useroverlap.cpp

sendmsg.o : sendmsg.h send.h sendmsg.cpp
	g++ -c sendmsg.cpp

# selecroom.o : selecroom.h recv.h send.h selecroom.cpp
# 	g++ -c selecroom.cpp

start : sock.o addr.o servsock.o servermain.o msgmain.o useroverlap.o sendmsg.o serv.o 
	g++ -o start sock.o addr.o servsock.o servermain.o msgmain.o useroverlap.o sendmsg.o serv.o -lpthread