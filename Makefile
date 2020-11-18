CC = gcc
CFLAGS = -std=gnu99
HEADERS = error.h filter.h dns_serv.h dns_packet.h
ALL_FILES = error.h error.c filter.c filter.h server.c dns_serv.c dns_serv.h dns_packet.c dns_packet.h Makefile README.md manual.pdf
TARGET = server

.PHONY : all

all: dns

dns: $(TARGET).o error.o filter.o dns_serv.o dns_packet.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c $(HEADERS)
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
	tar -czvf xjavor20.tar.gz $(ALL_FILES)

clean:
	$(RM) *.o $(TARGET) *.out