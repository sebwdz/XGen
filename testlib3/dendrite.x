Init_Dendrite<(
	set ( @ImDendriteHead 10 )
	set ( #PreSynaptic 10 )
	set ( @ImPostSynaptic 10 )
	set ( @ ( /From @CellId ) 10000 )

	[ PHYSICAL INTERACTION ]
	:Make_Rpls_Mv ( &RplsBase ?to 0 ( ?need ( @ImDendriteHead ) ) ( ?need ( @ImDendriteBase ) ) )
	set ( &RplsBase^?pw 10 )
	cp ( &RplsBase^?scope ?scope ( ?link ) )

	cp ( &RplsOth 0 (
			35 0 40
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImPostSynaptic @ImDendriteHead @ImCell ) )
			) ?mv ?to ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByBase 0 (
			130 30 7
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImDendriteBase ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	cp ( &AtrBase 0 (
			130 35 10
			?act (
				( ?need ( @ImDendriteHead ) )
				( ?need ( @ImDendriteBase ) )
			) ?mv ?oth ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	cp ( &AtrByTarget 0 (
			40 0 15
			?act (
				( ?need ( @ImDendriteHead @AtrPrimary ) )
				( ?need ( @ImPreSynaptic @ActiveImpulse ) ?forbiden ( @From ) )
			) ?mv ?to ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByTargetLong 0 (
			150 0 2
			?act (
				( ?need ( @AtrPrimary ) )
				( ?need ( @ActiveImpulse @ImPreSynaptic ) ?forbiden ( @From ) )
			) ?mv ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	[ TRANSMIT ]
	cp ( &GiveImpulse 0 (
			100 0 2000
			?act (
				( ?need ( @Impulse ) )
				( ?need ( @ImDendriteBase ) )
			) ?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	cp ( &GivePrimary 0 (
			50 0 500
			?act (
				( ?need ( @SalPrimary ) )
				( ?need ( @ImPreSynaptic ) ?forbiden ( @From ) )
			) ?chng ?to ?atr
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &AtrByTarget^?act^1^?forbiden^0^1 @CellId )
	cp ( &AtrByTargetLong^?act^1^?forbiden^0^1 @CellId )
	cp ( &GivePrimary^?act^1^?forbiden^0^1 @CellId )
)>

Create_Branching_Dendrite<(
	:Init ( ( shared ( /IMSON ) add ( @IMSON 1 ) ) )
	inf ( ( @IMSON 2 ) (
			:CycleL ( (
				:Create_Branching_Link (
					@ImDendriteBase
					0 (
						cp ( &AtrByTarget^?act^1^?need^0^0 /ImDendriteHead )
						cp ( &AtrByTarget^?act^1^?need^1 0 )
						cp ( &AtrByTarget^?act^1^?forbiden 0 )
						cp ( &GivePrimary^?act^1^?need^0^0 /ImDendriteHead )
						cp ( &GivePrimary^?act^1^?forbiden 0 )
						cp ( &GivePrimary^?act^0^?need^0^0 /Primary )
						cp ( &GivePrimary^?scope ?scope ( ?link ) )
						cp ( &RplsOth^?act^1^?need^0^0 /ImDendriteBase 0 )
						set ( #PreSynaptic 0 )
						set ( @ImPostSynaptic 0 )
					)
				)
			) 200 2 )
		)
	)
)>

Install_Dendrite<(
	:Init ( (
		set ( &RplsBase^?dst 10 )
		cp ( &AtrActor 0 (
                		200 0 0.01
                                ?act ( ( ?need ( @ImDendriteHead ) ) ( ?need ( @IM_ACTOR ) ) )
                                ?mv ?to ?atr
                                ?reduce ( ?fix ) 0 ?scope ( ?oth )
                        )
                )
	) )
	:CycleL ( set ( &AtrActor^?pw 0 ) 100 1 )
)>

Pre_Synaptic_Dendrite<(
	div ( @Primary 2 )
	add ( @SalPrimary @Primary )
)>

ActOut_Dendrite<(
	set ( !tmp @Primary )
	sub ( @SalPrimary 1 )
	sub ( @Primary 1 )
	sub ( @AtrPrimary 0.2 )
	sup ( ( #PreSynaptic 0 ) ( add ( @AtrPrimary !tmp ) ) )
	sup ( ( @AtrPrimary 10 ) ( set ( @AtrPrimary 10 ) ) )
)>

Dendrite<(
	:Debug ( @Primary 68 )
	:Init ( :Init_Dendrite )
	:Link ( @ImDendriteBase :Install_Dendrite )
	:Create_Branching_Dendrite ( )
	sup ( ( #PreSynaptic 0 ) ( :Pre_Synaptic_Dendrite ) )
	:ActOut_Dendrite
)>
