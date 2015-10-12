MAIN<
0 (
	:Cycle ( #crt1 #time1 creat ( :CELL_1 ) 10 40 )
	:Cycle ( #crt2 #time2 creat ( :CELL_2 ) 40 80 )
	sup ( #crt1 39 sup ( #crt2 79 kill ) )
	set ( @ImMaster 10 )
	set ( @impulseStk 10 )
)
>

CELL_1<
0 (
	:Init ( #init :Init_Cell1 )
)
>

CELL_2<
0 (
	:Init ( #init :Init_Cell2 )
	:Cycle ( #kill #time kill 280 1 )
)
>

Init_Cell1<
0 (
	set ( @ImCell 10 )

        :Make_Rpls_Mv ( &Rpls oth @ImCell @ImCell )
        :Init_Prop_Chan ( &Rpls 10 30 )
)
>

Init_Cell2<
0 (
	set ( @Impulse 10 )
	set ( @ImMaster 10 )

	:Make_Atr_Mv ( &Atr oth @ImMaster @ImCell )
	:Init_Prop_Chan ( &Atr 10 100 )

	:Make_Rpls_Mv ( &Rpls oth @ImMaster @ImMaster )
	:Init_Prop_Chan ( &Rpls 3 50 )

	:Make_Rpls_Mv ( &RplsCell1 oth @ImMaster @ImCell )
	:Init_Prop_Chan ( &RplsCell1 15 20 )
)
>
