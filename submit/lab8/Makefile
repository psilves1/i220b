<<<<<<< HEAD
DOC =		lab8

HOME_DIR =	../..

TEMPLATE_DIR =  $(HOME_DIR)/assets/umt

TARGETS = 	$(DOC).html $(DOC).pdf

all:		$(TARGETS)

.PHONY:		clean
clean:
		rm -rf *~ $(DOC) $(TARGETS) *.toc *.snm *.nav

%.html:		%.umt
		umt -D HOME=$(HOME_DIR) \
		  $(TEMPLATE_DIR)/article-template.html $< $@

%.pdf:		%.umt
		umt -D HOME=$(HOME_DIR) \
		  $(TEMPLATE_DIR)/article-template.tex $< $@

.PHONY:		files-clean
files-clean:
		for d in files/* ; \
		do \
		  if [ -d "$$d" -a -f "$$d/Makefile" ] ; \
		  then \
		    ( cd $$d; make clean ); \
		  fi \
		done
=======
CFLAGS = -g -Wall -std=c11

TARGET = hello

all:		$(TARGET)

.PHONY:		clean
clean:
		rm -f *.o 
>>>>>>> 0ab41f804029c8053ff3d234b81e497065f8e949

