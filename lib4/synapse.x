Synapse|Construct<(
	set ( !tmp mod ( rand 10 ) ) 
	set ( !tmp sub ( !tmp 5.0 ) )

	[ ATTRIBUTS ]
	(
		cp ( * ( #this /_weight ) !tmp )
		cp ( * ( #this /_from ) #__av__^0 )
		cp ( * ( #this /_pre ) 0 )
		cp ( * ( #this /_value ) 0 )
	)
	[ MEMBERS ]
	(
		cp ( * ( #this /Exec ) :Synapse|Exec )
	)
)>

Synapse|Exec<(
	set ( !val * ( * ( #this /_pre ) /_output ) )
	set ( !val mult ( * ( #this /_weight ) !val ) )
	set ( * ( #this /_value ) !val )
)>
