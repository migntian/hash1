.PHONY:clean
main:hash.c
	gcc -o $@ $^
clean:
	rm main
