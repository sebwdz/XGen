Init_Axon<(
	set ( @ImAxonHead 10 )

	:Make_Rpls_Mv ( &RplsCell to @ImAxonHead @ImCell )
	set ( &RplsCell^?pw 10 )
	set ( &RplsCell^?scope 0 ( ?link ) )
)>

Install_Axon<(
	inf ( ( #install 1 ) (
			:Make_Link (
				&LinkCell @ImAxonHead @ImCell
				20 #install
			)
		) ( :Init ( set ( &RplsCell^?dst 20 ) ) )
	)
)>

Exec_Axon<(
	sup ( ( #install 0 ) (
			
		)
	)
)>

Axon<(
	:Init ( :Init_Axon )
	:Install_Axon
	:Exec_Axon
)>
