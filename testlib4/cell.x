TEST<(
	:Init ( (
		shared ( /CellId )
		add ( @CellId 1 )
		set ( #it @CellId )
		set ( @ ( /ImCell #it ) 90 )
		set ( #limit 100 )
		add ( #limit #it )
		add ( #limit #it )
		set ( @Dopamine #it )
		mult ( @Dopamine 2 )
		cp ( &Rpls 0 (
				20 0 50
				?act (
					( ?need ( @ImCell^0 ) )
					( ?need ( @ImCell^0 ) )
				)
				?mv ?oth ?rpls	
			)
		)
		cp ( & ( /Rpls ?act 0 ?need 0 1 ) #it )
		cp ( & ( /Rpls ?act 1 ?need 0 1 ) #it )
	) )
	and ( (
			sup ( ( !it #limit ) ) 
			inf ( ( #it 5 ) )
		) (
			duplic
			set ( !it 0 )
		)
	)
	add ( !it 1 )
)>
