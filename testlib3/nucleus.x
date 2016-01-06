Init_Nucleus<(
	set ( @IsNegNucleus 10 )

	set ( #Biais 50 )
	set ( #AxonWeight 20 )

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

	:Create_Axon
	[:ChangeTo ( @Impulse #ImpulseStk )
	sup ( ( #ImpulseStk #Biais ) (
			set ( #ActiveNucleus 1 )
			set ( @IsNegNucleus 0 )
		)
	)]
	:Nucleus_Cycle
)>

Nucleus_Cycle<(
	sup ( ( #ActiveNucleus 0 ) (
			[sup ( ( #ImpulseStk #AxonWeight )
				( add ( @GiveImpulse #AxonWeight ) )
				( add ( @GiveImpulse #ImpulseStk ) )
			)
			sub ( #ImpulseStk #AxonWeight )
			inf ( ( #ImpulseStk 1 ) (
					set ( #ActiveNucleus 0 )
					set ( @IsNegNucleus 10 )
				)
			)]
		)
	)
)>
