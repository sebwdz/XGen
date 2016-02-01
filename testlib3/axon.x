Init_Axon<(
	shared ( /SON /CellId )
	add ( @SON 1 )
	set ( @ImPreSynaptic 10 )
	set ( @ImAxonHead 10 )
	set ( @IsNegAxon 10 )
	set ( @ ( /From @CellId ) 10000 )

	[ PHISICAL INTERACTION ]
	:Make_Rpls_Mv ( &RplsCell ?to 10 ( ?need ( @ImAxonHead ) ) ( ?need ( @ImAxonBase ) ) )
	cp ( &RplsCell^?pw 10 )
	cp ( &RplsCell^?scope ?scope ( ?link ) )
	cp ( &AtrByDendrite 0 (
			30 0 5
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImPostSynaptic ) ?forbiden ( @From ) )
			) ?mv ?to ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrPrimary 0 (
			60 0 15
			?act (
				( ?need ( @ActiveImpulse ) )
				( ?need ( @AtrPrimary ) ?forbiden ( @From ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &RplsOth 0 (
			50 0 20
			?act (
				( ?need ( @ActiveImpulse ) )
				( ?need ( @ImAxonHead @ImCell ) )
			) ?mv ?oth ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByPrimary 0 (
			160 0 5
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @AtrPrimary ) ?forbiden ( @From ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &RplsByOth 0 (
			30 0 40
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImAxonHead @ImCell ) )
			) ?mv ?to ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByBase 0 (
			500 70 5
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImAxonBase ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	cp ( &AtrBase 0 (
			500 75 14
			?act (
				( ?need ( @ImAxonHead ) )
				( ?need ( @ImAxonBase ) )
			) ?mv ?oth ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	[ TRANSMITION ]
	cp ( &GiveImpulse 0 (
			10 0 2000
			?act (
				( ?need ( @Impulse ) )
				( ?need ( @ImPostSynaptic ) ?forbiden ( @From ) )
			) ?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &GivePrimary 0 (
			2000 0 2000
			?act (
				( ?need ( @Primary ) )
				( ?need ( @ImAxonBase ) )
			) ?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	[ SPECIALIZATION ]
	sup ( ( @SON 1 ) ( set ( &AtrByBase^?mindst 40 ) ) )
	cp ( &AtrByDendrite^?act^1^?forbiden^0^1 @CellId )
	cp ( &AtrPrimary^?act^1^?forbiden^0^1 @CellId )
	cp ( &GiveImpulse^?act^1^?forbiden^0^1 @CellId )
	cp ( &AtrByPrimary^?act^1^?forbiden^0^1 @CellId )
)>

Install_Axon<(
	:Init ( (
			set ( &RplsCell^?dst 50 )
			cp ( &AtrSensor 0 (
					300 0 0.1
					?act ( ( ?need ( @ImAxonHead ) ) ( ?need ( @IM_SENSOR ) ) )
					?mv ?to ?atr
					?reduce ( ?auto ) 0 ?scope ( ?oth )
				)
			)
	) )
	:CycleL ( set ( &AtrSensor^?pw 0 ) 100 1 )
)>

Exec_Axon<(
	sup ( ( #install 0 ) (
			add ( @ActiveImpulse @Impulse )
			sup ( ( @ActiveImpulse 50 ) ( set ( @ActiveImpulse 50 ) ) )
			sup ( ( @Impulse 0 ) ( sub ( @Impulse 1 ) ) )
			sup ( ( @ActiveImpulse 0 ) ( sub ( @ActiveImpulse 1 ) ) )
		)
	)
)>

Split_Axon<(
[:CycleL ( (
		:Init ( (
			echo ( 65 10 )
			cp ( &GiveImpulseSon 0 (
					1000 0 200
					?act ( ( ?need ( @Impulse ) ) ( ?need ( @ImAxonHead ) ) )
					?chng ?to ?atr
					?reduce ( ?fix ) 0 ?scope ( ?link )
				)
			)
			set ( &AtrByPrimary^?pw 0 )
			set ( &AtrPrimary^?pw 0 )
			set ( &RplsOth^?pw 10 )
			set ( &GiveImpulse^?pw 0 )
		) )
		splitin
		set ( @ImAxonBase 10 )
	) 100 1 )]
)>

Axon<(
	:Init ( :Init_Axon )
	:Link ( @ImAxonBase :Install_Axon )
	:Exec_Axon
	sub ( @Primary 1 )
	add ( @Primary @SalPrimary )
	set ( @SalPrimary 0 )
)>

