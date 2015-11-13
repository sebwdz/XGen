Init($code)<(
	:Init_S ( !init $code )
)>

Init_S($exec $code)<(
        inf ( ( $exec 1 )
		( $code set ( $exec 1 ) )
	)
)>


Cycle($code $wait)<(
	:CycleL ( $code $wait 0 )
)>

CycleL($code $wait $limit)<(
	:Cycle_S ( !count !time $code $wait $limit )
)>

Cycle_S($count $time $code $wait $limit)<(
        or ( (
			inf ( ( $count $limit ) )
			inf ( ( $limit 1 ) )
		) (
                	sup ( ( $time $wait ) ( $code
				add ( $count 1 ) set ( $time 0 ) )
			)
                	add ( $time 1 )
		)
	)
)>

Set_Takein($cond $affct $value)<(
	sup ( $cond
		0 ( set ( $affct 0 ) )
                ( set ( $affct $value ) )
	)
)>
