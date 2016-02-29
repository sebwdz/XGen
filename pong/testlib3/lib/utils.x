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

Limit($chan $limit)<(
	sup ( ( $chan $limit )
		( set ( $chan $limit ) )
	)
)>

Reduce($chan $rate $min)<(
	set ( !sub $chan )
	set ( !min $min )
       	mult ( !sub $rate )
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

ChangeTo($from $to)<(
	sup ( ( $from 0 ) (
			add ( $to $from )
			set ( $from 0 )
		)
	)
)>

OnlyOne($master $min)<(
	sup ( ( $master 0 ) ( set ( $min 0 ) ) )
)>

Debug($chan $id)<(
	or ( (
			sup ( ( $chan 1 ) )
			sup ( ( !prev 1 ) )
		) (
                        echo ( !prev 32 $id 32 $chan 10 )
                        set ( !prev $chan )
                ) ( set ( !prev 0 ) )
        )
)>
