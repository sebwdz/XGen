[ Test Factorielle en recursif ]

Init<(
	cp ( @Test :FactRec )
)>

MAIN<(
	inf ( ( #val 1 ) ( :Init ) )
	inf ( ( #val 100 ) (
			add ( #val 1 )
			call ( :Fact ( #val ) )
			echo ( #res 10 )
		)
	)
)>

Fact($val)<(
	set ( #res 1 )
	set ( #it $val )
	call ( @Test )
)>

FactRec<(
	mult ( #res #it )
	sub ( #it 1 )
	sup ( ( #it 0 ) ( call ( @Test ) ) )
)>
