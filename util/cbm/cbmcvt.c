/* cbmcvt.c --  PetSCII <--> ISO-8859-1 Conversion Filter Tool */
/* 2010-09-06, Greg King */

#include <stdio.h>
#include <unistd.h>

/* Translation table ISO-8859-1 -> PetSCII */
static const unsigned char CTPET[256] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x14,0x09,0x0D,0x11,0x93,0x0A,0x0E,0x0F,
    0x10,0x0B,0x12,0x13,0x08,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
    0x40,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
    0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0x5B,0xBF,0x5D,0x5E,0xA4,
    0xAD,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0xB3,0xDD,0xAB,0xB1,0xDF,
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
    0x90,0x91,0x92,0x0C,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
    0xA0,0xA1,0xA2,0xA3,0x5F,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0x7D,0xAC,0x60,0xAE,0xAF,
    0xB0,0x7E,0xB2,0x7B,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0x5C,
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0xDC,0x7C,0xDE,0x7F,
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
};

static unsigned char CTISO[256];


int main (int argc, char *argv[]) {
    int C;
    size_t I = 0u;

    if (isatty(fileno(stdin))) {
	fputs("cbmcvt v2.1 -- Conversion Filter (stdin --> stdout)\n"
	      " -p  converts ISO-8859-1 to PetSCII\n"
	      " else, converts in other direction.\n", stderr);
	return 0;
	}
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'p') {
	while ((C = fgetc (stdin)) != EOF) {
	    fputc (CTPET[C], stdout);
	}
    } else {
	/* Create translation table PetSCII -> ISO-8859-1 */
	for (; I < sizeof CTPET; ++I) {
	    CTISO[CTPET[I]] = I;
	}

	while ((C = fgetc (stdin)) != EOF) {
	    fputc (CTISO[C], stdout);
	}
    }
    return 0;
}
