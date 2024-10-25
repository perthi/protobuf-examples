
CFLAGS = -Wall -Werror -g -O0


CSRC  = kf.c   # The main program
CSRC += kf.pb.c               
CSRC += pb_encode.c  
CSRC += pb_decode.c  
CSRC += pb_common.c  

INCLUDES= -I $(CURDIR)

PROTOC=protoc
PROTOC_OPTS= --plugin=protoc-gen-nanopb=protoc-gen-nanopb 


kf: $(CSRC)
	$(CC) $(CFLAGS) $(INCLUDES) -okf $(CSRC)



%.pb.c %.pb.h: %.proto $(wildcard %.options)
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. $<


.PHONY: clean
clean:
	@rm -f kf.pb.h kf.pb.c 
