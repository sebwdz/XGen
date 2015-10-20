Init($exec $code)<(
        inf ( ( $exec 1 )
		( $code set ( $exec 1 ) )
	)
)>

Cycle($count $time $code $wait $limit)<(
        or ( (
			inf ( ( $count $limit ) )
			inf ( ( $limit 1 ) )
		)
		(
                	sup ( ( $time $wait ) (
					[:]$code
					add ( $count 1 ) set ( $time 0 )
				)
			)
                	add ( $time 1 )
		)
	)
)>
