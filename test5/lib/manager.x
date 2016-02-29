Init_Manager<(
	?c_@__manager__^_orders?. % ( #__Array )?__
	?c_@__manager__^_interactions?. % ( #__Array )?__
)>

Manager|Add<(
	cp ( !int #__av__^0 )
	?_@__manager__^_orders?. /Push ?: ( !int )?__
)>

Manager|Exec<(
	:Init ( :Init_Manager )
	set ( !it 0 )
	while ( or ( (
			inf ( ( !it @__manager__^_interactions^_size ) )
		) ) (
			cp ( !cur @ ( /__manager__ /_interactions /_data !it ) )
			inf ( ( * ( !cur /_param ?limit 0 ) 1 ) (
					?_@__manager__^_interactions?. /Erase ?:( !it )?__
				) (
					[set ( * ( !cur /_param ?limit 0 ) sub ( * ( !cur /_param ?limit 0 ) 1 ) )]
					set ( !it add ( !it 1 ) )
				)
			)
		)
	)
	set ( !it 0 )
	while ( or ( (
			inf ( ( !it @__manager__^_orders^_size ) )
		) ) (
			cp ( !cur @ ( /__manager__ /_orders /_data !it ) )
			?_@__manager__^_interactions?. /Push ?:(!cur)?__
			set ( !it add ( !it 1 ) )
		)
	)
	?_@__manager__^_orders?. /Clear ?: ?__
)>
