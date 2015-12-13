#ifndef OPT_HPP
#define OPT_HPP

/* range parameter */

#define         OPT_RANGE       0
#define         OPT_CHAN_RANGE  0
#define         CHANNEL_RANGE   0
#define         VALUE_RANGE     0

/* Set opt */

#define         SET             0 + OPT_RANGE
#define         ADD             1 + OPT_RANGE
#define         SUB             2 + OPT_RANGE
#define         DIV             95 + OPT_RANGE
#define         MULT            96 + OPT_RANGE

/* compare opt */

#define         SUP             3 + OPT_RANGE
#define         INF             4 + OPT_RANGE
#define         EGAL            5 + OPT_RANGE
#define         AND             22 + OPT_RANGE
#define         OR              23 + OPT_RANGE
#define         XOR             24 + OPT_RANGE
#define         NO              25 + OPT_RANGE

/* create module and detach decriptor */

#define         CREAT           6 + OPT_RANGE
#define         DETACH          7 + OPT_RANGE
#define         NEW_HEAD        17 + OPT_RANGE

/* use or unuse parameter */

#define         USE             8 + OPT_RANGE
#define         UNUSE           9 + OPT_RANGE

/* signals */

#define         ATTACH          10 + OPT_RANGE
#define         FREE            11 + OPT_RANGE

#define         LINK            12 + OPT_RANGE
#define         COMIN           13 + OPT_RANGE
#define         TAKEOUT         14 + OPT_RANGE

#define         KILL            15 + OPT_RANGE
#define         DESTROY         18 + OPT_RANGE

#define         DUPLIC          16 + OPT_RANGE
#define         SPLIT           26 + OPT_RANGE

/* SHARE */

#define         SHARED          20 + OPT_RANGE
#define         UNSHARED        21 + OPT_RANGE

/* CHAN OPT */

#define         VAR             19 + OPT_RANGE

/* PROPRIETY */

#define         TO              6 + OPT_CHAN_RANGE
#define         OTH             7 + OPT_CHAN_RANGE
#define         MV              8 + OPT_CHAN_RANGE
#define         CHNG            9 + OPT_CHAN_RANGE
#define         TYPE            10 + OPT_CHAN_RANGE
#define         ACT             11 + OPT_CHAN_RANGE
#define         ATR             1 + OPT_CHAN_RANGE
#define         RPLS            2 + OPT_CHAN_RANGE

#define         PW              4 + OPT_CHAN_RANGE
#define         DST             5 + OPT_CHAN_RANGE
#define         MINDST          31 + OPT_CHAN_RANGE

/* Node type */

#define         BLOCK           0
#define         INSTRU          1
#define         GLOBAL_CHAN     2
#define         LOCAL_CHAN      3
#define         FAST_CHAN       4
#define         VALUE           5

#define         FAST_SIZE   20

#endif // OPT_HPP
