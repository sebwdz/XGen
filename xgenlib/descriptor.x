
<
	?Descriptor 	2;
>

Descriptor|Construct<(
	?c_ * ( #this ) ?. % ( #__Class ) ) )

	cp ( * ( #this /Init ) :Descriptor|Init )

	set ( * ( #this ) ?Descriptor )
)>

Descriptor|Init<(
	:Class|Init
	
	cp ( * ( #this /_lc ) % ( # ) )
)>