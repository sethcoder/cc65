;
; Ullrich von Bassewitz, 21.06.2002
;
; unsigned char __fastcall__ tgi_getpixel (int x, int y);
; /* Get the color value of a pixel */


        .include        "tgi-kernel.inc"

        .export         _tgi_getpixel

_tgi_getpixel:
        jsr     tgi_getset      ; Pop args, check range
        bcs     @L9
        jmp     tgi_getpixel    ; Call the driver
@L9:    rts


