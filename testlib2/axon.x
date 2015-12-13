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
	:Link ( @ImNucleus @ImAxon :Axon_Base ( ) :Axon_Head ( ) )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegAxon 10 ) 20 )
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
)>

Init_Axon_Head_Split<(
	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegCell )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	set ( @ImAxonHeadSplit 10 )
	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImAxonHead )
	:Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

	:Make_Give_Chan ( &GivePeptide @Peptide @ImAxonHead )
	:Set_Prop_Chan ( &GivePeptide pw ( 100 ) )
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
	:CycleL ( :Init_Prop_Chan ( &RplsBase 10 30 ) 100 1 )
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
        :Init_Prop_Chan ( &AtrDopamine 7 100 )

	:Make_Rpls_Mv ( &AtrPeptide to @ImInGrow @PeptideAct )
	:Init_Prop_Chan ( &AtrPeptide 10 50 )

	:Make_Rpls_Mv ( &RplsFromOth to @ImAxonHeadSplit @ImAxonHeadSplit )
	:Init_Prop_Chan ( &RplsFromOth 10 20 )

	:Make_Atr_Mv ( &AtrCell to @ImInGrow @IsNegCell )
	:Init_Prop_Chan ( &AtrCell 5 20 )

	:Make_Rpls_Mv ( &RplsOth oth @ImInGrow @ImAxonHeadSplit )
	:Init_Prop_Chan ( &RplsOth 5 30 )
)>

Grow_Axon<(
	:Init ( :Init_Grow_Axon ( ) )

	sup ( ( @Impulse 0 ) ( set ( @ImInGrow 10 ) ) )
	sup ( ( @ImInGrow 0 ) (
			:Cycle ( sub ( @ImInGrow 1 ) 5 )
			:Reduce ( @Impulse 20 1 )
		)
	)
)>
