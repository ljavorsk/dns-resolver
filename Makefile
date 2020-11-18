CC = gcc
CFLAGS = -std=gnu99
HEADERS = error.h filter.h dns_serv.h dns_packet.h
ALL_FILES = error.h error.c filter.c filter.h server.c dns_serv.c dns_serv.h dns_packet.c dns_packet.h Makefile README.md manual.pdf
TARGET = dns
TAR_NAME = xjavor20.tar

.PHONY : all

all: $(TARGET)

$(TARGET): server.o error.o filter.o dns_serv.o dns_packet.o
	$(CC) $(CFLAGS) -o $@ $^

server.o: server.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

error.o: error.c error.h
	$(CC) $(CFLAGS) -c $<

filter.o: filter.c filter.h
	$(CC) $(CFLAGS) -c $<

dns_serv.o: dns_serv.c dns_serv.h dns_packet.h error.h
	$(CC) $(CFLAGS) -c $<

dns_packet.o: dns_packet.c dns_packet.h filter.h
	$(CC) $(CFLAGS) -c $<

tar:
	tar -czvf $(TAR_NAME) $(ALL_FILES)

clean:
	$(RM) *.o $(TARGET) *.out