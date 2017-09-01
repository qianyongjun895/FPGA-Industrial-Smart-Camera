PROJECT=libSsznAlg.so

#include path
IDIR=../../include
CC=arm-linux-gnueabihf-gcc

#lib path
LIBPATH =../../lib/sszn
LIBINSTALL =../../install/lib
#libs name
LIBS= -L. -lpthread -lm -ldl
CFLAGES=  -I$(IDIR) -I$(IMONKEYSTRUCT) -I$(ILIB) -L$(LIBPATH) -g -fPIC -shared
DIRS=.
FILES=$(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS=$(patsubst %.c,%.o,$(FILES))

$(PROJECT): $(OBJS)
	@echo CC -o $(PROJECT) $(OBJS) $(CFLAGES) $(LIBS)
	@$(CC) -O2 -o $(PROJECT) $(OBJS) $(CFLAGES) $(LIBS) 
	cp $(PROJECT) $(LIBPATH)
	cp $(PROJECT) $(LIBINSTALL)
$(OBJS):%.o:%.c	
	@echo CC -c $(CFLAGES) $< -o $@ 
	@$(CC) -c $(CFLAGES) $< -o $@
clean:	
	rm $(PROJECT) $(OBJS)
