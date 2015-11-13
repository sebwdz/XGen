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
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 50 ) )
)>

NucleusCode<(
	:Init ( :InitNucleusCode )
	:CycleL ( split 0 1 )
	:CycleL ( unshared ( @ImSplit ) 2 1 )
	and ( (
			sup ( ( @Impulse 280 ) )
			inf ( ( @NoAxon 1 ) )
		) (
			:CycleL ( (
				creat ( :Axon )
				set ( @Impulse 0 )
			) 10 1 )
		)
	)
	:Cycle ( :Set_Takein ( ( @Impulse 350 ) @IsNegNucleus 10 ) 20 )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 20 )
)>

InitSplitNucleus<(
	set ( @ImNucleusSplit 10 )
	set ( @ImFreeNucleusSplit 10 )
	unshared ( @ImSplit )

	:Make_Rpls_Mv ( &RplsSplit to @ImNucleusSplit @ImNucleusSplit )
	:Init_Prop_Chan ( &RplsSplit 10 40 )

	:Make_Spe_Chan ( &LinkNucleus @ImNucleus @block link 10 )
)>

SplitNucleus<(
	:Init ( :InitSplitNucleus )
	:CycleL ( take_out 20 1 )
	:CycleL ( :Set_Prop_Chan ( &LinkNucleus dst ( 0 ) ) 20 1 )
	sup ( ( @ImAct 2 )
		( set ( @ImFreeNucleusSplit 0 ) )
	)
)>
