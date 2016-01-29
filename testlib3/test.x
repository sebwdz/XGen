Init_Test<(
	set ( @ImFree 20 )

	cp ( &AtrCell 0 (
			90 0 60
			?act ( ( ?need ( @ImFree ) ) ( ?need ( @ImCell ) ?forbiden ( @ImFree ) ) )
			?mv ?oth ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &GiveFree 0 (
			10 0 50
			?act ( ( ?need ( @ImFree ) ) ( ?need ( @ImCell )) )
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

[	cp ( &AtrCell 0 (
			100 0 200
			?act ( ( ?need ( @ImAttach ) ) ( ?need ( @ImCell ) ) )
			?mv ?oth ?atr
			?reduce 0 ?scope ( ?parent )
		)
	)
]
	cp ( &GiveImpulse 0 (
			20 0 1000
			?act ( ( ?need ( @Impulse @Primary ) ) ( ?need ( @IsNegNucleus ) ) )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?parent )
		)
	)
	cp ( &AtrImpulse 0 (
			20 0 1000
			?act ( ( ?need ( @ImAttach ) ) ( ?need ( @ActImpulse ) ) )
			?chng ?oth ?atr
			?reduce ( ?fix ) 0 ?scope ( ?parent )
		)
	)
	:Make_Link ( &CominCell @ImCell @Block 20 #comin )
	set ( &CominCell^?type ?comin )
	cp ( &CominCell^?scope 0 ( ?oth ) )
	sup ( ( @IM_SENSOR 0 ) ( set ( #IM_SENSOR 10 ) ) )
)>

Attach<(
	sup ( ( @ActImpulse 0 ) ( set ( @ActImpulse 0 ) ) )
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
	sup ( ( #IM_SENSOR 0 ) (
			add ( @Primary @Impulse )
			set ( @Impulse 0 )
		)
	)
)>
