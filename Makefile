
.PHONY: all clean print uninstall lib src


all: lib src

lib:
	cd ./lib/ && $(MAKE)

src:
	$(MAKE) -C ./src/

install:
	$(MAKE) -C ./lib/ install

uninstall:
	$(MAKE) -C ./lib/ uninstall

clean:
	cd ./lib/ && $(MAKE) clean
	$(MAKE) clean -C ./src/