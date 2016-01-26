Init_Axon<(
	set ( @ImAxonHead 10 )
	set ( @IsNegAxon 10 )

	[ PHISICAL INTERACTION ]
	:Make_Rpls_Mv ( &RplsCell ?to 0 ( ?need ( @ImAxonHead ) ) ( ?need ( @ImSoma ) ) )
	cp ( &RplsCell^?pw 10 )
	cp ( &RplsCell^?scope ?scope ( ?link ) )
	cp ( &AtrActive 0 (
			300 20 10
			?act (
				( ?need ( @ActiveImpulse ) )
				( ?need ( @ImActive ) ?forbiden ( @ @From ) )
			)
			?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrDendrite 0 (
			30 0 40
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImDendriteHead ) ?forbiden ( @ @From ) )
			)
			?mv ?to ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	[ TRANSIT ]
	cp ( &GiveImpulse 0 (
			20 0 500
			?act (
				( ?need ( @Impulse ) )
				( ?need ( @ImDendriteHead ) ?forbiden ( @From ) )
			)
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	[ SPECIALISATION ]
	sup ( ( @IM_SENSOR 0 )
		( cp ( #type /IM_SENSOR ) )
		( cp ( #type /IM_ACTOR ) )
	)
	cp ( &AtrActive^?act^1^?forbiden^0^0 #type )
	cp ( &AtrActive^?act^1^?forbiden^1^1 @CellId )
	cp ( &AtrDendrite^?act^1^?forbiden^0^0 #type )
	cp ( &AtrDendrite^?act^1^?forbiden^1^1 @CellId )
	cp ( &GiveImpulse^?act^1^?forbiden^0^1 @CellId )
)>

Install_Axon<(
	inf ( ( #install 1 ) (
			:Make_Link (
				&LinkCell @ImSoma @Block
				20 #install
			)
			:Init ( cp ( &LinkCell^?scope ?scope ( ?parent ) ) )
		) ( 
			:Init ( (
					take_out
					set ( &RplsCell^?dst 60 )
			) )
		)
	)
)>

Exec_Axon<(
	sup ( ( #install 0 ) (
			inf ( ( @InSynapse 1 ) (
					set ( @ActiveImpulse @Impulse )
					sup ( ( @Impulse 0 ) ( sub ( @Impulse 2 ) ) )
				)
			)
		)
	)
)>

Axon<(
	:Init ( :Init_Axon )
	:Install_Axon
	:Exec_Axon
)>
