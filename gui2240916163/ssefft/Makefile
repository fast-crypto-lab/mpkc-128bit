CC=    gcc
CXX=   g++
LD=    gcc

CFLAGS= -O3 -mavx2 -mpclmul -std=gnu99 -Wall -Wextra
CXXFLAGS= -O3 -mavx2 -mpclmul -Wall -Wextra -fno-exceptions -fno-rtti -nostdinc++
INCPATH= -I/usr/local/include -I/opt/local/include -I/usr/include
LDFLAGS= 
LIBPATH= -L/usr/local/lib -L/opt/local/lib -L/usr/lib
LIBS=    -lm -lcrypto


OBJ= blas.o gf16.o quartz_sig.o gui_gf2.o mq_gf2_n256_m224_sse.o tbl_gf256v_polymul_32.o
EXE= gui-test gui-benchmark

CSRC= $(wildcard *.cpp)


ifdef DEBUG
        CFLAGS+=  -D_DEBUG_ -g
        CXXFLAGS+= -D_DEBUG_ -g
endif

ifdef NO_SSE
	CFLAGS += -D_NO_SSE_
	CXXFLAGS += -D_NO_SSE_
endif


ifdef K
	CFLAGS += -DK=$(K)
	CXXFLAGS += -DK=$(K)
endif


ifdef AVX2
	CFLAGS += -mavx2 -D_USE_AVX2_
	CXXFLAGS += -mavx2 -D_USE_AVX2_
endif

ifdef AVX
	CFLAGS += -mavx -D_USE_AVX_
	CXXFLAGS += -mavx -D_USE_AVX_
endif

ifdef GPROF
	CFLAGS += -pg
	CXXFLAGS += -pg
	LDFLAGS += -pg
endif

.PHONY: all tests tables clean

all: $(OBJ) $(EXE)


%-test: $(OBJ) %-test.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)

%-benchmark: $(OBJ) %-benchmark.o
	$(LD) $(LDFLAGS) $(LIBPATH) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCPATH) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $<

tests:
	cd tests; make

tables:
	cd supplement; make

clean:
	rm *.o *-test *-benchmark
