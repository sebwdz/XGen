
Cytosol<(
	:Init ( :Init_Cytosol ( ) )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegCytosol 10 ) 20 )
	:Cycle ( ( :Give_Cycle ( &GiveImpulse @Impulse 50 0 ) ) 10 )
)>

Init_Cytosol<(
	set ( @ImCytosol 10 )
	set ( @ImNeg 10 )

	:Make_Rpls_Mv ( &Rpls to @ImCytosol @ImCytosol )
	:Init_Prop_Chan ( &Rpls 20 10 )

	:Make_Atr_Mv ( &AtrNcl to @ImCytosol @ImNucleus )
	:Init_Prop_Chan ( &AtrNcl 10 40 )

	:Make_Give_Chan ( &GiveImpulse @Impulse @IsNegNucleus )
	:Set_Prop_Chan ( &GiveImpulse pw ( 50 ) )
)>
