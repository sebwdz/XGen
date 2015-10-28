Test<(
	add ( @x :Node1 )
	add ( :Node2 @x )
)>

Node1<(
	inf ( ( @x2 10 ) return ( 8 ) )
	return ( 10 )
)>

Node2<(
	inf ( ( @x3 10 ) return ( @x4 ) )
	return ( @x5 )
)>
