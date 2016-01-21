Init_Main<(
	inf ( ( @S_IMSON 1 ) (
			set ( #ImMain 1 )
			shared ( /S_IMSON )
			set ( @S_IMSON 1 )
		) ( unshared ( /S_IMSON ) )
	)
)>

MAIN<(
	:Init ( :Init_Main )
	sup ( ( #ImMain 0 ) ( :Im_Main ) [ else ] ( :Cell ) )
)>	

Im_Main<(
	inf ( ( #duplic 6 ) (
			:Cycle ( (
					add ( #duplic 1 )
					duplic
			) 20 )
		) ( kill )
	)
)>

Init_Cell<(
	set ( @ImCell 10 )

	:Make_Rpls_Mv ( &RplsOth ?to @ImCell @ImCell )
	set ( &RplsOth^?pw 15 )
	set ( &RplsOth^?dst 60 )
	cp ( &RplsOth^?scope ?scope ( ?oth ) )
)>

Create_Dendrite<(
	:Cycle_S ( !dendrite !time creat ( :Dendrite ) 100 2 )
)>

Cell<(
	:Init ( :Init_Cell )
	:Nucleus ( )
	:Create_Dendrite ( )
)>
