Init_Axon<(
	set ( @ImAxon 10 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxonHead )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImAxonBase )
	:Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

	:Make_Give_Chan ( &GivePeptide @Peptide @ImAxonBase )
	:Set_Prop_Chan ( &GivePeptide pw ( 100 ) )
)>

Axon<(
	:Init ( :Init_Axon ( ) )
	:Link ( @ImNucleus @ImAxon :Axon_Base :Axon_Head )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxon 80 ) 20 )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 5 ) 
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 50 0 ) 10 )
)>

Init_Axon_Base<(
	set ( @ImAxonBase 10 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxon )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImNucleus )
	:Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

	:Make_Give_Chan ( &GivePeptide @Peptide @ImNucleus )
	:Set_Prop_Chan ( &GivePeptide pw ( 100 ) )

	:Make_Atr_Mv ( &AtrHead oth @ImAxonBase @ImAxonHead )
	:Init_Prop_Chan ( &AtrHead 10 160 )
	:Set_Prop_Chan ( &AtrHead mindst ( 70 ) )

	:Make_Atr_Mv ( &AtrByHead to @ImAxonBase @ImAxonHead )
	:Init_Prop_Chan ( &AtrByHead 10 160 )
	:Set_Prop_Chan ( &AtrByHead mindst ( 70 ) )

	:Make_Rpls_Mv ( &RplsByHead to @ImAxonBase @ImAxonHead )
	:Init_Prop_Chan ( &RplsByHead 5 60 )
	:Set_Prop_Chan ( &RplsByHead mindst ( 10 ) )
)>

Axon_Base<(
	:Init ( :Init_Axon_Base ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 5 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonBase 50 ) 20 )
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 50 0 ) 10 )
)>

Init_Axon_Head_Code<(
	set ( @ImInGrow 10 )
	set ( @ImAxonHead 10 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxonHeadSplit )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	:Make_Rpls_Mv ( &RplsBase to @ImAxonHead @ImAxonBase )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImLink )
	:Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

	:Make_Give_Chan ( &GivePeptide @Peptide @ImLink )
	:Set_Prop_Chan ( &GivePeptide pw ( 100 ) )

	:Make_Atr_Mv ( &AtrByBase to @PeptideAct @ImAxonBase )
	:Init_Prop_Chan ( &AtrByBase 100 160 )
	:Set_Prop_Chan ( &AtrByBase mindst ( 20 ) )
)>

Init_Axon_Head_Split<(
	set ( @ImAxonHeadSplit 10 )
	set ( @ImConductor 1 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegDendriteHeadSplit )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImAxonHead )
	:Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

	:Make_Give_Chan ( &GivePeptide @Peptide @ImAxonHead )
	:Set_Prop_Chan ( &GivePeptide pw ( 100 ) )

	:Make_Rpls_Mv ( &RplsCell to @ImAxonHeadSplit @ImCell )
	:Init_Prop_Chan ( &RplsCell 10 20 )
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
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 30 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 30 0 ) 10 )
	:CycleL ( :Init_Prop_Chan ( &RplsBase 5 50 ) 100 1 )
	:TransformTo ( @Peptide @PeptideAct 40 )
	:Reduce ( @PeptideAct 20 1 )
)>

Axon_Head_Split<(
	:Init ( :Init_Axon_Head_Split ( ) )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 10 0 ) 5 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxonHeadSplit 10 ) 5 )

	:Grow_Axon ( )
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 30 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 30 0 ) 10 )
)>

Init_Grow_Axon<(
	:Make_Atr_Mv ( &AtrDopamine to @ImInGrow @DopamineAct )
        :Init_Prop_Chan ( &AtrDopamine 5 50 )

	:Make_Atr_Mv ( &AtrDendrite oth @ImInGrow @ImDendriteHeadSplit )
	:Init_Prop_Chan ( &AtrDendrite 10 5 )

	:Make_Rpls_Mv ( &RplsPeptide to @ImInGrow @PeptideAct )
	:Init_Prop_Chan ( &RplsPeptide 10 40 )

	:Make_Rpls_Mv ( &RplsFromOth to @ImAxonHeadSplit @ImAxonHeadSplit )
	:Init_Prop_Chan ( &RplsFromOth 20 40 )

	:Make_Rpls_Mv ( &RplsOth oth @ImInGrow @ImAxonHeadSplit )
	:Init_Prop_Chan ( &RplsOth 30 30 )
)>

Grow_Axon<(
	:Init ( :Init_Grow_Axon ( ) )

	sup ( ( @Impulse 0 ) ( set ( @ImInGrow 10 ) ) )
	sup ( ( @ImInGrow 0 ) (
			:Reduce ( @ImInGrow 10 1 )
			:Reduce ( @Impulse 10 1 )
		)
	)
)>
