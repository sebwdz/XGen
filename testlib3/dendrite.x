Init_Dendrite<(
	set ( @ImDendriteHead 10 )
	set ( @ ( /From @CellId ) 10 )

	mult ( @IM_SENSOR 100 )
	mult ( @IM_ACTOR 100 )

	[ PHYSICAL INTERACTION ]
	:Make_Rpls_Mv ( &RplsCell ?to 0 ( ?need ( @ImDendriteHead ) ) ( ?need ( @ImCell ) ) )
	set ( &RplsCell^?pw 10 )
	cp ( &RplsCell^?scope ?scope ( ?link ) )
	cp ( &RplsOth 0 (
			20 0 100
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImDendriteHead ) )
			)
			?mv ?to ?rpls
			0 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrCell 0 (
			150 40 100
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImCell ) )
			)
			?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	[ TRANSMIT ]
	cp ( &GiveImpulse 0 (
			80 0 200
			?act (
				( ?need ( @Impulse ) )
				( ?need ( @ImCell ) )
			)
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
)>

Install_Dendrite<(
	inf ( ( #install 1 ) (
                        :Make_Link ( &LinkCell @ImCell @Block 20 #install )
                        cp ( &LinkCell^?scope ?scope ( ?parent ) )
                ) ( :Init ( ( take_out set ( &RplsCell^?dst 15 ) ) ) )
        )
)>

Dendrite<(
	:Init ( :Init_Dendrite )
	:Install_Dendrite
	sup ( ( @Active 0 ) (
			sub ( @Active 1 )
			inf ( ( @IM_ACTOR 1 ) (
					set ( @ImActive @Active )
					div ( @ImActive 10 )
				)
			)
		)
	)
)>
