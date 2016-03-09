[
	#
	# Object Array 
	#
]

[
	# Construct Array
	(void) -> (void)
]

Array|Construct<(
	[ ATTRIBUTS ]
	(
		cp ( * ( #this /_data ) #__av__ )
		cp ( * ( #this /_size ) len ( #__av__ ) )

		cp ( * ( #this /_new ) % ( #__Array ) )
	)
	[ MEMBERS ]
	(
		cp ( * ( #this /Push ) :Array|Push )
		cp ( * ( #this /Pop ) :Array|Pop )

		cp ( * ( #this /Erase ) :Array|Erase )
		cp ( * ( #this /Clear ) :Array|Clear )

		cp ( * ( #this /ForEach ) :Array|ForEach )
		cp ( * ( #this /Cmp ) :Array|Cmp )

		cp ( * ( #this /Sub ) :Array|Sub )
		cp ( * ( #this /Split ) :Array|Split )
		cp ( * ( #this /Copy ) :Array|Copy )
	)
)>

[
	# Push elm to array
	( elm ) -> (void)
]

Array|Push<(
	set ( !i 0 )
	set ( !it * ( #this /_size ) )
	set ( !len len ( #__av__ ) )
	set ( * ( #this /_size ) add ( !it !len ) )
	while ( or ( ( inf ( ( !i !len ) )
		) ) (
			set ( !x add ( !it !i ) )
			cp ( * ( #this /_data !x ) #__av__ ( !i ) )
			set ( !i add ( !i 1 ) )
	) )
)>

[	# Pop elm from array 
	( %elm ) -> (void)
]

Array|Pop<(
	set ( !it sub ( * ( #this /_size ) 1 ) )
	set ( * ( #this /_size ) !it )
	cp ( * ( #__av__^0 ) * ( #this /_data !it ) )
)>

Array|ForEach<(
	set ( !it 0 )
	cp ( !F #__av__^0 )
	set ( !len * ( #this /_size ) )
	while ( or ( ( inf ( ( !it !len ) )
		) ) (
				call ( * ( !F ) 0 ( % ( * ( #this /_data !it ) ) !it ) )
				set ( !it add ( !it 1 ) )
	) )
)>

Array|Cmp<(
	set ( !it 0 )
	egal ( ( * ( #__av__^0 /_size ) * ( #this /_size ) ) (
		set ( !len * ( #this /_size ) )
		while ( or ( ( inf ( ( !it !len ) )
			) ) (
				no ( (
						egal ( ( * ( #this /_data !it ) * ( #__av__^0 /_data !it ) ) )
				) ( ret ( 0 ) ) )
				set ( !it add ( !it 1 ) )
		) )
	) ( ret ( 0 ) ) )
	ret ( 1 )
)>

[
	# Erase case of array
	(int) -> (void)
]

Array|Erase<(
	erase ( * ( #this /_data ) #__av__^0 )
	set ( * ( #this /_size ) sub ( * ( #this /_size ) 1 ) )	
)>
[
	# Clear all array
	(void) -> (void)
]

Array|Clear<(
	set ( * ( #this /_size ) 0 )
)>

[
	# Return sub array
	(int ?int?) -> %Array
]

Array|Sub<(
	set ( !it #__av__^0 )
	set ( !len #__av__^1 )
	set ( !i 0 )
	cp ( !tmp 0 )
	cp ( !res call ( #__new__ ) )
	?c_ * ( !res ) ?. * ( #this /_new ) ) )
	inf ( ( !len 1 )
		( set ( !len sub ( * ( #this /_size ) !it ) ) )
	)
	while ( or ( ( inf ( ( !i !len ) )
		) ) (
			cp ( !tmp ( !i ) * ( #this /_data !it ) )
			set ( !it add ( !it 1 ) )
			set ( !i add ( !i 1 ) )
	) )
	cp ( * ( !res /_data ) !tmp )
	set ( * ( !res /_size ) !len )
	ret ( !res )
)>

Array|Split<(
	set ( !char #__av__^0 )
	set ( !limit #__av__^1 )
	set ( !cur 0 )
	set ( !size * ( #this /_size) )
	set ( !it 0 )
	set ( !last 0 )

	while ( or ( ( inf ( ( !it !size ) )
		) ) (
			egal ( ( * ( #this /_data !it ) !char ) (
				cp ( !res ( !cur ) ?_ * ( #this ) ?. /Sub ?: ( !last sub ( !it !last ) ) ) ) )
				set ( !cur add ( !cur 1 ) )
				set ( !last add ( !it 1 ) )
				sup ( ( !limit 0 ) (
					sup ( ( add ( !cur 1 ) !limit ) (
						cp ( !res ( !limit ) ?_ * ( #this ) ?. /Sub ?: ( !last ) ) ) )
						ret ( !res )
					) )
				) )
			) )
			set ( !it add ( !it 1 ) )
	) )
	cp ( !res ( !cur ) ?_ * ( #this ) ?. /Sub ?: ( !last ) ) ) )
	ret ( !res )
)>

Array|Copy<(
	cp ( !res call ( #__new__ ) )
	?c_ * ( !res ) ?. * ( #this /_new ) * ( #this /_data ) ) )
	ret ( !res )
)>
