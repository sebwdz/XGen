
Layer|Construct<(
	[ ATTRIBUTS ]
	(
		?c_* ( #this /_neuron )?. % ( #__Array )?__
		cp ( * ( #this /_execNeuron ) :Layer|ExecNeuron )
	)
	[ MEMBERS ]
	(
		cp ( * ( #this /Generate ) :Layer|Generate )
		cp ( * ( #this /Plug ) :Layer|Plug )
		cp ( * ( #this /Exec ) :Layer|Exec )
	)
)>

Layer|Generate<(
	set ( !it 0 )
	set ( !nb #__av__^0 )

	while ( or ( ( inf ( ( !it !nb ) )
		) ) ( 
			cp ( !neuron call ( #__new__ ) )
			?c_* ( !neuron )?. % ( #__Neuron )?__
			?_* ( #this /_neuron )?. /Push ?:( !neuron )?__
			set ( !it add ( !it 1 ) )
	) )
)>

Layer|Plug<(
	set ( !it 0 )
	cp ( !layer #__av__^0 )

	while ( or ( ( inf ( ( !it * ( #this /_neuron /_size ) ) )
  	) ) (
			set ( !it2 0 )
			cp ( !cur * ( #this /_neuron /_data !it ) )
			while ( or ( ( inf ( ( !it2 * ( !layer /_neuron /_size ) ) )
				) ) (
					?_* ( !cur )?. /AddInput ?:( * ( !layer /_neuron /_data !it2 ) )?__
					set ( !it2 add ( !it2 1 ) )
			) )
			set ( !it add ( !it 1 ) )
	) )
)>

Layer|ExecNeuron<(
	cp ( !neuron #__av__^0 )
	?_* ( * ( !neuron ) )?. /Exec ?: ?__
)>

Layer|Exec<(
	?_* ( #this /_neuron )?. /ForEach ?: ( % ( * ( #this /_execNeuron ) ) )?__
)>
