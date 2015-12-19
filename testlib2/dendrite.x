Init_Dendrite<(
	set ( @ImDendrite 10 )
	set ( @IsNegDendrite 80 )

	:Make_Give_Chan ( &GiveImpulse @Impulse @IsNegDendriteBase )
	:Set_Prop_Chan ( &GiveImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImDendriteHead )
        :Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

        :Make_Give_Chan ( &GivePeptide @Peptide @ImDendriteHead )
        :Set_Prop_Chan ( &GivePeptide pw ( 100 ) )
)>
	
Dendrite<(
	:Init ( :Init_Dendrite ( ) )
	:Link ( @WithDendrite @ImDendrite :Dendrite_Base ( ) :Dendrite_Head ( ) )
	:Cycle ( :Give_Cycle ( &GiveImpulse @Impulse 100 0 ) 5 )
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 10 )
        :Cycle ( :Give_Cycle ( &GivePeptide @Peptide 50 0 ) 10 )
)>

Init_Dendrite_Base<(
	set ( @ImDendriteBase 10 )
	set ( @IsNegDendriteBase 80 )
	
	:Make_Atr_Mv ( &AtrCytosol to @ImDendriteBase @ImCytosol )
	:Init_Prop_Chan ( &AtrCytosol 10 50 )

	:Make_Atr_Mv ( &AtrDendriteHead oth @ImDendriteBase @ImDendriteHead )
	:Init_Prop_Chan ( &AtrDendriteHead 30 120 )
	:Set_Prop_Chan ( &AtrDendriteHead mindst ( 20 ) )

	:Make_Give_Chan ( &GiveImpulse @Impulse @IsNegCytosol )
	:Set_Prop_Chan ( &GiveImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImDendrite )
        :Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

        :Make_Give_Chan ( &GivePeptide @Peptide @ImDendrite )
        :Set_Prop_Chan ( &GivePeptide pw ( 100 ) )
)>

Dendrite_Base<(
	:Init ( :Init_Dendrite_Base ( ) )
	:Cycle ( :Give_Cycle ( &GiveImpulse @Impulse 50 0 ) 5 )
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 50 0 ) 10 )
[
	sup ( ( @Impulse 1 )
                (
                        echo ( #prev 32 66 32 @Impulse 10 )
                        set ( #prev @Impulse )
                ) ( set ( #prev 0 ) )
        )
]
)>

Init_Dendrite_Head_Code<(
	set ( @ImDendriteHead 10 )
	set ( @IsNegDendriteHead 80 )

	:Make_Give_Chan ( &GiveImpulse @Impulse @IsNegDendrite )
	:Set_Prop_Chan ( &GiveImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImDendriteHeadSplit )
        :Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

        :Make_Give_Chan ( &GivePeptide @Peptide @ImDendriteHeadSplit )
        :Set_Prop_Chan ( &GivePeptide pw ( 100 ) )
)>

Dendrite_Head<(
	sup ( ( @ImMain 0 ) (
			:Init ( :Init_Dendrite_Head_Code ( ) )
			:Cycle ( :Give_Cycle ( &GiveImpulse @Impulse 50 0 ) 5 )
			:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 10 )
        		:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 50 0 ) 10 )
		) ( :Dendrite_Head_Split ( ) )
	)
)>

Init_Dendrite_Head_Split<(
	set ( @ImDendriteHeadSplit 10 )
	set ( @IsNegDendriteHeadSplit 80 )

	:Make_Rpls_Mv ( &RplsCell to @ImDendriteHeadSplit @ImCell )
	:Init_Prop_Chan ( &RplsCell 10 20 )

	:Make_Atr_Mv ( &AtrByInGrow to @DopamineAct @ImInGrow )
	:Init_Prop_Chan ( &AtrByInGrow 10 40 )

	:Make_Rpls_Mv ( &RplsDendriteHeadSplit to
				@ImDendriteHeadSplit @ImDendriteHeadSplit )
	:Init_Prop_Chan ( &RplsDendriteHeadSplit 10 10 )

	:Make_Give_Chan ( &GiveImpulse @Impulse @IsNegDendriteHead )
	:Set_Prop_Chan ( &GiveImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImAxonHeadSplit )
        :Make_Give_Chan ( &GivePeptide @Peptide @ImAxonHeadSplit )

	:Make_Atr_Mv ( &AtrByDopamine oth @DopamineAct @ImConductor )
	:Set_Prop_Chan ( &AtrByDopamine pw ( 1 ) )

	:Make_Atr_Mv ( &AtrAxonHead to @ImDendriteHeadSplit @ImAxonHeadSplit )
	:Init_Prop_Chan ( &AtrAxonHead 5 10 )
)>

Dendrite_Head_Split<(
	:Init ( :Init_Dendrite_Head_Split ( ) )
	:Cycle ( :Give_Cycle ( &GiveImpulse @Impulse 50 0 ) 5 )

	:Dendrite_Head_React ( )

	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 10 )
        :Cycle ( :Give_Cycle ( &GivePeptide @Peptide 20 0 ) 10 )
        :Cycle ( :Give_Cycle ( &AtrByDopamine @DopamineAct 80 0 ) 10 )
)>

Dendrite_Head_React<(
	:TransformTo ( @Dopamine @DopamineAct 20 )
        :TransformTo ( @Peptide @PeptideAct 20 )

        :OnlyOne ( @Dopamine @Peptide )
        :OnlyOne ( @DopamineAct @PeptideAct )

        sup ( ( @DopamineAct 0 ) (
                        :Cycle ( :Reduce ( @DopamineAct 10 1 ) 5 )
                        :Cycle ( :Reduce ( @Dopamine 10 1 ) 5 )
                )
        )
        sup ( ( @PeptideAct 0 ) (
                        :Cycle ( :Reduce ( @PeptideAct 10 1 ) 5 )
                        :Cycle ( :Reduce ( @Peptide 20 1 ) 5 )
                )
        )
)>
