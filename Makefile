NAME=script
INPUT=pam_${NAME}.c
OUTPUT=pam_${NAME}.so

all:
	gcc -fPIC -DPIC -shared -rdynamic -o ${OUTPUT} ${INPUT}

clean:
	rm ${OUTPUT}

install:
	cp ${OUTPUT} /lib/security/${OUTPUT}
	cp script /etc/security/script
	cp scriptconf.py /etc/security/scriptconf.py
	chmod 755 /etc/security/script
	chmod 755 /etc/security/scriptconf.py
