
Init_Main<(
	set ( @IM_MAIN 10 )

	:Make_Atr_Mv ( &AtrAxonHead oth @IM_MAIN @ImAxonHeadSplit )
	:Init_Prop_Chan ( &AtrAxonHead 10 400 )
	:Set_Prop_Chan ( &AtrAxonHead mindst ( 60 ) )
)>

MAIN<(
	:Init ( :Init_Main ( ) )
	inf ( ( #crt 8 )
		( :Cycle_S ( #crt !time creat ( :Cell :Killable ) 20 0 ) )
		( :CycleL ( set ( #center 1 ) 700 1 ) )
	)
	sup ( ( #center 0 )
		( :Cycle_S ( #crtCenter !time creat ( :Cell ) 30 0 ) )
	)
	and ( (
			sup ( ( #crtCenter 0 ) )
			inf ( ( #center 1 ) )
		) (
			[:Cycle ( creat ( :Cell ) 500 )]
		)
	)
	:CycleL ( :Set_Prop_Chan ( &AtrAxonHead dst ( 0 ) ) 1200 1 )
	:CycleL ( :Set_Prop_Chan ( &RplsAxonHead dst ( 0 ) ) 1200 1 )
	sup ( ( #crtCenter 7 ) ( set ( #center 0 ) :Cycle ( set ( @IM_MAIN 0 ) 900 ) ) )
)>

Killable<(
	inf ( ( @ImAttach 1 ) (
			:Cycle ( kill 800 )
			:CycleL ( detach ( :NucleusKillable ) 100 1 )
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
	new_head ( :Nucleus )
	set ( @ImCell 20 )
	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegCytosol )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 1000 ) )
)>

Cell<(
	:Init ( :CellInit )
	:CycleL ( new_head ( :Cytosol ) 30 3 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegCell 10 ) 20 )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 5 )
)>

