Link_Head<
0 (
	inf ( @it 1
		var (
			&RplsCytosol (
				type ( mv to rpls )
				act ( @HeadLink @CytoChan )
				dst ( 10 )
				pw ( 5 )
			)
			&RplsHead (
				type ( mv to rpls )
				act ( @HeadLink @HeadLink )
				dst ( 30 )
				pw ( 10 )
			)
			&RplsNucleus (
				type ( mv oth rpls )
				act ( @HeadLink @NclChan )
				dst ( 20 )
				pw ( 0 )
			)
			&AtrImpulse (
				type ( oth chng atr )
				act ( @Head @AtrImpulse )
				dst ( 90 )
				pw ( 90 )
			)
		)
		set ( @it 1 )
	)
	sup ( @AtrImpulse 0
		add ( @Impulse @AtrImpulse )
		set ( @AtrImpulse 0 )
	)
	set ( @HeadLink 10 )
	set ( @Head 10 )
)
>

Link_Base<
0 (
	inf ( @it 1
		var (
			&AtrCytosol (
				type ( mv to atr )
				act ( @BaseLink @CytoChan )
				dst ( 15 )
				pw ( 50 )
			)
			&RplsHead (
				type ( mv oth rpls )
				act ( @BaseLink @Head )
				dst ( 40 )
				pw ( 30 )
			)
			&AtrImpulse (
				type ( chng oth atr )
				act ( @Base @Impulse )
				dst ( 40 )
				pw ( 0 )
			)
			&AtrExec (
				type ( chng oth atr )
				act ( @Base @ExecNcl )
				dst ( 40 )
				pw ( 100 )
			)
		)
		set ( @it 1 )
	)
	sup ( @ExecNcl 0
		add ( @wait @ExecNcl )
		set ( @ExecNcl 0 )
	)
	inf ( @wait 1 var ( &AtrImpulse ( pw ( 0 ) ) ) )
	sup ( @wait 1
		var ( &AtrImpulse ( pw ( 20 ) ) )
		sub ( @wait 3 )
	)
	sup ( @Impulse 0 add ( @AtrImpulse @Impulse ) set ( @Impulse 0 ) )
	set ( @BaseLink 10 )
	set ( @Base 10 )
)
>

Link<
0 (
	inf ( @itLink 1
		unuse ( @Head @AtrImpulse )
		new_head ( :Link_Head )
		new_head ( :Link_Base )
	)
	add ( @itLink 1 )
)
>
