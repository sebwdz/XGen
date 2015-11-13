
MAIN<(
	:Cycle_S ( #crt !time creat ( :Cell ) 40 0 ) 
	sup ( ( #crt 15 ) ( kill ) )
)>

CellInit<(
	new_head ( :Nucleus )
	set ( @ImCell 10 )
	:Make_Give_Chan ( &GiveOutImpulse @Impulse @IsNegCytosol )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 50 ) )
)>

Cell<(
	:Init ( :CellInit )
	:CycleL ( new_head ( :Cytosol ) 30 3 )
	:Cycle ( :Set_Takein ( ( @Impulse 150 ) @IsNegCell 10 ) 20 )
	:Cycle ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) 10 )
)>

