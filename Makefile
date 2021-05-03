tinyc.out: tinyc.s
	gcc -o tinyc.out tinyc.s

tinyc.s: a.out
	./a.out example2.c

a.out: lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -o a.out

y.tab.c:
	yacc -d -v tinyc.yacc

lex.yy.c:
	flex tinyc.lex

clean:
	rm -f a.out lex.yy.c y.tab.c y.tab.h y.output tinyc.s tinyc.out