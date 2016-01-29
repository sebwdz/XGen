Init_Axon<(
	set ( @ImAxonHead 10 )
	set ( @IsNegAxon 10 )
	set ( @ ( /From @CellId ) 10 )

	mult ( @ ( /From @CellId ) 100 )
	[ PHISICAL INTERACTION ]
	:Make_Rpls_Mv ( &RplsCell ?to 10 ( ?need ( @ImAxonHead ) ) ( ?need ( @ImSoma ) ) )
	cp ( &RplsCell^?pw 1 )
	cp ( &RplsCell^?scope ?scope ( ?link ) )
	cp ( &AtrActive 0 (
			20 0 2
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImDendriteHead ) ?forbiden ( @ @From ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrPrimary 0 (
			100 0 15
			?act (
				( ?need ( @ActiveImpulse ) )
				( ?need ( @AtrPrimary ) ?forbiden ( @ @From ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &RlsOth 0 (
			50 0 50
			?act (
				( ?need ( @ActiveImpulse ) )
				( ?need ( @ImAxonHead ) )
			) ?mv ?oth ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByPrimary 0 (
			80 0 10
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @AtrPrimary ) ?forbiden ( @ @From ) )
			) ?mv ?to ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &RplsByOth 0 (
			20 0 40
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImAxonHead ) )
			) ?mv ?to ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByCell 0 (
			500 70 1
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImCell ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	[ TRANSMITION ]
	cp ( &GiveImpulse 0 (
			10 0 1500
			?act (
				( ?need ( @Impulse ) )
				( ?need ( @ImDendriteHead ) ?forbiden ( @ @From ) )
			) ?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &GivePrimary 0 (
			500 0 100
			?act (
				( ?need ( @Primary ) )
				( ?need ( @ImCell ) )
			) ?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	[ SPECIALIZATION ]
	sup ( ( @IM_SENSOR 0 )
		( cp ( #type /IM_SENSOR ) )
		( sup ( ( @IM_ACTOR ) (
				cp ( #type /IM_ACTOR )
			) ( cp ( #type /IM_NOTHING ) )
		) )
	)
	cp ( &AtrActive^?act^1^?forbiden^0^0 #type )
	cp ( &AtrActive^?act^1^?forbiden^1^1 @CellId )
	cp ( &AtrPrimary^?act^1^?forbiden^0^0 #type )
	cp ( &AtrPrimary^?act^1^?forbiden^1^1 @CellId )
	cp ( &GiveImpulse^?act^1^?forbiden^0^0 #type )
	cp ( &GiveImpulse^?act^1^?forbiden^1^1 @CellId )
	cp ( &AtrByPrimary^?act^1?forbiden^0^0 #type )
	cp ( &AtrByPrimary^?act^1^?forbiden^1^1 @CellId )
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
					set ( &RplsCell^?dst 40 )
			) )
		)
	)
)>

Exec_Axon<(
	sup ( ( #install 0 ) (
			inf ( ( @InSynapse 1 ) (
					add ( @ActiveImpulse @Impulse )
					sup ( ( @ActiveImpulse 50 ) ( set ( @ActiveImpulse 50 ) ) )
					sup ( ( @Impulse 0 ) ( sub ( @Impulse 2 ) ) )
					sup ( ( @ActiveImpulse 0 ) ( sub ( @ActiveImpulse 5 ) ) )
				)
			)
		)
	)
)>

Axon<(
	:Debug ( @SalPrimary 65 )
	:Init ( :Init_Axon )
	:Install_Axon
	:Exec_Axon
	sub ( @Primary 1 )
	add ( @Primary @SalPrimary )
	set ( @SalPrimary 0 )
)>

