Test<(
	:Init ( :InitTest )
	sup ( ( @ImAttach 0 ) ( :AttachAct ) )
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
	:Init_Prop_Chan ( &atr 2 80 )
)>

Attach<(
        set ( @ImAttach 10 )

	:Make_Atr_Mv ( &atr to @ImAttach @ImNucleus )
        :Init_Prop_Chan ( &atr 15 80 )
	:Make_Spe_Chan ( &enter @ImCell @ImAct comin 20 )
)>

Init_AttachAct<(
	:Make_Give_Chan ( &GiveOutImpulse @Impulse @ImNeg )
	:Set_Prop_Chan ( &GiveOutImpulse pw ( 10 ) )
)>

AttachAct<(
[	set ( @Impulse 10 )]
	:Init ( :Init_AttachAct )
	:Cycle ( ( :Give_Cycle ( &GiveOutImpulse @Impulse 50 0 ) ) 5 )
	:CycleL ( detach ( :AttachCompnent ) 10 1 )
)>

AttachCompnent<(
	sup ( ( @ImNucleus 0 ) (
			:Init ( :InitCompnentNucleus )
		) (
			sup ( ( @ImNucleusSplit 0 ) (
                        		:Init ( :InitCompnentNucleusSplit )
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
	sup ( ( @ISSENSOR 0 )
		( set ( @NoAxon 10 ) )
        )
)>
