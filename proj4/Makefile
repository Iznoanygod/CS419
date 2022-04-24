all: pow-create pow-check

.PHONY: pow-create
pow-create:
	gcc pow-create.c -o pow-create -lcrypto -lpthread

pow-check:

clean:
	rm -f pow-create
