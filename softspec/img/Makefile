SRC = $(wildcard *.txt)
OUT = $(SRC:.txt=.png)

all: $(OUT)

%.png: %.txt
	plantuml $<

clean:
	rm *.png || true
