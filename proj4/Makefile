all: pow-create pow-check

.PHONY: pow-create pow-check
pow-create:
	gcc pow-create.c -o pow-create -lcrypto -lpthread

pow-check:
	gcc pow-check.c -o pow-check -lcrypto

clean:
	rm -f pow-create pow-check
