
Neuron|Construct<(
	set ( !tmp mod ( rand 10 ) )
	set ( !tmp sub ( !tmp 5.0 ) )

	[ ATTRIBUTS ]
	(
		?c_* ( #this /_synapses )?. % ( #__Array )?__
		cp ( * ( #this /_output ) 0 )
		cp ( * ( #this /_input ) 0 )
		cp ( * ( #this /_biais ) !tmp )
	)
	[ MEMBERS ]
	(
		cp ( * ( #this /AddInput ) :Neuron|AddInput )
		cp ( * ( #this /Exec ) :Neuron|Exec )
	)
)>

Neuron|AddInput<(
	cp ( !from #__av__^0 )
	cp ( !syn call ( #__new__ ) )
	call ( #__construct__ 0 ( !syn % ( #__Synapse ) 0 ( #this ) ) )
	cp ( * ( !syn /_pre ) !from )
	?_* ( #this /_synapses )?. /Push ?:( !syn )?__
)>

Neuron|Exec<(
	set ( !input 0 )
	set ( !it 0 )
	while ( or ( (
			inf ( ( !it * ( #this /_synapses /_size ) ) )
		) ) (
			cp ( !sin * ( #this /_synapses /_data !it ) )
			?_* ( !sin )?. /Exec ?: ?__
			set ( !input add ( * ( !sin /_value ) !input ) )
			set ( !it add ( !it 1 ) )
	) )
	set ( !input call ( :Math|Sigmoide 0 ( sub ( !input * ( #this /_biais ) ) ) ) )
	set ( * ( #this /_output ) !input )
)>
