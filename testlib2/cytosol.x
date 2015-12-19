
Cytosol<(
	set ( @WithDendrite 10 )

	:Init ( :Init_Cytosol ( ) )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegCytosol 80 ) 5 )
	:Cycle ( ( :Give_Cycle ( &GiveImpulse @Impulse 50 0 ) ) 5 )
	[:CycleL ( (
			:Set_Prop_Chan ( &Rpls dst ( 0 ) )
			:Set_Prop_Chan ( &AtrNcl dst ( 0 ) )
	) 1000 1 )]
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 5 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 50 0 ) 5 )
[
	sup ( ( @Impulse 1 )
                (
                        echo ( #prev 32 67 32 @Impulse 10 )
                        set ( #prev @Impulse )
                ) ( set ( #prev 0 ) )]
)>

Init_Cytosol<(
	set ( @ImCytosol 10 )

	:Make_Rpls_Mv ( &Rpls to @ImCytosol @ImCytosol )
	:Init_Prop_Chan ( &Rpls 20 10 )

	:Make_Atr_Mv ( &AtrNcl to @ImCytosol @ImNucleus )
	:Init_Prop_Chan ( &AtrNcl 10 40 )

	:Make_Give_Chan ( &GiveImpulse @Impulse @IsNegNucleus )
	:Set_Prop_Chan ( &GiveImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImDendriteBase )
        :Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

        :Make_Give_Chan ( &GivePeptide @Peptide @ImDendriteBase )
        :Set_Prop_Chan ( &GivePeptide pw ( 100 ) )
)>
