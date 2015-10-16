Init($exec $code)<
0 (
        inf ( ( $exec 1 )
		0 ( 
			$code
			set ( $exec 1 )
		)
	)
)
>

Cycle($count $time $code $wait $limit)<
0 (
        or (
		0 (
			inf ( ( $count $limit ) )
			inf ( ( $limit 1 ) )
		)
		0 (
                	sup ( ( $time $wait )
				0 (
                       			$code
					add ( $count 1 )
					set ( $time 0 )
				)
                	)
                	add ( $time 1 )
		)
        )
)
>
