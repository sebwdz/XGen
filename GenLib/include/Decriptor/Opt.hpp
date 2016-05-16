#ifndef OPT_HPP
#define OPT_HPP

/* range parameter */

#define         OPT_RANGE       0
#define         OPT_CHAN_RANGE  0
#define         CHANNEL_RANGE   0
#define         VALUE_RANGE     0

/* Set opt */

#define         SET             78 + OPT_RANGE
#define         ADD             1 + OPT_RANGE
#define         SUB             2 + OPT_RANGE
#define         DIV             95 + OPT_RANGE
#define         MULT            96 + OPT_RANGE
#define         MOD             97 + OPT_RANGE

/* compare opt */

#define         SUP             3 + OPT_RANGE
#define         INF             4 + OPT_RANGE
#define         EGAL            5 + OPT_RANGE
#define         AND             22 + OPT_RANGE
#define         OR              23 + OPT_RANGE
#define         XOR             24 + OPT_RANGE
#define         NO              25 + OPT_RANGE
#define         WHILE           98 + OPT_RANGE

/* create module and detach decriptor */

#define         CREAT           6 + OPT_RANGE
#define         DETACH          7 + OPT_RANGE
#define         NEW_HEAD        17 + OPT_RANGE
#define         COPY            99 + OPT_RANGE
#define         CALL            94 + OPT_RANGE

/* use or unuse parameter */

#define         USE             8 + OPT_RANGE
#define         UNUSE           9 + OPT_RANGE

/* signals */

#define         ATTACH_INSTRU   60 + OPT_RANGE
#define         ATTACH          2 + OPT_RANGE
#define         FREE            59 + OPT_RANGE

#define         LINK            1 + OPT_RANGE
#define         COMIN           3 + OPT_RANGE
#define         TAKEOUT         14 + OPT_RANGE

#define         KILL            15 + OPT_RANGE
#define         DESTROY         18 + OPT_RANGE

#define         DUPLIC          16 + OPT_RANGE
#define         SPLIT           26 + OPT_RANGE
#define         SPLITIN         80 + OPT_RANGE

/* SHARE */

#define         SHARED          20 + OPT_RANGE
#define         UNSHARED        21 + OPT_RANGE

/* CHAN OPT */

#define         VAR             19 + OPT_RANGE
#define         REF             73 + OPT_RANGE
#define         DEREF           74 + OPT_RANGE
#define         SIZE            72 + OPT_RANGE
#define         RETURN          70 + OPT_RANGE
#define         POW             69 + OPT_RANGE
#define         RAND            68 + OPT_RANGE
#define         ERASE           67 + OPT_RANGE
#define         MOVE            65 + OPT_RANGE
#define         ROUND           64 + OPT_RANGE
#define         SQRT            63 + OPT_RANGE
#define         KEY_EXIST       62 + OPT_RANGE
#define         INCR            61 + OPT_RANGE
#define         DECR            75 + OPT_RANGE
#define         VAL             76 + OPT_RANGE
#define         CP_ONE          77 + OPT_RANGE
#define         NIL_INSTRU      222
#define         GEN             221

/* PROPRIETY */

#define         TO              1 + OPT_CHAN_RANGE
#define         OTH             0 + OPT_CHAN_RANGE

#define         MV              0 + OPT_CHAN_RANGE
#define         CHNG            1 + OPT_CHAN_RANGE

#define         ATR             0 + OPT_CHAN_RANGE
#define         RPLS            1 + OPT_CHAN_RANGE

#define         AUTO            0
#define         FIX             1
#define         PROP            1

#define         TYPE            3 + OPT_CHAN_RANGE

#define         ACT             3 + OPT_CHAN_RANGE
#define         DIR             6 + OPT_CHAN_RANGE
#define         PW              2 + OPT_CHAN_RANGE

#define         DST             0 + OPT_CHAN_RANGE
#define         MINDST          1 + OPT_CHAN_RANGE

#define         TARGET          5 + OPT_CHAN_RANGE
#define         REDUCE          7

#define         LIMIT           4
#define         SCOPE           2

#define         MANUAL          0


#define         SON             2
#define         PARENT          3
#define         NETWORK         4

/* OTHER */

#define         ECHO            32 + OPT_CHAN_RANGE

/* Node type */

#define         BLOCK                 0
#define         INSTRU                1
#define         GLOBAL_CHAN           2
#define         LOCAL_CHAN            3
#define         FAST_CHAN             4
#define         VALUE                 5
#define         EMPTY_CHAN            6
#define         INTERACTION           7

#define         FAST_SIZE   20

#endif // OPT_HPP
