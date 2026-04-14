f?=helloworld
rb?=n

all: _init _build _run

_init:
	@if [ "$(rb)" = "s" ]; then \
		rm -rf build; \
	fi
	mkdir -p build

_build:
	cd build && cmake -DEPR_EXEC_NAME=executable -DEPR_EXAMPLE_NAME=$(f) .. && make

_run:
	cd build && ./executable