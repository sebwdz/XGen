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
	inf ( ( #duplic 6 ) (
			:Cycle ( (
					add ( @CellId 1 )
					add ( #duplic 1 )
					duplic
			) 20 )
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
	set ( &RplsOth^?pw 50 )
	set ( &RplsOth^?dst 70 )
	cp ( &RplsOth^?scope ?scope ( ?oth ) )
)>

Create_Dendrite<(
	:Cycle_S ( !dendrite !time new_head ( :Dendrite ) 200 2 )
)>

Cell<(
	:Init ( :Init_Cell )
	:Nucleus ( )
	:Create_Dendrite ( )
)>
