Cytosol_Init<
	inf ( @init 1 add ( @init 1 )
		:Skl_Arround
		:Cytosol_Chan
		set ( @CytoChan 10 )
	)
>

Cytosol<
0 (
	:Cytosol_Init
	sup ( @IMPULSE 0 add ( @EXIT @IMPULSE ) set ( @IMPULSE 0 ) )
)
>
