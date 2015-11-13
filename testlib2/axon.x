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
	set ( @impulseStk 100 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxon )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 100 ) )
)>

Axon_Base<(
	:Init ( :Init_Axon_Base ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 20 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonBase 10 ) 20 )
)>

Init_Axon_Head_Code<(
	set ( #biais 40 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxonHeadSplit )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 100 ) )

	:Make_Rpls_Mv ( &RplsBase to @ImInGrow @ImAxonBase )
        :Set_Prop_Chan ( &RplsBase pw ( 2 ) )
)>

Init_Axon_Head_Split<(
	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegCell )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 50 ) )
)>

Axon_Head<(
	sup ( ( @ImMain 0 )
		( :Axon_Head_Code )
		( :Axon_Head_Split )
	)
)>

Axon_Head_Code<(
	:Init ( :Init_Axon_Head_Code ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 20 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonHead 10 ) 20 )
	:Cycle ( :Set_Takein ( ( @Impulse 20 ) @ImInGrow 20 ) 10 )
	:Cycle ( :Give_Cycle ( &RplsBase @ImInGrow #biais 0 ) 10 )
)>

Axon_Head_Split<(
	:Init ( :Init_Axon_Head_Split ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 20 0 ) 20 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonHeadSplit 10 ) 20 )

	sup ( ( @Impulse 40 )
		( set ( @Grow 10 ) )
		( set ( @Grow 0 ) )
	) 

	:Make_Atr_Mv ( &AtrCell to @Grow @ImCell )
	:Init_Prop_Chan ( &AtrCell 2 50 )

	:Make_Rpls_Mv ( &RplsImpulse to @Grow @Grow )
	:Init_Prop_Chan ( &RplsImpulse 2 40 )
[
	:Make_Rpls_Mv ( &RplsImpulse2 to @Grow @Impulse )
        :Init_Prop_Chan ( &RplsImpulse2 2 20 )
]
	[:Grow_Axon ( )]
)>

Init_Grow_Axon<([
	:Make_Atr_Mv ( &AtrCell to @ImInGrow @IsNegCell )
	:Init_Prop_Chan ( &AtrCell 10 60 )
]
	set ( @ImInGrow 10 )
)>

Grow_Axon<(
	:Init ( :Init_Grow_Axon ( ) )
	[:Cycle ( :Set_Takein ( ( @Impulse 150 ) @ImInGrow 10 ) 20 )]
)>
