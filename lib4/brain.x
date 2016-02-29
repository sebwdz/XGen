Brain|Construct<(
	[ ATTRIBUT ]
	(
		?c_ * ( #this /_input )?. % ( #__Layer )?__
		?c_ * ( #this /_output )?. % ( #__Layer )?__
		?c_ * ( #this /_layers )?. % ( #__Array )?__
		cp ( * ( #this /_link ) 0 )
		cp ( * ( #this /_id ) 0 )
		cp ( * ( #this /_execLayer ) :Brain|ExecLayer )
	)
	[ MEMBER ]
	(
		cp ( * ( #this /Generate ) :Brain|Generate )
		cp ( * ( #this /AddLayer ) :Brain|AddLayer )
		cp ( * ( #this /Exec ) :Brain|Exec )
	)
)>

Brain|Generate<(
	set ( !input #__av__^0 )
	set ( !output #__av__^1 )
	?_ * ( #this /_input )?. /Generate ?:( !input )?__
	?_ * ( #this /_output )?. /Generate ?:( !output )?__
	cp ( !prev % ( * ( #this /_input ) ) )
	set ( !it 0 )
	while ( or ( (
			inf ( ( !it * ( #this /_layers /_size ) ) )
		) ) (
			cp ( !cur * ( #this /_layers /_data !it ) )
			?_ * ( !cur )?. /Plug ?:( !prev )?__
			cp ( !prev !cur )
			set ( !it add ( !it 1 ) )
		)
	)
	?_ * ( #this /_output )?. /Plug ?:( !prev )?__
)>

Brain|AddLayer<(
	set ( !nb #__av__^0 )

	cp ( !layer call ( #__new__ ) )
	?c_ * ( !layer )?. % ( #__Layer )?__
	?_ * ( !layer )?. /Generate ?:( !nb )?__
	?_ * ( #this /_layers )?. /Push ?:( !layer )?__
)>

Brain|ExecLayer<(
	cp ( !layer #__av__^0 )
	?_ * ( * ( !layer ) )?. /Exec ?: ?__
)>

Brain|Exec<(
	sup ( ( * ( #this /_link ) 0 ) (
			?_ * ( #this /_input )?. /Exec ?: ?__
		)
	)
	?_ * ( #this /_layers )?. /ForEach ?:( % ( * ( #this /_execLayer ) ) )?__
	?_ * ( #this /_output )?. /Exec ?: ?__
)>
