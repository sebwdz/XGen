TEST<(
	:Attach
)>

Init_Attach<(
	set ( @ImFree 0 )
	set ( @ImAttach 10 )

	cp ( &GiveImpulse 0 (
			10 0 1000
			?act ( ( ?need ( @Impulse ) ) ( ?need ( @ImPostSynaptic ) ) )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &GivePrimary 0 (
			30 0 1000
			?act ( ( ?need ( @Primary ) ) ( ?need ( @ImPreSynaptic ) ) )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?oth )
		)
	)
	cp ( &RplsCell 0 (
			70 0 10
			?act ( ( ?need ( @ImAttach ) ) ( ?need ( @ImCell ) ) )
			?mv ?to ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &RplsOth 0 (
			90 0 10
			?act ( ( ?need ( @ImAttach ) ) ( ?need ( @ImAttach ) ) )
			?mv ?to ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	cp ( &RplsDiff 0 (
			140 0 5
			?act ( ( ?need ( @ImAttach ) ) ( ?need ( @ ) ) )
			?mv ?to ?rpls
			?reduce ( ?auto ) 0 ?scope ( ?oth )
		)
	)
	mult ( @IM_SENSOR 1 )
	mult ( @IM_ACTOR 1 )
	sup ( ( @IM_SENSOR 0 ) (
			cp ( &RplsDiff^?act^1^?need^0^0 /IM_ACTOR )
		) ( cp ( &RplsDiff^?act^1^?need^0^0 /IM_SENSOR ) )
	)
	sup ( ( @IM_SENSOR 0 ) (
			set ( @ImPostSynaptic 50 )
			set ( #PreSynaptic 10 )
		) ( set ( @ImPreSynaptic 50 ) ) )
	)
)>

Attach<(
	sup ( ( @IM_SENSOR 0 ) (
			:Pre_Synaptic_Dendrite
			:ActOut_Dendrite
			set ( @Impulse 0 )
		) (
			:Exec_Axon
			set ( @Primary 0 ) 
		)
	)
	:CycleL ( set ( &RplsCell^?dst 0 ) 900 1 )
	:Init ( :Init_Attach )
)>
