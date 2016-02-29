[
	#
	#	Basic function of std
	#
]


[
	# Copy Functions to Variable # 
]

Init_Std<(
	:Init ( (
			[ Basic Function ]
			cp ( #__construct__ :__construct__ )
			cp ( #__obj__ :__obj_call__ )
			cp ( #__new__ :__new__ )

			[ Object ]
			cp ( #__Array :Array|Construct )
		)
	)
)>

Init($code)<(
	inf ( ( !it 1 ) ( $code set ( !it 1 ) ) )
)>

__new__<(
	cp ( !local 0 ( 0 ) )
	cp ( !ptr % ( !local^0 ) )
	ret ( !ptr )
)>
