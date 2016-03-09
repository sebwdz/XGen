
[
	Link ( Value Next Prev )
]

LinkList|Construct<(
	cp (* (#this /_begin) 0)
	cp (* (#this /_end) 0)
	cp (* (#this /_size) 0)

	cp (* (#this /Push_Back) :LinkList|Push_Back)
	cp (* (#this /Push_Front) :LinkList|Push_Front)
	cp (* (#this /Insert) :LinkList|Insert)

	cp (* (#this /Pop_Back) :LinkList|Pop_Back)
	cp (* (#this /Pop_Front) :LinkList|Pop_Front)
	cp (* (#this /Erase) :LinkList|Erase)
	cp (* (#this /Clear) :LinkList|Clear)

	cp (* (#this /ForEach) :LinkList|ForEach)
)>

LinkList|Push_Back<(
	cp (!tmp #__av__^0)
	?_* (#this)?. /Insert?:(* (#this /_end) !tmp)))
)>

LinkList|Push_Front<(
	cp ( !tmp #__av__^0 )
	?_ * ( #this ) ?. /Insert ?: ( 0 !tmp ) ) ) )
)>

LinkList|Insert<(
	egal ( ( #__av__^0 0 ) (
			cp ( !next * ( #this /_begin ) )
		) ( cp ( !next * ( #__av__ ( 0 ) 1 ) ) )
	)
	cp ( !link call ( #__new__ ) )
	cp ( * ( !link 0 ) #__av__^1 )
	cp ( * ( !link 2 ) #__av__^0 )
	cp ( * ( !link 1 ) !next )
	sup ( ( !next 0 ) (
			cp ( * ( !next 2 ) !link )
	) )
	egal ( ( #__av__^0 * 0 )
		( cp ( * ( #this /_begin ) !link ) )
		( cp ( * ( #__av__^0 1 ) !link ) )
	)
	egal ( ( #__av__^0 * ( #this /_end ) )
		( cp ( * ( #this /_end ) !link ) )
	)
	set ( * ( #this /_size ) add ( * ( #this /_size ) 1 ) )
)>

LinkList|Pop_Back<(
	?_ * ( #this ) ?. /Erase ?: ( * ( #this /_end ) ) ) )
)>

LinkList|Pop_Front<(
	?_ * ( #this ) ?. /Erase ?: ( * ( #this /_begin ) ) ) )
)>

LinkList|Erase<(
	cp ( !lst #__av__^0 )
	egal ( ( !lst * ( #this /_begin ) ) (
		cp ( * ( #this /_begin ) * ( !lst 1 ) )
	) )
	egal ( ( !lst * ( #this /_end ) ) (
		cp ( * ( #this /_end ) * ( !lst 2 ) )
	) )
	sup ( ( * ( !lst 1 ) 0 ) (
			cp ( * ( * ( !lst 1 ) 2 ) * ( !lst 2 ) )
	) )
	sup ( ( * ( !lst 2 ) 0 ) (
			cp ( * ( * ( !lst 2 ) 1 ) * ( !lst 1 ) )
	) )
	set ( * ( #this /_size ) sub ( * ( #this /_size ) 1 ) )
)>

LinkList|Clear<(
	cp ( * ( #this /_begin ) 0 )
	cp ( * ( #this /_end ) 0 )
	cp ( * ( #this /_size ) 0 )
)>

LinkList|ForEach<(
	cp ( !av #__av__ )
	cp ( !tmp * ( #this /_begin ) )
	while ( no ( ( egal ( ( !tmp 0 ) )
		) ) (
			cp ( !val * ( !tmp 0 ) )
		 	call ( * ( !av^0 ) 0 ( % ( !val ) ) )
		 	cp ( !tmp * ( !tmp 1 ) )
	) )
)>