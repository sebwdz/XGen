Init_Main<(
	shared ( /CellId )
	inf ( ( @S_IMSON 1 ) (
			set ( #ImMain 1 )
			shared ( /S_IMSON )
			set ( @S_IMSON 1 )
		) ( unshared ( /S_IMSON ) )
	)
)>

MAIN<(
	:Init ( :Init_Main )
	sup ( ( #ImMain 0 ) ( :Im_Main ) ( :Cell ) )
)>	

Im_Main<(
	inf ( ( #duplic 4 ) (
			:Cycle ( (
					add ( @CellId 1 )
					add ( #duplic 1 )
					duplic
			) 280 )
		) ( kill )
	)
)>


Init_Cell<(
	shared ( /CellId )
	
	set ( @ImCell 15 )
	set ( @ImDendriteBase 10 )

	:Make_Rpls_Mv ( &RplsOth ?to
			0 ( ?need ( @ImCell ) )
			( ?need ( @ImCell @ImAttach ) )
	)
	set ( &RplsOth^?pw 10 )
	set ( &RplsOth^?dst 10 )
	cp ( &RplsOth^?scope ?scope ( ?oth ) )

	cp ( &AtrByOth 0 (
			300 100 10
			?act ( ( ?need ( @ImCell ) ) ( ?need ( @ImCell ) ) )
			?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)

	cp ( &GivePrimary 0 (
			200 0 500
			?act ( ( ?need ( @Primary ) ) ( ?need ( @ImDendriteHead ) ?forbiden ( @SalPrimary ) ) )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
)>

Create_Dendrite<(
	inf ( ( @IM_ACTOR 1 ) (
			:Cycle_S ( !dendrite !time new_head ( :Dendrite ) 400 2 )
		)
	)
)>

Cell<(
	:Init ( :Init_Cell )
	:Nucleus ( )
	:Create_Dendrite ( )
	inf ( ( &RplsOth^?dst 80 ) ( add ( &RplsOth^?dst 1 ) ) )	
)>
