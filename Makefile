CXX=g++
CXXFLAGS=-I./memflow_lib/memflow-win32-ffi/ -I./memflow_lib/memflow-ffi/ -I/usr/include/freetype2 -I/usr/include/libpng16 -I/path/to/glew/include -L./memflow_lib/target/release -L/path/to/glew/lib -Wno-multichar
LIBS=-lm -Wl,--no-as-needed -ldl -lpthread -l:libmemflow_win32_ffi.a -lglfw -lGL -lfreetype -lGLEW -lglut


OUTDIR=./build
OBJDIR=$(OUTDIR)/obj

$(shell mkdir -p $(OBJDIR))
$(shell cp memflow_lib/memflow-qemu-procfs/target/release/libmemflow_qemu_procfs.so $(OUTDIR))

%.o: %.cpp
	$(CXX) -c -o $(OBJDIR)/$@ $< $(CXXFLAGS)

wt_dma: wt_dma.o memory.o 
	$(CXX) -o $(OUTDIR)/$@ $(OBJDIR)/wt_dma.o $(OBJDIR)/memory.o $(CXXFLAGS) $(LIBS)

.PHONY: all
all: wt_dma

.DEFAULT_GOAL := all

clean:
	rm -rf $(OUTDIR)
