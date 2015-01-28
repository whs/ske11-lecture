SRC = $(wildcard *.txt)
OUT = $(SRC:.txt=.png)

all: $(OUT)

%.png: %.txt
	erwiz $< $@

clean:
	rm *.png || true
