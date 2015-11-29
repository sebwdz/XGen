Init_Axon<(
	set ( @ImAxon 10 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxonHead )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 100 ) )
)>

Axon<(
	:Init ( :Init_Axon ( ) )
	:Link ( @ImNucleus @ImAxon :Axon_Base ( ) :Axon_Head ( ) )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxon 10 ) 20 )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 20 ) 
)>

Init_Axon_Base<(
	set ( @ImAxonBase 10 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxon )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )
)>

Axon_Base<(
	:Init ( :Init_Axon_Base ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 20 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonBase 10 ) 20 )
)>

Init_Axon_Head_Code<(
	set ( @ImInGrow 10 )
	set ( @ImAxonHead 10 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxonHeadSplit )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	:Make_Rpls_Mv ( &RplsBase to @ImAxonHead @ImAxonBase )
        :Init_Prop_Chan ( &RplsBase 10 30 )
)>

Init_Axon_Head_Split<(
	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegCell )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	set ( @ImAxonHeadSplit 10 )
)>

Axon_Head<(
	sup ( ( @ImMain 0 )
		( :Axon_Head_Code )
		( :Axon_Head_Split )
	)
)>

Axon_Head_Code<(
	:Init ( :Init_Axon_Head_Code ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 5 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonHead 10 ) 5 )
)>

Axon_Head_Split<(
	:Init ( :Init_Axon_Head_Split ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 10 0 ) 5 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonHeadSplit 10 ) 5 )

	:Grow_Axon ( )
)>

Init_Grow_Axon<(
	:Make_Atr_Mv ( &AtrCell to @ImInGrow @Dopamine )
        :Init_Prop_Chan ( &AtrCell 1 200 )

	:Make_Rpls_Mv ( &RplsFromOth to @ImAxonHeadSplit @ImAxonHeadSplit )
	:Init_Prop_Chan ( &RplsFromOth 10 30 )

	:Make_Atr_Mv ( &AtrConst to @ImInGrow @IsNegCell )
	:Init_Prop_Chan ( &AtrConst 10 30 )

	:Make_Rpls_Mv ( &RplsOth oth @ImInGrow @ImInGrow )
	:Init_Prop_Chan ( &RplsOth 5 40 )
)>

Grow_Axon<(
	:Init ( :Init_Grow_Axon ( ) )
	sup ( ( @Impulse 0 )
		( set ( @ImInGrow 10 ) )
	)
	sup ( ( @ImInGrow 0 ) (
			sub ( @ImInGrow 1 )
			set ( !sub @Impulse )
			div ( !sub 20 )
			inf ( ( !sub 1 )
				( sub ( @Impulse 1 ) )
				( sub ( @Impulse !sub ) )
			)
		)
	)
)>
