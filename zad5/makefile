
DEPS=main.c studenci.c dziekanat.c

zad5: $(DEPS)
	cc $(DEPS) -o $@ -Wall --pedantic

%.o:%.c
	cc -c $^ -o $@


clean:
	rm -f zad5
	rm -f *.o

test: zad5
	./zad5 najtrudniejszy_przedmiot DANE.txt