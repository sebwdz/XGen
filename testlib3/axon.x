Init_Axon<(
	set ( @ImAxonHead 10 )
	set ( @IsNegAxon 10 )

	:Make_Rpls_Mv ( &RplsCell ?to @ImAxonHead @ImSoma )
	set ( &RplsCell^?pw 10 )
	cp ( &RplsCell^?scope ?scope ( ?link ) )
)>

Install_Axon<(
	inf ( ( #install 1 ) (
			:Make_Link (
				&LinkCell @ImSoma @Block
				20 #install
			)
			cp ( &LinkCell^?scope ?scope ( ?oth ) )
		) ( :Init ( set ( &RplsCell^?dst 25 ) ) )
	)
)>

Exec_Axon<(
	sup ( ( #install 0 ) (
			sup ( ( @Impulse 0 ) ( sub ( @Impulse 1 ) ) )
		)
	)
)>

Axon<(
	:Init ( :Init_Axon )
	:Install_Axon
	:Exec_Axon
)>
