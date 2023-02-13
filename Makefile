ok := all: ok
bok := backend: ok
fok := frontend: ok
clok := clean: ok

all: backend frontend
	@echo ${ok}

backend:
	@cd backend_parser && $(MAKE) 
	@echo ${bok}

frontend: lex.yy.c y.tab.c
	@gcc -fstack-protector-all -o frontend y.tab.c lex.yy.c modules/utility.c modules/syntaxTree.c modules/symbolTable.c modules/codegen.c
	@echo ${fok}

y.tab.c: structfe.y
	@yacc -d structfe.y

lex.yy.c: ANSI-C.l
	@lex ANSI-C.l
	
clean:
	@rm -f y.tab.c y.tab.h lex.yy.c
	@rm -f backend_parser/y.tab.c backend_parser/y.tab.h backend_parser/lex.yy.c
	@echo ${clok}
clean-all: clean
	@rm -f backend
	@rm -f frontend
