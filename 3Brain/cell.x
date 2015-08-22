Cell<
0 (
	:Cell_Init
	inf ( @cellInit 10
		add ( @cellInit 1 )
	)
)
>

Cell_Init<
0 (
	inf ( @cellInit 1
		shared ( @CellDuplic )
		sup ( @CellDuplic 0
			:Cell_Base_Chan
		)
		add ( @CellDuplic 1 )
	)
	:Duplic_Cell
)
>

Duplic_Cell<
0 (
	inf ( @CellDuplic 2
		inf ( @cellCreate 80
			sup ( @waitCreate 5
				duplic ( )
				add ( @cellCreate 1 )
				set ( @waitCreate 0 )
			)
			set ( @Impulse 10 )
			add ( @waitCreate 1 )
		)
	)
)
>
