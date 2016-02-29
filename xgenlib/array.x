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
		cp ( * ( #this /_data ) 0 )
		cp ( * ( #this /_size ) 0 )
	)
	[ MEMBERS ]
	(
		cp ( * ( #this /Push ) :Array|Push )
		cp ( * ( #this /Pop ) :Array|Pop )
		cp ( * ( #this /Merge ) :Array|Merge )
		cp ( * ( #this /Erase ) :Array|Erase )
		cp ( * ( #this /ForEach ) :Array|ForEach )
		cp ( * ( #this /Clear ) :Array|Clear )
		cp ( * ( #this /Sub ) :Array|Sub )
		cp ( * ( #this /Split ) :Array|Split )
	)
)>

[
	# Push elm to array
	( elm ) -> (void)
]

Array|Push<(
	set ( !it * ( #this /_size ) )
	set ( * ( #this /_size ) add ( !it 1 ) )
	cp ( * ( #this /_data !it ) #__av__^0 )
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
	cp ( !F #__av__^0 )
	call ( * ( !F ) 0 ( % ( * ( #this /_data !it ) ) ) )
	set ( !it add ( !it 1 ) )
	inf ( ( !it * ( #this /_size ) ) (
			call ( * ( #this /ForEach ) 0 ( !F ) )
	) )
	set ( !it sub ( !it 1 ) )
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
	# Merge two array
	( %Array ) -> (void)
]

Array|Merge<(
	set ( !it 0 )
	set ( !size * ( #this /_size ) )
	set ( !size2 * ( #this /_size ) )
	while ( or ( ( inf ( ( !it !size2 ) )
		) ) (
			cp ( * ( #this /_data add ( !it !size ) ) * ( #__av__^0 /_data !it ) )
	) )
	set ( * ( #this /_size ) add ( !size !size2 ) )
)>

[
	# Clear all array
	(void) -> (void)
]

Array|Clear<(
	cp ( * ( #this /_data ) 0 )
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
	?c_ * ( cp ( !res call ( #__new__ ) ) ) ?. % ( #__Array ) ) )
	inf ( ( !len 1 )
		( set ( !len * ( #this /_size ) ) )
		( set ( !len add ( !len !it ) ) )
	)
	while ( or ( ( inf ( ( !it !len ) )
		) ) (
			cp ( !tmp ( !i ) * ( #this /_data !it ) )
			set ( !it add ( !it 1 ) )
			set ( !i add ( !i 1 ) )
	) )
	cp ( * ( !res /_data ) !tmp )
	set ( * ( !res /_size ) len ( !tmp ) )
	ret ( !res )
)>

Array|Split<(
	set ( !char #__av__^0 )
	set ( !limit #__av__^1 )
	set ( !cur 0 )
	set ( !size * ( #this /_size) )
	set ( !it 0 )

	while ( or ( ( inf ( ( !it !size ) ) 
		) ) (
			set ( !it add ( !it 1 ) )
	) )
)>