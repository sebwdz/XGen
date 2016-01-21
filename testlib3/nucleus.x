Init_Nucleus<(
	set ( @IsNegNucleus 10 )

	set ( #Biais 50 )
	set ( #ImpulseWeight 30 )
	set ( #Speed 40 )

)>

Create_Axon<(
	inf ( ( #HaveAxon 1 ) (
			:Cycle ( (
				creat ( :Axon )
				set ( #HaveAxon 1 )
			) 200 )
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
