MAIN<
0 (
   	:Cycle ( #duplic #time3 creat ( :Main_Cell ) 50 10 )
)
>

Main_Cell<
0 (
	:Cycle ( #crt1 #time1 creat ( :CELL_1 ) 30 10 )
	:Cycle ( #crt2 #time2 creat ( :CELL_2 ) 20 5 )
	:Cycle ( #nucl #time3 creat ( :Nucleus ) 30 5 )

	and (
		0 (
			sup ( 0 ( #crt1 19 ) )
			sup ( 0 ( #crt2 4 ) )
		) 
		kill
	)
)
>

Nucleus<
0 (
	set ( @ImMaster 5 @impulseStk 5 )

        :Make_Rpls_Mv ( &Rpls to @impulseStk @impulseStk )
        :Init_Prop_Chan ( &Rpls 20 20 )
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
	:Make_Atr_Mv ( &Atr to @ImMaster @impulseStk )
	:Init_Prop_Chan ( &Atr 4 60 )
)
>

Init_Cell1<
0 (
	set ( @ImCell 40 )

        :Make_Rpls_Mv ( &Rpls oth @ImCell @ImCell )
        :Init_Prop_Chan ( &Rpls 10 30 )
)
>

Init_Cell2<
0 (
	set ( @Impulse 10 @ImMaster 10 )

	:Make_Atr_Mv ( &AtrC oth @ImMaster @ImCell )
	:Init_Prop_Chan ( &AtrC 15 30 )

	:Make_Rpls_Mv ( &Rpls oth @ImMaster @ImMaster )
	:Init_Prop_Chan ( &Rpls 7 20 )

	:Make_Rpls_Mv ( &RplsCell1 to @ImMaster @ImCell )
	:Init_Prop_Chan ( &RplsCell1 10 10 )
)
>
