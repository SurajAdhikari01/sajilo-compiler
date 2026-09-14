all:	build install


configure:
	@cmake -B build


build:	configure
	@cmake --build build


install:
	@sudo cmake --install build


test: all
	@cd ../language && sajilo testfunc && sajilo test
