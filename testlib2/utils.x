Init($code)<(
	:Init_S ( !init $code )
)>

Init_S($exec $code)<(
        inf ( ( $exec 1 ) ( $code set ( $exec 1 ) ) )
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
				add ( $count 1 )
				set ( $time 0 ) )
			)
                	add ( $time 1 )
		)
	)
)>

Set_Takein($cond $affct $value)<(
	sup ( $cond 0 ( set ( $affct 0 ) )
                ( set ( $affct $value ) )
	)
)>

Limit($chan $biais)<(
	sup ( ( $chan $biais )
		( set ( $chan $biais ) )
	)
)>

Reduce($chan $rate $min)<(
	set ( !sub $chan )
	set ( !min 1 )
	div ( !min $min )
       	div ( !sub $rate )
        inf ( ( !sub !min )
              	( sub ( $chan !min ) )
                ( sub ( $chan !sub ) )
        )
)>

TransformTo($from $to $limit)<(
	sup ( ( $from 0 ) (
			add ( $to $from )
			:Limit ( $to $limit )
		)
	)
)>

OnlyOne($master $min)<(
	sup ( ( $master 0 ) ( set ( $min 0 ) ) )
)>
