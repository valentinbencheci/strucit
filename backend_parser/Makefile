backend: y.tab.c lex.yy.c
	@gcc -fstack-protector-all -o ../backend y.tab.c lex.yy.c

y.tab.c: structbe.y
	@yacc -d structbe.y

lex.yy.c: b.l
	@lex b.l