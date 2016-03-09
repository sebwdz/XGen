
formula<(
	ret ( div ( mult (
				sub ( #__av__^0 mult ( #__av__^2 10 ) )
				sub ( #__av__^1 mult ( #__av__^3 10 ) )
			) mult (
				sub ( mult ( #__av__^0 5 ) 150 )
				sub ( mult ( #__av__^1 5 ) 150 )
			)
	) )
)>

get_format<(
	ret ( round ( #__av__^0 3 ) )
)>

get_tab<(
	cp ( !u 0 ( #__av__^0 #__av__^1 ) )
	set ( !x 1 )
	while ( or ( ( inf ( ( !x 6 ) )
		) ) (
			set ( !y 1 )
			set ( !sum 0 )
			while ( inf ( ( !y 6 ) ) (
					set ( !tmp call ( :formula 0 ( !u^0 !u^1 !y !x 10 ) ) )
					set ( !sum add ( !sum !tmp ) )
					set ( #tab ( 5 sub ( !y 1 ) ) add ( #tab ( 5 sub ( !y 1 ) ) !tmp ) )
					cp ( #tab ( sub ( !x 1 ) sub ( !y 1 ) ) !tmp )
					set ( !y add ( !y 1 ) )
			) )
			cp ( #tab ( sub ( !x 1 ) sub ( !y 1 ) ) !sum )
			set ( #tab ( 5 sub ( !y 1 ) ) add ( #tab ( 5 sub ( !y 1 ) ) !sum ) )
			set ( !x add ( !x 1 ) )
	) )
)>

print_list<(
	set ( !it 0 )
	cp ( !tab #__av__^0 )
	set ( !len len ( * ( !tab ) ) )
	while ( inf ( ( !it !len ) ) (
			echo ( call ( :get_format 0 ( * ( !tab !it ) ) ) )
			inf ( ( !it sub ( !len 1 ) ) echo ( "\t" ) )
			set ( !it add ( !it 1 ) )
	) )
)>

FirstPart<(
	echo ( #line "\n" )
	call ( :get_tab 0 ( #av^0 #av^1 ) )
	set ( !it 0 )
	cp ( !len len ( #tab ) )
	echo ( "\tX=10\tX=20\tX=30\tX=40\tX=50\tY law\n" )
	while ( inf ( ( !it !len ) ) (
			inf ( ( !it sub ( !len 1 ) ) (
					echo ( "Y=" mult ( add ( !it 1 ) 10 ) "\t" )
			) ( echo ( "X law\t") ) )
			call ( :print_list 0 ( % ( #tab ( !it ) ) ) )
			echo ( "\n" )
			set ( !it add ( !it 1 ) )
	) )
)>

get_diagonal<(
	set ( !x #__av__^0 )
	set ( !y #__av__^1 )
	set ( !sum 0 )
	while ( and ( ( inf ( ( !x 5 ) )
					sup ( ( !y -1 ) )
		) ) (
			set ( !sum add ( !sum #tab ( !y !x ) ) )
			set ( !y sub ( !y 1 ) )
			set ( !x add ( !x 1 ) )
	) )
	ret ( !sum )
)>

SecondPart<(
	echo ( #line "\n" )
	echo ( "z\t20\t30\t40\t50\t60\t70\t80\t90\t100\ttotal\n" )
	echo ( "p(Z=z)\t" )
	set ( !it 0 )
	cp ( #z 0 )
	set ( !sum 0 )
	while ( inf ( ( !it 9 ) ) (
			inf ( ( !it 5 ) (
				set ( !x 0 )
				set ( !y !it )
			) (
				set ( !x sub ( !it 4 ) )
				set ( !y 4 )
			) )
			set ( #z ( !it ) call ( :get_diagonal 0 ( !x !y ) ) )
			echo ( call ( :get_format 0 ( #z ( !it ) ) ) "\t" )
			set ( !sum add ( !sum #z ( !it ) ) )
			set ( !it add ( !it 1 ) )
	) )
	echo ( !sum )
	echo ( "\n" )
)>

ThirthPart<(
	echo ( #line "\n" )
	echo ( #line "\n" )
)>

MAIN<(
	cp ( #__push__ :__push__ )
	cp ( #__pop__ :__pop__ )

	cp ( #line 2 ( "------------------------------------------" ) )
	cp ( #GetNbr :get_nbr )
	cp ( #only :only )
	cp ( #count :count )
	cp ( #av 0 (
				call ( #GetNbr 0 ( #str_av^0 ) )
				call ( #GetNbr 0 ( #str_av^1 ) )
	) )
	or ( ( 
			egal ( ( call ( #only 0 ( % ( #str_av^0 ) "01234567890." ) ) 0 ) )
			egal ( ( call ( #only 0 ( % ( #str_av^1 ) "01234567890." ) ) 0 ) )
			sup ( ( call ( #count 0 ( % ( #str_av^0 ) "." ) ) 1 ) )
			sup ( ( call ( #count 0 ( % ( #str_av^1 ) "." ) ) 1 ) )
			no ( ( sup ( ( #av^0 50 ) ) ) )
			no ( ( sup ( ( #av^1 50 ) ) ) )
		) (
			ret ( 84 )
	) )
	:FirstPart
	:SecondPart
	:ThirthPart
	ret ( 0 )
)>