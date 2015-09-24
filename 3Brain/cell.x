[ 
 All use of fast chans in this file are illegal,
 normaly is only used for talk between differents blocks inside a decriptor

 ( 0 - 9 ) => used for talk between block
 ( 10 - 19 ) => are use for global chan in the decriptor ( more fast than global chan ) it's temporary
]

[
	#0 => init state chan
]

Cell< [ Main node ]
0 (
	:Cell_Init ( #0 )
	inf ( #0 1 set ( #0 1 ) )
	:Duplic_Cell ( ) 
)
>


[
	$0 => init state chan
]

Cell_Init< [ Function for init cell ]
0 (
	inf ( $0 1
		set ( @ImCell 10 )		[ for move ]
		shared ( @CellDuplic )
		sup ( @CellDuplic 0
			:Cell_Base_Chan ( )
		)
		add ( @CellDuplic 1 )
	)
)
>

[ 
	#1 => number of created cell
  	#2 => cycle from last creat
]

Duplic_Cell< [ Function for duplic cell if it's first ]
0 (
	inf ( @CellDuplic 2
		inf ( #1 160
			sup ( #2 5
				duplic ( )
				add ( #1 1 )
				set ( #2 0 )
			)
			set ( @Impulse 10 )			[ chan for color ]
			add ( #2 1 )
		)
	)
)
>
