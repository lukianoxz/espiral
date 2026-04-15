# executable name
e?=executable
# file name
f?=helloworld
# rebuild
rb?=n
# clear build message
cls?=s

all: _init _build _run

_init:
	@if [ "$(rb)" = "s" ]; then \
		rm -rf build; \
	fi
	@mkdir -p build

_build:
	cd build && cmake -DEPR_EXEC_NAME=$(e) -DEPR_EXAMPLE_NAME=$(f) .. && make

_run:
	@if [ "$(cls)" = "s" ]; then \
		clear; \
	fi

	@cd build && ./$(e)