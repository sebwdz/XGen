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
	inf ( ( #duplic 19 ) (
			:Cycle ( (
					add ( @CellId 1 )
					add ( #duplic 1 )
					duplic
			) 80 )
		) ( kill )
	)
)>


Init_Cell<(
	shared ( /CellId )
	shared ( /IM_SENSOR )
	shared ( /IM_ACTOR )
	
	set ( @ImCell 15 )

	:Make_Rpls_Mv ( &RplsOth ?to
			0 ( ?need ( @ImCell ) )
			( ?need ( @ImCell ) )
	)
	set ( &RplsOth^?pw 180 )
	set ( &RplsOth^?dst 40 )
	cp ( &RplsOth^?scope ?scope ( ?oth ) )

	cp ( &GivePrimary 0 (
			200 0 500
			?act ( ( ?need ( @Primary ) ) ( ?need ( @ImDendriteHead ) ) )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
)>

Create_Dendrite<(
	inf ( ( @IM_ACTOR 1 ) (
			:Cycle_S ( !dendrite !time new_head ( :Dendrite ) 800 2 )
		)
	)
)>

Cell<(
	:Debug ( @Primary 67 )
	:Init ( :Init_Cell )
	:Nucleus ( )
	:Create_Dendrite ( )
	inf ( ( &RplsOth^?dst 50 ) ( add ( &RplsOth^?dst 0.01 ) ) )	
)>
