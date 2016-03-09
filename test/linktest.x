
ShowList<(
	cp ( !lst #__av__^0 )
	cp ( !tmp * ( !lst /_begin ) )
	while ( no ( ( egal ( ( !tmp 0 ) )
		) ) (
			cp ( !val * ( !tmp 0 ) )
		 	echo ( !val "\n" )
		 	cp ( !tmp * ( !tmp 1 ) )
	) )
)>

show_int<(
	cp ( !lst #__av__^0 ) 
	echo ( "->" * ( !lst ) "\n" )
)>

MAIN<(
	?Init
			:Init_Std
			:Chain|Init
			cp ( !lst 0 ( 2 ( "C1" ) 0 ( 2 ( "C2" ) 0 ( 2 ( "C3" ) 0 ( 2 ( "C4" ) 0 ( 0 ) ) ) ) ) )
	?ie__
			cp ( !len call ( #Chain|Length 0 ( % ( !lst ) ) ) )
			echo ( !len "\n" )
	[
	:Init_Std
	:Init ( (
		cp ( #__LinkList :LinkList|Construct )
		cp ( #ShowList :ShowList )
		cp ( #ShowInt :show_int )
	) )

	?Init
			cp ( !item % ( !lst ) )
			while ( or ( ( sup ( ( len ( * ( !item 1 ) ) 0 ) )
				) ) (
					echo ( * ( !item 0 ) )
					sup ( ( len ( * ( !item 1 ) ) 1 ) ( echo ( " -> " ) ) )
					cp ( !item % ( * ( !item 1 ) ) )
			) )
			echo ( "\n" )

			cp ( !lst call ( #__new__ ) )
			?c_ * ( !lst ) ?. % ( #__LinkList ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 10 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 11 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 12 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 13 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 10 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 11 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 12 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 13 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 10 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 11 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 12 ) ) )
			?_ * ( !lst ) ?. /Push_Front ?: ( 13 ) ) )

			call ( #ShowList 0 ( !lst ) )
			echo ( "____\n" )
			
			call ( #ShowList 0 ( !lst ) )
			?_ * ( !lst ) ?. /ForEach ?: ( % ( #ShowInt ) ) ) )
			echo ( "____\n" )
			?_ * ( !lst ) ?. /Pop_Back ) )
			echo ( "\n" )

			call ( #ShowList 0 ( !lst ) )
			echo ( "\n" )

			?_ * ( !lst ) ?. /Push_Back ?: ( 1 ) ) )
			call ( #ShowList 0 ( !lst ) )
			echo ( "\n" )

			cp ( !next * ( * ( !lst /_begin ) 1 ) )
			?_ * ( !lst ) ?. /Insert ?: ( !next 1 ( "OOO" ) ) ) )
			call ( #ShowList 0 ( !lst ) )
			echo ( "\n" )

			cp ( !next * ( * ( !lst /_begin ) 1 ) )
			?_ * ( !lst ) ?. /Erase ?: ( !next ) ) )
			call ( #ShowList 0 ( !lst ) )
			echo ( "\n" )

			cp ( !next * ( * ( !lst /_begin ) 1 ) )
			?_ * ( !lst ) ?. /Insert ?: ( !next 1 ( "RRR" ) ) ) )
			call ( #ShowList 0 ( !lst ) )
			echo ( "\n" )

			?_ * ( !lst ) ?. /Pop_Back ) )
			?_ * ( !lst ) ?. /Pop_Back ) )
	?ie__
	]
)>