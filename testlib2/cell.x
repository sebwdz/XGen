
Init_Main<(
	set ( @IM_MAIN 10 )

	:Make_Atr_Mv ( &AtrAxonHead oth @IM_MAIN @ImAxonHeadSplit )
	:Init_Prop_Chan ( &AtrAxonHead 20 200 )
	:Set_Prop_Chan ( &AtrAxonHead mindst ( 60 ) )

	:Make_Atr_Mv ( &AtrCell oth @IM_MAIN @ImNucleusSplit )
	:Init_Prop_Chan ( &AtrCell 100 500 )
	:Set_Prop_Chan ( &AtrCell mindst ( 110 ) )

	:Make_Rpls_Mv ( &RplsCell oth @IM_MAIN @ImSplitNucleusAct )
        :Init_Prop_Chan ( &RplsCell 50 90 )
)>

MAIN<(
	:Init ( :Init_Main ( ) )
	inf ( ( #crt 8 )
		( :Cycle_S ( #crt !time creat ( :Cell ) 20 0 ) )
		( :CycleL ( set ( #center 1 ) 70 1 ) )
	)
	sup ( ( #center 0 ) (
			:Cycle_S ( #crtCenter !time creat ( :Cell ) 30 0 )
		)
	)
	:CycleL ( :Set_Prop_Chan ( &AtrAxonHead mindst ( 120 ) ) 1200 1 )
	sup ( ( #crtCenter 7 ) (
			set ( #center 0 )
		)
	)
)>

Killable<(
	inf ( ( @ImAttach 1 ) (
[			:Cycle ( kill 800 )
			:CycleL ( detach ( :NucleusKillable ) 100 1 )]
		)
	)
)>

NucleusKillable<(
	inf ( ( @ImNucleusSplit 1 ) (
			:Init (
				:Make_Spe_Chan ( &attachToNcl @ImNucleusSplit @Stop attach 50 )
			)
		) (
			:Set_Prop_Chan ( &attachToNcl dst ( 0 ) )
			:CycleL ( ( set ( @ImFreeNucleusSplit 30 ) ) 100 1 )
		)
	)
)>

CellInit<(
	set ( @ImCell 20 )
	new_head ( :Nucleus )
)>

Cell<(
	:Init ( :CellInit )
	:CycleL ( new_head ( :Cytosol ) 30 2 )
)>

