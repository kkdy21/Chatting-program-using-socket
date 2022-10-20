sock.o : sock.h sock.cpp
	g++ -c sock.cpp

addr.o : addr.h addr.cpp
	g++ -c addr.cpp

time.o : time.h time.cpp
	g++ -c time.cpp

FD_func.o : FD_func.h FD_func.cpp
	g++ -c FD_func.cpp

Select.o : Select.h Select.cpp 
	g++ -c Select.cpp

servermain.o : servermain.h servermain.cpp recv.h send.h useroverlap.h
	g++ -c servermain.cpp

servsock.o : servsock.h servsock.cpp
	g++ -c servsock.cpp

serv.o : servermain.h serv.cpp
	g++ -c serv.cpp

useroverlap.o : useroverlap.cpp useroverlap.h
	g++ -c useroverlap.cpp


start : sock.o addr.o time.o FD_func.o Select.o servermain.o servsock.o serv.o  useroverlap.o
	g++ -o start sock.o addr.o time.o FD_func.o Select.o servermain.o servsock.o serv.o useroverlap.o
