Init_Neuron<(
	:Init ( (
			cp ( #__Neuron :Neuron|Construct )
			cp ( #__Synapse :Synapse|Construct )
			cp ( #__Layer :Layer|Construct )
			cp ( #__Brain :Brain|Construct )
		)
	)
)>

TEST_NEURON<(
	:Init_Std
	:Init_Neuron

	inf ( ( !it 1 ) (
			set ( !it 1 )

			?c_!brain?. % ( #__Brain )?__

			?_!brain?. /AddLayer ?:( 3 )?__
			?_!brain?. /Generate ?:( 2 1 )?__
		)
	)
	cp ( * ( !brain^_input^_neuron^_data^0 /_output ) mod ( rand 10 ) )
	cp ( * ( !brain^_input^_neuron^_data^1 /_output ) mod ( rand 10 ) )

	?_!brain?. /Exec ?: ?__

	echo ( * ( !brain^_output^_neuron^_data^0 /_output ) 10 )
)>
