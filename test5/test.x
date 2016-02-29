Exec<(
	sup ( ( * ( #__oth__ /User ) 0 ) (
			inf ( ( #__vct__^2 25 ) (
					sup ( ( * ( #this /_go ) 0 ) (
							set ( * ( #this /_go ) 0 )
							set ( @_put 1 )
						)
					)
				)
			)
			set ( * ( #this /_ok ) 1 )
		)
	)
)>

Clean<(
	sup ( ( * ( #this /_param ?limit 0 ) 0 ) (
			inf ( ( * ( #this /_ok ) 1 ) (
					set ( * ( #this /_go ) 1 )
				)
			)
			set ( * ( #this /_param ?limit 0 ) 0 )
			set ( * ( #this /_ok ) 0 )
		)
	)
)>

Link<(
	sup ( ( * ( #__oth__ /BTN ) 0 ) (
			cp ( @RON % ( * ( #__oth__ /ON ) ) )
			set ( * ( #this /_param ?limit 0 ) 0 )
		)
	)
)>

User<(
	:Init_Std
	:Init ( (
		cp ( @__pos__ 0 ( -100 0 ) )
		set ( @User 1 )
		cp ( #vct 0 ( -0.5 0 ) )
		move
	) )
	sup ( ( @__pos__^0 100 ) (
			cp ( #vct 0 ( -0.5 0 ) )
		) ( inf ( ( @__pos__^0 -90 ) ( cp ( #vct 0 ( 0.5 0 ) ) ) ) )		
	)
	set ( @__pos__^0 add ( @__pos__^0 #vct^0 ) )
	set ( @__pos__^1 add ( @__pos__^1 #vct^1 ) )
	move
)>


MAIN<(
	:Init_Std
	:Process|Init

	creat ( 0 ( :ROOM ) )
	creat ( 0 ( :User ) )
	kill
)>

LIGHT<(
	:Init_Std
	:Init ( (
		set ( @__pos__^0 mod ( rand 100 ) )
		set ( @__pos__^1 mod ( rand 100 ) )
		set ( @__pos__^1 sub ( @__pos__^1 50 ) )
		move

		?c_&Interaction?. % ( #__Interaction )?__
                cp ( &Interaction^_exec :Link )
                cp ( &Interaction^_param 0 ( 200 0 ?scope ( ?oth ) ?manual ?limit ( 1 ) ) )
	) )
	set ( @DopamineAct * ( @RON ) )
)>

ROOM<(
	:Init ( ( new_head ( 0 ( :BTN ) ) ) )
	inf ( ( !l 10 ) ( set ( !l add ( !l 1 ) ) new_head ( 0 ( :LIGHT ) ) ) )
)>

BTN<(
	set ( !a 10 )
	set ( ! ( /a ) 10 )
	inf ( ( !a 10 ) (
			[ code ]
		) (
			[ code ]
		)
	)
	:Init_Std
	:Init ( (
		set ( @BTN 10 )
		cp ( @__pos__ 0 ( 0 -5 ) )
		move

		?c_&Interaction?. % ( #__Interaction )?__
                cp ( &Interaction^_exec :Exec )
                cp ( &Interaction^_clean :Clean )
                cp ( &Interaction^_param 0 ( 30 0 ?scope ( ?oth ) ?manual ?limit ( 1 ) ) )
	) )
	inf ( ( &Interaction^_param^?limit^0 1 ) (
                        sup ( ( set ( !time add ( !time 1 ) ) 1 ) (
                                        ?_&Interaction?. /Exec ?:( 1 )?__
                                        set ( !time 0 )
                                )
                        )
                )
        ) 
	sup ( ( @_put 0 ) (
			sup ( ( @ON 0 ) ( set ( @ON 0 ) ) ( set ( @ON 10 ) ) )
			set ( @_put 0 )
		)
	)
	sup ( ( set ( !out add ( !out 1 ) ) 100 ) (
			:Init ( ( take_out ) )
		)
	)
)>
