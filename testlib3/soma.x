Soma<(
	:Init ( :Init_Soma ( ) )

	sup ( ( #ActiveNucleus 0 ) ( :Active_Cycle ) )
)>

Init_Soma<(
	set ( @ImSoma 10 )

	cp ( &GiveImpulse 0 (
			400 0 40
			?act ( @Impulse @IsNegAxon )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )
		)
	)
	
	cp ( &GiveActive 0 (
			100 0 50
			?act ( @ImActive @ImDendriteHead )
			?chng ?to ?atr
			?reduce ( ?fix ) 0 ?scope ( ?link )	
		)
	)
)>

Active_Cycle<(
        and ( ( 
                        inf ( ( @Impulse 1 ) )
                        inf ( ( @ImpulseStk 1 ) )
                ) (
                        sup ( ( !wait 5 ) (
                                        set ( #ActiveNucleus 0 )
                                        set ( @IsNegNucleus 10 )
                                )
                        )
			set ( @ImActive 0 )
                        add ( !wait 1 )
                ) (
			set ( @ImActive 20 )
                        set ( !wait 0 )
                        set ( !sd #Speed )
                        sup ( ( !sd @ImpulseStk ) ( set ( !sd @ImpulseStk ) ) )
                        sub ( @ImpulseStk !sd )
                        add ( @Impulse !sd )
                )
        )
)>
