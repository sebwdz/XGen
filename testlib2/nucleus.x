InitNucleus<(
	shared ( @ImSplit )
	inf ( ( @ImSplit 1 ) (
			set ( @ImSplit 10 )
			set ( #nucleus 1 )
		)
	)
)>

Nucleus<( 
	:Init ( :InitNucleus )
	sup ( ( #nucleus 0 )
		( :NucleusCode )
		( :SplitNucleus )	
	)
)>

InitNucleusCode<(
	set ( @ImNucleus 10 )
	set ( @ImCytosol 10 )

	:Make_Atr_Mv ( &AtrSplit to @ImNucleus @ImNucleusSplit )
	:Init_Prop_Chan ( &AtrSplit 15 60 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxonBase )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImNucleusSplit )
	:Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

	:Make_Give_Chan ( &GivePeptide @Peptide @ImNucleusSplit )
	:Set_Prop_Chan ( &GivePeptide pw ( 100 ) )
)>

NucleusCode<(
	:Init ( :InitNucleusCode )
	:CycleL ( split 0 1 )
	:CycleL ( unshared ( @ImSplit ) 2 1 )
	and ( (
			inf ( ( #haveAxon 1 ) )
			inf ( ( @NoAxon 1 ) )
		) (
			:CycleL ( (
                        	creat ( :Axon ) 
                        	set ( #haveAxon 1 )
				set ( @Impulse 50 )
                	) 900 1 )
		)
	)
	:Cycle ( :Set_Takein ( ( @Impulse 350 ) @IsNegNucleus 10 ) 10 )
	sup ( ( @NoAxon 0 ) (
			:Init ( (
					:Make_Give_Chan ( &GiveOutImpulse @Impulse @AtrImpulse )
					:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )
				)
			)
		)
	)
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 5 )
	:Reduce ( @Dopamine 20 1 )
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 30 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 30 0 ) 10 )
)>

InitSplitNucleus<(
	set ( @ImNucleusSplit 10 )
	set ( @ImFreeNucleusSplit 10 )
	unshared ( @ImSplit )

	:Make_Rpls_Mv ( &RplsSplit to @ImNucleusSplit @ImNucleusSplit )
	:Init_Prop_Chan ( &RplsSplit 10 50 )

	:Make_Atr_Mv ( &AtrByDopamine oth @DopamineAct @ImAxonHeadSplit )
	:Set_Prop_Chan ( &AtrByDopamine pw ( 1 ) )

	:Make_Spe_Chan ( &LinkNucleus @ImNucleus @block link 10 )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImAxonHeadSplit )
	:Make_Give_Chan ( &GivePeptide @Peptide @ImAxonHeadSplit )

	inf ( ( @ImAct 2 )
		( :Set_Prop_Chan ( &GiveDopamine pw ( 10 ) ) )
		( :Set_Prop_Chan ( &GiveDopamine pw ( 100 ) ) )
	)
)>

SplitNucleus<(
	:Init ( :InitSplitNucleus )
	:CycleL ( take_out 20 1 )
	:CycleL ( :Set_Prop_Chan ( &LinkNucleus dst ( 0 ) ) 20 1 )
	sup ( ( @ImAct 2 ) ( set ( @ImFreeNucleusSplit 0 ) ) )
	:CycleL ( :Set_Prop_Chan ( &RplsSplit dst ( 0 ) ) 1000 1 )

	:TransformTo ( @Dopamine @DopamineAct 10 )
	:TransformTo ( @Peptide @PeptideAct 10 )

	:OnlyOne ( @Dopamine @Peptide )
	:OnlyOne ( @DopamineAct @PeptideAct )

	sup ( ( @DopamineAct 0 ) (
			:Cycle ( sub ( @DopamineAct 1 ) 5 )
			:Cycle ( :Reduce ( @Dopamine 20 1 ) 5 )
		)
	)
	sup ( ( @PeptideAct 0 ) (
			:Cycle ( sub ( @PeptideAct 1 ) 5 )
			:Cycle ( :Reduce ( @Peptide 20 1 ) 5 )
		)
	)
	sup ( ( @ISSENSOR 0 ) (
			inf ( ( #born 1 ) ( add ( @Dopamine 20 ) ) )
			:CycleL ( set ( #born 1 ) 2100 1 )
		)
	)
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 50 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 20 0 ) 10 )
	:Cycle ( :Give_Cycle ( &AtrByDopamine @DopamineAct 100 0 ) 10 )
)>
