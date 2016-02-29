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

[
	# Merge two array
	( %Array ) -> (void)
]

Array|ForEach<(
	cp ( !F #__av__^0 )
	call ( * ( !F ) 0 ( % ( * ( #this /_data !it ) ) ) )
	set ( !it add ( !it 1 ) )
	inf ( ( !it * ( #this /_size ) ) (
			call ( * ( #this /ForEach ) 0 ( !F ) )
		)
	)
	set ( !it sub ( !it 1 ) )
)>

Array|Erase<(
	
)>

Array|Merge<(
)>

Array|Clear<(
	cp ( * ( #this /_data ) 0 )
)>
