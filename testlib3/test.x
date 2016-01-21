Init_Test<(
	set ( @ImFree 10 )

	cp ( &AtrCell 0 (
			160 10 230
			?act ( @ImFree @ImCell )
			?mv ?oth ?atr
			?reduce 0 ?scope ( ?oth )
		)
	)
	cp ( &GiveFree 0 (
			20 0 20
			?act ( @ImFree @ImCell )
			?chng ?to ?atr
			?reduce ( ?fix 0 ) 0 ?scope ( ?oth )
		)
	)
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
			?reduce 0 ?scope ( ?parent )
		)
	)
	cp ( &GiveImpulse 0 (
			20 0 200
			?act ( @Impulse @IsNegNucleus )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?parent )
		)
	)
	:Make_Link ( &CominCell @ImCell @Block 20 #comin )
	set ( &CominCell^?type ?comin )
	cp ( &CominCell^?scope 0 ( ?oth ) )
)>

Attach<(
		:Init ( :Init_Attach )
		sup ( ( #comin 0 ) (
				:Init ( (
					echo ( 65 10 )
					set ( &CominCell^?dst 0 )
				) )
			)
		)
)>
