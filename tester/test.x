MAIN<(
	inf ( ( #turn 1 ) (
			inf ( ( #it 1 ) (
					inf ( ( @limit 1 ) ( set ( @limit 50 ) ) )
					shared ( /CRT /limit )
					set ( @A^A 10 )
					cp ( &Rpls 0 (
         			               		8 0 60
                        				0 ( @A^A @A^A )
                        				?mv ?oth ?rpls
                				)
        				)
					set ( #it 1 )
				)
			)
			add ( !time 1 )
			sup ( ( !time @limit ) (
					mult ( @limit 1 )
					inf ( ( @CRT 11 ) (
							add ( @CRT 1 )
							duplic
						) ( set ( #turn 1 ) )
					)
					set ( !time 0 )
				)
			)
		)
	)
)>
