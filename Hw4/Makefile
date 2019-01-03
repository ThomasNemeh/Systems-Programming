all: freq encode_bits decode_bits todecimal tobinary tooctal tohex

freq: freq.c
	gccx -o freq freq.c

encode_bits: encode_bits.c
	gccx -o encode_bits encode_bits.c

decode_bits: decode_bits.c
	gccx -o decode_bits decode_bits.c

todecimal: todecimal.c
	gccx -o todecimal todecimal.c

tobinary: tobinary.c
	gccx -o tobinary tobinary.c

tooctal: tooctal.c
	gccx -o tooctal tooctal.c

tohex: tohex.c
	gccx -o tohex tohex.c

clean:
	rm -f freq bits encode_bits decode_bits todecimal tobinary tooctal tohex

