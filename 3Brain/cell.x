[ #0 => init state cell ]

[ Main node ]

Cell<
0 (
	:Cell_Init
	inf ( #0 1 add ( #0 10 ) )
	:Duplic_Cell
)
>


[ function need to init cell ]

Cell_Init<
0 (
	inf ( #0 1
		set ( @ImCell 10 )		[ for move ]
		shared ( @CellDuplic )
		sup ( @CellDuplic 0
			:Cell_Base_Chan
		)
		add ( @CellDuplic 1 )
	)
)
>

[ function for duplic cell if it's the one ]

Duplic_Cell<
0 (
	inf ( @CellDuplic 2
		inf ( @cellCreate 160
			sup ( @waitCreate 5
				duplic ( )
				add ( @cellCreate 1 )
				set ( @waitCreate 0 )
			)
			set ( @Impulse 10 )			[ color cell ]
			add ( @waitCreate 1 )
		)
	)
)
>
