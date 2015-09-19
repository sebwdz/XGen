ABCD<
0 (
	set ( @AA 0 )
        add ( @AB 10 :CRTNB )
        sup ( @AB 0 add ( @AC 1 ) set ( @AB 4 ) )
        add ( @AD 10 )
        sup ( @AD 0 add ( @AE 2 ) set ( @AD 4 ) )
        sup ( @AD 0 sup ( @AE 0 add ( @AF 1 ) ) )
        set ( @AH 0 :CRTNB)
        add ( @BA 10 )
	set ( @X 10 )
	var (
		&x (
			type ( oth rpls mv )
			act ( @X @X )
			dst ( 80 )
			pw ( 50 )
		)
	)
	inf (  @HEAD 10 add ( @HEAD 1 ) new_head ( :CRT :XJJ ) )
)
>

XJJ<
0 (
	set ( @AA 0 )
        add ( @AB 10 :CRTNB )
        sup ( @AB 0 add ( @AC 1 ) set ( @AB 4 ) )
        add ( @AD 10 )
        sup ( @AD 0 add ( @AE 2 ) set ( @AD 4 ) )
        sup ( @AD 0 sup ( @AE 0 add ( @AF 1 ) ) )
        set ( @AH 0 :CRTNB)
        add ( @BA 10 )
)
>

CRT<
0 (
	set ( @AA 0 )
        add ( @AB 10 :CRTNB )
        sup ( @AB 0 add ( @AC 1 ) set ( @AB 4 ) )
        add ( @AD 10 )
        sup ( @AD 0 add ( @AE 2 ) set ( @AD 4 ) )
        sup ( @AD 0 sup ( @AE 0 add ( @AF 1 ) ) )
        set ( @AH 0 :CRTNB)
        add ( @BA 10 )
)
>

CRTX<
0 (
	sup ( @BC 0 add ( @BD 2 ) set ( @BC 4 ) :ABCD)
        sup ( @BD 0 sup ( @BC 0 add ( @BD 1 ) ) )
        add ( @BE 10 )
        set ( @BG 0 )
        add ( @BH 10 )
        sup ( @BH 0 add ( @BI 1 ) set ( @BH 4 :OTH :XJJ ) )
	var (
		&xf (
			type ( oth rpls mv )
			act ( @XEGJ @DND )
			dst ( 0909 )
			pw ( 2934 )
		)
	)
)
>

XKK<
0 (
	sup ( @BC 0 add ( @BD 2 ) set ( @BC 4 ) )
        sup ( @BD 0 sup ( @BC 0 add ( @BD 1 ) ) )
        add ( @BE 10 )
        set ( @BG 0 )
        add ( @BH 10 )
        sup ( @BH 0 add ( @BI 1 ) set ( @BH 4 ) )
        var (
                &xf (
                        type ( oth rpls mv )
                        act ( @XEGJ @DND )
                        dst ( 0909 )
                        pw ( 2934 )
                )
        )
)
>

CRTNB<
0 (
        sup ( @BH 0 add ( @BI 1 ) set ( @BH 4 inf ( @MYHEAD 10 add ( @MYHEAD 1 )
		creat ( :MAINNEXT :XKK ) ) ) )
        add ( @CA 10 )
        sup ( @CA 0 add ( @CB 2 ) set ( @CA 4 ) )
        sup ( @CA 0 sup ( @CB 0 add ( @CE 1 ) ) )
        add ( @CF 10 )
        set ( @CD 10 )
        add ( @EB 10 )
        sup ( @EB 0 add ( @EC 1 ) set ( @EB 4 ) )
        add ( @EX 10 )
	shared ( @SHARE )
	inf ( @SHARE 1
		set ( @SHARE 1 )
		duplic ()
	)
        sup ( @GX 0 add ( @YE 2 ) set ( @GX 4 ) :MAINNEXT )
     	use ( @JFF @IZHE @ZJJ @IERJFD @JJFLSD @JDNKSK @JKSLWJD @JDHSKDF @JDK )
)
>

MAIN<
0 (
	set ( @ADS 0 :ABCD )
	add ( @BFF 10 )
	add ( @XDML 10 )
	sup ( @XDML 0 add ( @YDDD 2 ) set ( @QX 4 ) :OTH )
	sup ( @XDML 0 sup ( @DDDDDDC 0 add ( @VX 1 ) ) )
	add ( @W 10 )
	set ( @A 0 )
        add ( @B 10 )
        set ( @AA 0 )
        add ( @AB 10 )
        sup ( @AB 0 add ( @AC 1 ) set ( @AB 4 ) :MAINNEXT )
        add ( @AD 10 )
        sup ( @BA 0 add ( @BB 1 ) set ( @BA 4 ) )
        add ( @BC 10 )
)
>

MAINNEXT<
0 (
        sup ( @BC 0 add ( @BD 2 ) set ( @BC 4 ) )
        sup ( @BD 0 sup ( @BC 0 add ( @BD 1 ) ) )
        add ( @BE 10 )
        set ( @BG 0 )
        add ( @BH 10 )
        sup ( @BH 0 add ( @BI 1 ) set ( @BH 4 ) )
        add ( @CA 10 )
        sup ( @CA 0 add ( @CB 2 ) set ( @CA 4 ) )
        sup ( @CA 0 sup ( @CB 0 add ( @CE 1 ) ) )
        add ( @CF 10 )
        set ( @CD 10 )
        add ( @EB 10 )
        sup ( @EB 0 add ( @EC 1 ) set ( @EB 4 ) @JJD )
	var (
		&KKLF (
			type ( oth chng atr )
			act ( @DJFJ @DJD )
			pw ( 140 )
			dst ( 89 )
		)
	)
)
>

OTH<
0 (
        add ( @EX 10 )
        add ( @WFD 10 )
        use ( @JFF @IZHE @ZJJ @IERJFD @JJFLSD @JDNKSK @JKSLWJD @JDHSKDF @JDK )
	use ( @JKDJK @JJDK @gdf @dgfg @dgfdkfh @sqret @tetzto @trietry )
	inf ( @NBCRT 2 add ( @NBCRT 1 ) creat ( :DAD ) creat ( :CRT ) )
)
>

DAD<
0 (
        add ( @X 10 )
        add ( @W 10 )
        set ( @A 0 )
        add ( @B 10 )
        sup ( @X 0 add ( @Y 2 ) set ( @X 4 ) )
        sup ( @C 0 sup ( @C 0 add ( @V 1 ) ) )
        add ( @W 10 )
        sup ( @B 0 add ( @C 1 ) set ( @B 4 ) )
        add ( @X 10 )
        sup ( @X 0 add ( @Y 2 ) set ( @X 4 ) )
        sup ( @C 0 sup ( @C 0 add ( @V 1 ) ) )
        add ( @W 10 )
	inf ( @CNB 2 new_head ( :CRT :MAINNEXT ) add ( @CNB 1 ) )
	use ( @JFKSJFNX @JFJFk @KLDOZJF @JFJFKORI @JJXKJF @JDJFKNFN @JFJKEK @JD )
)
>
