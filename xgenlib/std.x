[
	#
	#	Basic function of std
	#
]


[
	# Copy Functions to Variable # 
]

<
	?Init 		inf ( ( !__init__ 1 ) (;
	?ie__			set ( !__init__ 1 ) ) );
>

Init_Std<(
	:Init ( (
			[ Basic Function ]
			cp ( #__construct__ :__construct__ )
			cp ( #__obj__ :__obj_call__ )
			cp ( #__new__ :__new__ )
			cp ( #__push__ :__push__ )
			cp ( #__pop__ :__pop__ )

			[ Object ]
			cp ( #__Array :Array|Construct )
			cp ( #__Interaction :Interaction|Construct )
	) )
)>

Init($code)<(
	inf ( ( !it 1 ) ( $code set ( !it 1 ) ) )
)>

__new__<(
	cp ( !local 0 ( 0 ) )
	cp ( !ptr % ( !local^0 ) )
	ret ( !ptr )
)>

count<(
	set ( !it 0 )
	set ( !len len ( * ( #__av__^0 ) ) )
	set ( !res 0 )

	while ( or ( ( inf ( ( !it !len ) )
		) ) (
			egal ( ( * ( #__av__^0 !it ) #__av__^1 )
				( set ( !res add ( !res 1 ) ) )
			)
			set ( !it add ( !it 1 ) )
	) )
	ret ( !res )
)>
