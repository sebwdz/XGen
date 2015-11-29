Test<(
	:Init ( :InitTest )
	sup ( ( @ImInstall 0 ) ( :AttachAct ) )
	and ( ( inf ( ( @ImAct 5 ) )
		inf ( ( @ImAttach 1 ) ) ) ( :Attach )
	)
)>

InitTest<(
	shared ( @ISSENSOR )
	set ( @ImAct 10 )

	:Make_Atr_Chng ( &attach to @ImAct @ImNucleusSplit )
	:Init_Prop_Chan ( &attach 10 20 )

	:Make_Atr_Mv ( &atr oth @ImAct @ImFreeNucleusSplit )
	:Init_Prop_Chan ( &atr 3 150 )
)>

Attach<(
        set ( @ImAttach 10 )
	set ( @ImInstall 10 )

	:Make_Atr_Mv ( &atr to @ImAttach @ImNucleus )
        :Init_Prop_Chan ( &atr 15 80 )
	:Make_Spe_Chan ( &enter @ImCell @ImAct comin 20 )
)>

Init_AttachAct<(
	set ( @AtrImpulse 10 )
	shared ( @ISSENSOR )
	inf ( ( @ISSENSOR 1 ) (
			:Make_Give_Chan ( &GiveOutImpulse @Impulse @ImNeg )
			:Set_Prop_Chan ( &GiveOutImpulse pw ( 500 ) )
		) (
			:Make_Give_Chan ( &GiveOutActive @Active @ImNucleus )
			:Set_Prop_Chan ( &GiveOutActive pw ( 10 ) )
		)
	)
	:Make_Give_Chan ( &GiveAct @ImAttach @ImCell )
	:Set_Prop_Chan ( &GiveAct pw ( 200 ) )
)>

AttachAct<(
	:Init ( :Init_AttachAct )
	inf ( ( @ISSENSOR 1 ) ( 
			:Cycle ( ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) ) 5 )
		) (
			:Cycle ( ( :Give_Cycle ( &GiveOutActive @Active 50 0 ) ) 2 )
		)
	)
	sup ( ( @ISSENSOR 0 ) (
		set ( @ImpulseStk @Impulse )
		sup ( ( @Impulse 0 ) ( set ( @Impulse 0 ) ) )
	) )
	:CycleL ( detach ( :AttachCompnent ) 10 1 )
	:Cycle ( :Give_Cycle ( &GiveAct @ImAttach 10 0 ) 50 )
)>

AttachCompnent<(
	sup ( ( @ImNucleus 0 ) (
			:Init ( :InitCompnentNucleus )
			sup ( ( @ISSENSOR 0 ) (
					:Cycle ( :Give_Cycle ( &GiveActive @Active 30 0 ) 2 )
			) )
		) (
			sup ( ( @ImNucleusSplit 0 ) (
                        		:Init ( :InitCompnentNucleusSplit )
					sup ( ( @ISSENSOR 0 )
						( sup ( ( @Active 0 ) (
								add ( @Dopamine 10 )
								sup ( ( @Dopamine 250 )
									( set ( @Dopamine 250 ) )
								)
								set ( @Active 0 )
						) ) sub ( @Dopamine 1 ) )
					)
                		) ( :Init ( :InitAttachCompnent ) )
			)
		)
	)
)>

InitAttachCompnent<(
	:Make_Spe_Chan ( &attach @ImNucleus @No attach 50 )
)>

InitCompnentNucleusSplit<(
	set ( @ImSplitNucleusAct 10 )
	
	:Set_Prop_Chan ( &attach dst ( 0 ) )
	:Set_Prop_Chan ( &atr dst ( 0 ) )
)>

InitCompnentNucleus<(
	sup ( ( @ISSENSOR 0 ) (
			set ( @NoAxon 10 )
			:Make_Give_Chan ( &GiveActive @Active @ImNucleusSplit )
			:Set_Prop_Chan ( &GiveActive pw ( 10 ) ) 
		)
        )
)>
