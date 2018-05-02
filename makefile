MAKEFLAGS += --no-print-directory

CC	!= which clang-devel || which clang
CXX	!= which clang++-devel || which clang++
FORMAT	!= which clang-format-devel || which clang-format
SYSDBG	!= which lldb-devel || which lldb || which gdb

CONFIG	:= -DCMAKE_TOOLCHAIN_FILE=${VCPKG}/scripts/buildsystems/vcpkg.cmake
CONFIG	+= -DVCPKG_TARGET_TRIPLET=${VCPKG_DEFAULT_TRIPLET}
CONFIG	+= -DCMAKE_INSTALL_PREFIX=$(PWD)

PROJECT	!= grep "^project" CMakeLists.txt | cut -c9- | cut -d " " -f1 | tr "[:upper:]" "[:lower:]"
SOURCES	!= find src -type f -name '*.h' -or -name '*.cpp'

all: release

run: build/llvm/release/CMakeCache.txt
	@cd build/llvm/release && cmake --build . --target $(PROJECT) && ./$(PROJECT)

install: release
	@cmake --build build/llvm/release --target install

release: build/llvm/release/CMakeCache.txt $(SOURCES)
	@cmake --build build/llvm/release

build/llvm/release/CMakeCache.txt: CMakeLists.txt build/llvm/release
	@cd build/llvm/release && CC=$(CC) CXX=$(CXX) cmake -GNinja -DCMAKE_BUILD_TYPE=Release $(CONFIG) $(PWD)

build/llvm/release:
	@mkdir -p build/llvm/release

format:
	@$(FORMAT) -i $(SOURCES)

clean:
	@rm -rf build/llvm bin lib

.PHONY: all run install release format clean
