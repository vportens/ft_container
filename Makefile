NAME    =	vector

CLONE		= FOLDERTEST

EXIT = exit_file

.PHONY: all

all: | $(CLONE)
	cd $(CLONE) && ./do.sh && @true 

$(CLONE) :
	git clone https://github.com/mli42/containers_test $@


.PHONY: clean

clean:
	rm -rf $(CLONE)

.PHONY: fclean

fclean: clean
	rm -rf $(CLONE)

.PHONY: re
re: fclean all


