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

	:Make_Atr_Mv ( &AtrBySplit to @ImNucleus @ImNucleusSplit )
	:Init_Prop_Chan ( &AtrBySplit 15 60 )

	:Make_Atr_Mv ( &AtrSplit oth @ImNucleus @ImNucleusSplit )
	:Init_Prop_Chan ( &AtrSplit 15 60 )

	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegAxonBase )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )

	:Make_Give_Chan ( &GiveDopamine @Dopamine @ImCytosol )
	:Set_Prop_Chan ( &GiveDopamine pw ( 100 ) )

	:Make_Give_Chan ( &GivePeptide @Peptide @ImCytosol )
	:Set_Prop_Chan ( &GivePeptide pw ( 100 ) )

	set ( @IsNegNucleus 80 )
)>

NucleusCode<(
	:Init ( :InitNucleusCode )
	:CycleL ( split 0 1 )
	:CycleL ( unshared ( @ImSplit ) 2 1 )
	and ( (
			inf ( ( #haveAxon 1 ) )
			inf ( ( @NoAxon 1 ) )
		) ( :CycleL ( ( creat ( :Axon ) set ( #haveAxon 1 ) ) 900 1 ) )
	)
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 5 )
	:Cycle ( :Give_Cycle ( &GiveDopamine @Dopamine 30 0 ) 10 )
	:Cycle ( :Give_Cycle ( &GivePeptide @Peptide 30 0 ) 10 )
	inf ( ( @NoDendrite 1 )
		( :CycleL ( creat ( :Dendrite ) 900 2 ) )
		( set ( @Dopamine 0 ) set ( @Peptide 0 ) )
	) 
)>

InitSplitNucleus<(
	set ( @ImNucleusSplit 10 )
	set ( @ImFreeNucleusSplit 10 )
	unshared ( @ImSplit )

	:Make_Rpls_Mv ( &RplsSplit to @ImNucleusSplit @ImNucleusSplit )
	:Init_Prop_Chan ( &RplsSplit 40 50 )

	:Make_Spe_Chan ( &LinkNucleus @ImNucleus @block link 10 )

	inf ( ( @ImAct 2 )
		( :Set_Prop_Chan ( &GiveDopamine pw ( 50 ) ) )
		( :Set_Prop_Chan ( &GiveDopamine pw ( 100 ) ) )
	)
)>

SplitNucleus<(
	:Init ( :InitSplitNucleus )
	:CycleL ( take_out 20 1 )
	:CycleL ( :Set_Prop_Chan ( &LinkNucleus dst ( 0 ) ) 20 1 )
	sup ( ( @ImAct 2 ) ( set ( @ImFreeNucleusSplit 0 ) ) )
)>
