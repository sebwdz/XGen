
Exec<(
	and ( (
			sup ( ( @Value 0 ) )
			sup ( ( * ( #__oth__ /Value ) 0 ) )
		) (
			set ( @_Result 1 )
			set ( * ( #__oth__ /A ) add ( * ( #__oth__ /A ) 50 ) )
			set ( * ( #__oth__ /__pos__ 0 ) add ( * ( #__oth__ /__pos__ 0 ) mult ( #__vct__^0 2 ) ) )
			set ( * ( #__oth__ /__pos__ 1 ) add ( * ( #__oth__ /__pos__ 1 ) mult ( #__vct__^1 2 ) ) )
[			echo ( 72 69 89 32 * ( #__oth__ /__pid__ ) 10 )]
		)
	)
)>

Clean<(
	set ( * ( #this /_param ?limit 0 )
		sub ( * ( #this /_param ?limit 0 ) 1 )
	)
)>

Manager|Process<(
	:Init_Std
	:Process|Init
	:Init ( (
		cp ( #__Interaction :Interaction|Construct )
		?c_&Interaction?. % ( #__Interaction )?__
    cp ( &Interaction^_exec :Exec )
    cp ( &Interaction^_clean :Clean )
    cp ( &Interaction^_param 0 ( 40 0 ?scope ( ?oth ) ?manual ?limit ( 0 ) ) )
		set ( @__pos__^0 5 )
		set ( @__pos__^1 5 )
		move
		set ( @A 50 )
	) )
	set ( @Impulse @A )
	sup ( ( @A 50 ) ( set ( @A 50 ) ) )
	sup ( ( @A 0 ) ( set ( !kill 0 ) ) )
	inf ( ( set ( @A sub ( @A 0.05 ) ) 0 ) ( set ( @A 0 ) ) )
	inf ( ( !i 1 ) (
			cp ( !vct 0 ( 1 1 ) )
			set ( !vct^0 sub ( div ( mod ( rand 100 ) 50 ) 1 ) )
			set ( !vct^1 sub ( div ( mod ( rand 100 ) 50 ) 1 ) )
		)
	)
	sup ( ( set ( !i add ( !i 1 ) ) 50 ) (
			?_&Interaction?. /Exec ?:( 1 )?__
			set ( @Value 5 )
			set ( !i 0 )
		)
	)
	[:Manager|Exec]
	sup ( ( set ( !time add ( !time 1 ) ) 10 ) (
			set ( @__pos__^0 add ( @__pos__^0 !vct^0 ) )
			set ( @__pos__^1 add ( @__pos__^1 !vct^1 ) )
			move
			set ( !time 0 )
		)
	)
[	sup ( ( set ( !kill add ( !kill 1 ) ) 200 ) ( kill ) ) )]
)>

MAIN<(
	:Init_Std
	:Process|Init

	:Init ( (
			creat ( 0 ( :Manager|Process ) )
			creat ( 0 ( :Manager|Process ) )
			set ( @Value 2 )
			cp ( #__Interaction :Interaction|Construct )
			cp ( #__NewProcess :Process|New_Process )
	) )
	inf ( ( @_Result 1 ) (
			sup ( ( set ( !time add ( !time 1 ) ) 200 ) (
					inf ( ( &Interaction^param^?limit^0 1 ) (
							?_&Interaction?. /Exec ?:( 1 )?__
						)
					)
					set ( !time 0 )
				)
			)
		) ( set ( @_Result 0 ) )
	)
	sup ( ( set ( !crtT add ( !crtT 1 ) ) 100 ) (
			inf ( ( !crt 20 ) (
					creat ( 0 ( :Manager|Process ) )
					set ( !crt add ( !crt 1 ) )
				) ( kill )
			)
			set ( !crtT 0 )
		)
	)
)>