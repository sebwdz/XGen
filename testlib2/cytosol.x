
Cytosol<(
	set ( @WithDendrite 10 )

	:Init ( :Init_Cytosol ( ) )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegCytosol 80 ) 5 )
	:Cycle ( ( :Give_Cycle ( &GiveImpulse @Impulse 50 0 ) ) 5 )
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 5 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 50 0 ) 5 )
)>

Init_Cytosol<(
	set ( @ImCytosol 10 )

	:Make_Rpls_Mv ( &Rpls to @ImCytosol @ImCytosol )
	:Init_Prop_Chan ( &Rpls 20 10 )

	:Make_Atr_Mv ( &AtrByNcl to @ImCytosol @ImNucleus )
	:Init_Prop_Chan ( &AtrByNcl 30 40 )
	:Set_Prop_Chan ( &AtrByNcl mindst ( 5 ) )

	:Make_Give_Chan ( &GiveImpulse @Impulse @IsNegNucleus )
	:Set_Prop_Chan ( &GiveImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImDendriteBase )
        :Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

        :Make_Give_Chan ( &GivePeptide @Peptide @ImDendriteBase )
        :Set_Prop_Chan ( &GivePeptide pw ( 100 ) )

	:Make_Atr_Mv ( &AtrNucleus oth @ImCytosol @ImNucleus )
	:Init_Prop_Chan ( &AtrNucleus 10 50 )
	:Set_Prop_Chan ( &AtrNucleus mindst ( 5 ) )
)>
