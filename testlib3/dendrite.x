Init_Dendrite<(
	set ( @ImDendriteHead 10 )
	set ( @ ( /From @CellId ) 10 )

	mult ( @ ( /From @CellId ) 100 )
	mult ( @IM_SENSOR 100 )
	mult ( @IM_ACTOR 100 )

	[ PHYSICAL INTERACTION ]
	:Make_Rpls_Mv ( &RplsCell ?to 0 ( ?need ( @ImDendriteHead ) ) ( ?need ( @ImCell ) ) )
	set ( &RplsCell^?pw 10 )
	cp ( &RplsCell^?scope ?scope ( ?link ) )
	cp ( &RplsOth 0 (
			30 0 50
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImDendriteHead ) ?forbiden ( @From ) )
			) ?mv ?to ?rpls
			0 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrCell 0 (
			130 20 20
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImCell ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	cp ( &AtrByAxon 0 (
			30 0 10
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImAxonHead ) ?forbiden ( @From ) )
			) ?mv ?to ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	[ TRANSMIT ]
	cp ( &GiveImpulse 0 (
			100 0 2000
			?act (
				( ?need ( @Impulse ) )
				( ?need ( @IsNegNucleus ) )
			) ?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	cp ( &GivePrimary 0 (
			50 0 4000
			?act (
				( ?need ( @SalPrimary ) )
				( ?need ( @ImAxonHead ) ?forbiden ( @From ) )
			) ?chng ?to ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByAxon^?act^1^?forbiden^0^1 @CellId )
	cp ( &GivePrimary^?act^1^?forbiden^0^1 @CellId )
	cp ( &RplsOth^?act^1^?forbiden^0^1 @CellId )
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
	sub ( @Active 1 )
	sub ( @SalPrimary 1 )
	sup ( ( @Active 20 ) ( set ( @Active 20 ) ) )
	sup ( ( @Primary 20 ) ( set ( @Primary 20 ) ) )
	inf ( ( @IM_ACTOR 1 ) (
			add ( @ImActive @Active )
			div ( @ImActive 10 )
			sup ( ( @ImActive 50 ) ( set ( @ImActive 50 ) ) )
		)
	)
	set ( #tmp @Primary )
	sub ( @Primary 1 )
	sub ( @AtrPrimary 0.5 )
	[sup ( ( #tmp 20 ) ( set ( #tmp 20 ) ) )]
	add ( @AtrPrimary #tmp )
	add ( @SalPrimary @Primary )
	div ( @Primary 5 )
)>
