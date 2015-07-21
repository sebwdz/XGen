Link_Head<
0 (
	var (
		&RplsCytosol (
			type ( mv to rpls )
			act ( @HeadLink @CytoChan )
			dst ( 10 )
			pw ( 5 )
		)
		&AtrExit (
			type ( mv to atr )
			act ( @HeadLink @EXIT )
			dst ( 50 )
			pw ( 0 )
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
			dst ( 40 )
			pw ( 0 )
		)
	)
	set ( @HeadLink 10 )
	set ( @Head 10 )
)
>

Link_Base<
0 (
	var (
		&AtrCytosol (
			type ( mv to atr )
			act ( @BaseLink @CytoChan )
			dst ( 15 )
			pw ( 50 )
		)
		&RplsHead (
			type ( mv oth rpls )
			act ( @Base @Head )
			dst ( 10 )
			pw ( 10 )
		)
	)
	set ( @BaseLink 10 )
	set ( @Base 10 )
)
>

Link<
0 (
	inf ( @itLink 1
		unuse ( @Base @Head )
		new_head ( :Link_Head )
		new_head ( :Link_Base )
	)
	add ( @itLink 1 )
)
>
