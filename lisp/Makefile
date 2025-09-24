# ---- config ----
SBCL_SRC ?= $(CURDIR)/sbcl-source
CC ?= gcc

.PHONY: all clean stage

all: simwrap.dll

# Build the SBCL core via ASDF
sim.core: sim-core.asd src/package.lisp src/core.lisp src/bindings.lisp build.lisp
	CL_SOURCE_REGISTRY="$(CURDIR)" \
	"$(SBCL_SRC)/run-sbcl.sh" --noinform --disable-debugger --load build.lisp --quit

libsbcl.so:
	cp "$(SBCL_SRC)/src/runtime/libsbcl.so" ./libsbcl.so

# Build the wrapper DLL (links against sbcl.dll import lib and zstd)
simwrap.o: simwrap.c
	$(CC) -O2 -Wall -c $< -o $@

simwrap.dll: simwrap.o sim.core libsbcl.so
	$(CC) -shared -o $@ simwrap.o "$(SBCL_SRC)/src/runtime/libsbcl.so" -lzstd

# Optional: copy runtime DLLs next to outputs for quick testing
# stage: $(DLL)
# 	-@cp "$(SBCL_SRC)/src/runtime/sbcl.dll" . 2>NUL || true
# 	-@cp /mingw64/bin/libzstd.dll . 2>NUL || true

clean:
	-@rm -f simwrap.dll simwrap.o sim.core
