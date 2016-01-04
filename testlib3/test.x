Init_Test<(
	set ( @ImFree 10 )

	cp ( &AtrCell 0 (
			160 10 230
			?act ( @ImFree @ImCell )
			?mv ?oth ?atr
		)
	)

	:Make_Give_Chan ( &GiveFree @ImFree @ImCell )
	set ( &GiveFree^?pw 100 )
	set ( &GiveFree^?dst 20 )
	set ( &GiveFree^?reduc^0 ?fix )
)>

TEST<(
	:Init ( :Init_Test )
	:MainTest
)>

MainTest<(
	inf ( ( !attach 1 ) (
			inf ( ( @ImFree 5 ) ( set ( !attach 10 ) ) )
		) ( :Attach )
	)
)>

Init_Attach<(
	set ( @ImFree 0 )
	set ( @ImAttach 10 )

	cp ( &AtrCell 0 (
			20 5 10
			?act ( @ImAttach @ImCell )
			?mv ?oth ?atr
		)
	)
	cp ( &GiveImpulse 0 (
			20 0 200
			?act ( @Impulse @IsNegNucleus )
			?chng ?to ?atr
		)
	)

	:Make_Spe_Chan ( &CominCell @ImCell @Block ?comin 20 )
)>

Attach<(
		:Init ( :Init_Attach )
		:CycleL ( set ( &CominCell^?dst 0 ) 1 1 )
)>
