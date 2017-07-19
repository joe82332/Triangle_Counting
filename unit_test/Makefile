RM = rm -rf

SUB_DIR = $(shell ls -d */ )

all:
	@for dir in $(SUB_DIR) ; do cd $$dir ; make ; cd .. ; done

clean:
	@for dir in $(SUB_DIR) ; do cd $$dir ; make clean ; cd .. ; done

