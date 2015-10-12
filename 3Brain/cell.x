
[
 #0 => init state chan
]

Move_Cell<
0 (
	inf ( #init 1
		set ( #init 1 )
		set ( #dst 70 )
		:Cell_Base_Chan ( &rpls )
		set ( @Impulse 10 )
		set ( #life 20 )
		set ( @ImCell 10 )
	)
	sup ( #up 15
		sup ( #dst 20
			var ( &rpls ( dst ( #dst ) ) )
			sub ( #dst 5 )
			sub ( @Impulse 1 )
			set ( #up 0 )
			add ( #life 15 )
		)
	)
	add ( #up 1 )
	sub ( #life 1 )
	inf ( #life 1 kill )
)
>

Cell< [ Main node ]
0 (
	inf ( #init 1 set ( #init 1 ) :Cell_Init ( ) set ( #needCreate 13 ) )
	inf ( @S_CellDuplic 2 :Duplic_Cell ( ) set ( @ImMaster 10 ) )
)
>

[
 $0 => init state chan
]

Cell_Init< [ Function for init cell ]
0 (
	set ( @ImCell 20 )			[ for move ]
	shared ( @S_CellDuplic )
	inf ( @S_CellDuplic 1
		var ( 
			&rpls (
				dst ( 120 )
				pw ( 30 )
				type ( mv to rpls )
				act ( @ImMaster @ImMaster )
			)
		)
	)
)
>

[ 
 #1 => number of created cell
 #2 => cycle from last creat
]

Duplic_Cell< [ Function for duplic cell if it's first ]
0 (
	sup ( #time 2
		creat ( :Move_Cell )
		add ( #nbCreate 1 )
		set ( #time 0 )
	)
	sup ( #nbCreate #needCreate
		duplic ( )
		set ( #needCreate #nbCreate )
		add ( #needCreate 23 )
	)
	set ( @ImpulseStk 10 )			[ chan for color ]
	add ( #time 1 )
	sup ( #nbCreate 34 kill )
)
>
