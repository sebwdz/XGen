MAIN<
(
   	:Cycle ( #duplic #time3 creat ( :Main_Cell ) 50 5 )
)
>

Main_Cell<
(
	:Cycle ( #crt1 #time1 new_head ( :CELL_1 ) 30 4 )
	:Cycle ( #crt2 #time2 new_head ( :CELL_2 ) 20 1 )

	and (
		0 (
			sup ( ( #crt1 29 ) )
			sup ( ( #crt2 19 ) )
		)
		kill
	)
)
>

CELL_1<
(
	:Init ( #init :Init_Cell1 )
)
>

CELL_2<
(
	:Init ( #init :Init_Cell2 )
)
>

Init_Cell1<
(
	set ( @ImCell 40 )

        :Make_Rpls_Mv ( &Rpls oth @ImCell @ImCell )
        :Init_Prop_Chan ( &Rpls 10 10 )
)
>

Init_Cell2<
(
	set ( @Impulse 10 @ImMaster 10 )

	:Make_Atr_Mv ( &AtrC oth @ImMaster @ImCell )
	:Init_Prop_Chan ( &AtrC 15 40 )

	:Make_Rpls_Mv ( &Rpls oth @ImMaster @ImMaster )
	:Init_Prop_Chan ( &Rpls 10 20 )

	:Make_Rpls_Mv ( &RplsCell1 oth @ImMaster @ImCell )
	:Init_Prop_Chan ( &RplsCell1 10 10 )

	:Make_Atr_Mv ( &Atr to @ImMaster @impulseStk )
        :Init_Prop_Chan ( &Atr 4 50 )
[	take_out ( )]
)
>
