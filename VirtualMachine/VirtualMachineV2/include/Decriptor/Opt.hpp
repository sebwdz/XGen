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

/* compare opt */

#define         SUP             3 + OPT_RANGE
#define         INF             4 + OPT_RANGE
#define         EGAL            5 + OPT_RANGE

/* create module and detach decriptor */

#define         CREAT           6 + OPT_RANGE   // object ( from node )
#define         DETACH          7 + OPT_RANGE   // object ( from node )
#define         NEW_HEAD        17 + OPT_RANGE  // module ( from node )

/* use or unuse parameter */

#define         USE             8 + OPT_RANGE
#define         UNUSE           9 + OPT_RANGE

/* signals */

#define         ATTACH          10 + OPT_RANGE // decriptor ( from NULL ) / module ( from decriptor )
#define         FREE            11 + OPT_RANGE // module ( from decriptor )

#define         LINK            12 + OPT_RANGE // module ( from NULL )
#define         UNLINK          13 + OPT_RANGE // module ( from NULL )

#define         KILL            15 + OPT_RANGE // module ( from object )
#define         DESTROY         18 + OPT_RANGE
#define         DUPLIC          16 + OPT_RANGE // decriptor ( from NULL ) / module ( from NULL )

/* jump X node */

#define         JMP             14 + OPT_RANGE

/* SHARE */

#define         SHARED          20 + OPT_RANGE
#define         UNSHARED        21 + OPT_RANGE

/* CHAN OPT */

#define         VAR             19 + OPT_RANGE

/* SET */

#define         ATR             1 + OPT_CHAN_RANGE
#define         RPLS            2 + OPT_CHAN_RANGE
#define         WGTH            3 + OPT_CHAN_RANGE

/* PROPRIETY */

#define         TO              6 + OPT_CHAN_RANGE
#define         OTH             7 + OPT_CHAN_RANGE
#define         MV              8 + OPT_CHAN_RANGE
#define         CHNG            9 + OPT_CHAN_RANGE
#define         TYPE            10 + OPT_CHAN_RANGE
#define         ACT            11 + OPT_CHAN_RANGE
#define         PW              4 + OPT_CHAN_RANGE
#define         DST             5 + OPT_CHAN_RANGE

/* constant */

#define         CREATE_CHANNEL  1 + CHANNEL_RANGE
#define         JMP_CHAN        CHANNEL_RANGE
#define         WEIGHT_CHAN     19 + CHANNEL_RANGE

/* Node type */

#define         INSTRU          0
#define         GLOBAL_CHAN     1
#define         LOCAL_CHAN      2
#define         DECRIPT_CHAN    3
#define         VALUE           4

#endif // OPT_HPP
