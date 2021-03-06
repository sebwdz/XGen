Init_Nucleus<(
	set ( @IsNegNucleus 10 )

	set ( #Biais 50 )
	set ( #ImpulseWeight 30 )
	set ( #Speed 70 )

)>

Create_Axon<(
	inf ( ( #HaveAxon 1 ) (
			:Cycle ( (
				new_head ( :Axon )
				set ( #HaveAxon 1 )
			) 500 )
		)
	)
)>


Nucleus<(
	:Init ( :Init_Nucleus )

	:Create_Axon ( )
	:Nucleus_Cycle ( )
	:Soma ( )
)>

Nucleus_Cycle<(
	inf ( ( #ActiveNucleus 1 ) (
			add ( @ImpulseStk @Impulse )
			set ( @Impulse 0 )
			sup ( ( @ImpulseStk #Biais ) (
					set ( #ActiveNucleus 1 )
					add ( @ImpulseStk #ImpulseWeight )
					set ( @IsNegNucleus 0 )
				)
			)
		)
	)
)>

