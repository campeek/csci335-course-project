TEST    START   1000
FIRST   LDA     #5
        STA     VALUE
        LDA     #10
        ADD     VALUE
        STA     RESULT
        RSUB
VALUE   RESW    1
RESULT  RESW    1
        END     FIRST
