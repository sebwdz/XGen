Init_Test<(
	set ( @ImFree 10 )

	cp ( &AtrCell 0 (
			160 10 600
			?act ( ( ?need ( @ImFree ) ) ( ?need ( @ImCell ) ) )
			?mv ?oth ?atr
			?reduce 0 ?scope ( ?oth )
		)
	)
	cp ( &GiveFree 0 (
			20 0 50
			?act ( ( ?need ( @ImFree ) ) ( ?need ( @ImCell ) ) )
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
			100 0 200
			?act ( ( ?need ( @ImAttach ) ) ( ?need ( @ImCell ) ) )
			?mv ?oth ?atr
			?reduce 0 ?scope ( ?parent )
		)
	)
	cp ( &GiveImpulse 0 (
			20 0 400
			?act ( ( ?need ( @Impulse ) ) ( ?need ( @IsNegNucleus ) ) )
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
	inf ( ( &CominCell^?limit^0  1 ) (
			:Init ( (
				set ( &CominCell^?dst 0 )
				cp ( &GiveType 0 (
						20 0 50
						?act ( ( ?need ( @ ) ) ( ?need ( @ImCell ) ) )
						?chng ?to ?atr
						?reduce ( ?fix ) 0 ?scope ( ?parent )
					)
				)
				sup ( ( @IM_SENSOR 0 ) (
						cp ( &GiveType^?act^0^?need^0^0 /IM_SENSOR )
					) ( cp ( &GiveType^?act^0^?need^0^0 /IM_ACTOR ) )
				)
			) )
		)
	)
		
)>
