<
	?full			0;
	?four			1;
	?pair			2;
	?three		3;
	?yams			4;
	?straigth	5;
>

get_wait<(
	set ( !v #__av__^0^0 )
	cp ( !r^?yams 0 ( !v !v !v !v !v ) )
  cp ( !r^?four 0 ( !v !v !v !v ) )
  cp ( !r^?full 0 ( !y !y !v !v !v ) )
  cp ( !r^?pair 0 ( !v !v ) )
  cp ( !r^?three 0 ( !v !v !v ) )
  cp ( !r^?straigth 0 (
  		sub ( !v 4 ) sub ( !v 3 )
  		sub ( !v 2 ) sub ( !v 1 ) !v
  ) )
	ret ( % ( !r ( #__av__^0 ) ) )
)>

binominal<(
	cp ( !a #__av__^0 )
	cp ( !b #__av__^1 )
	set ( !res call ( #Math|Factorial 0 ( !a ) ) )
	set ( !tmp mult (
			call ( #Math|Factorial 0 ( !b ) )
			call ( #Math|Factorial 0 ( sub ( !a !b ) ) )
	) )
	set ( !res div ( !res !tmp ) )
	set ( !res mult ( !res pow ( div ( 1 6 ) !b ) ) )
	set ( !res mult ( !res pow ( div ( 5 6 ) sub ( !a !b ) ) ) )
	ret ( !res )
)>

get_proba<(
	set ( !res 0 )
	cp ( !lst #__av__^0 )
	set ( !need #__av__^1 )
	set ( !value #__av__^2 )
	cp ( !count call ( :count 0 ( !lst !value ) ) )
	set ( !it sub ( !need !count ) )

	while ( or ( ( inf ( ( !it add ( sub ( 5 !count ) 1 ) ) )
		) ) (
			cp ( !tmp call ( :binominal 0 ( sub ( 5 !count ) !it ) ) )
			set ( !res add ( !res !tmp ) )
			set ( !it add ( !it 1 ) )
	) )
	ret ( !res )
)>

MAIN<(
	:Init_Std
	:Math|Init
	:Init ( cp ( #__av__ 0 ( ?four ( 5 ) 0 ( 0 0 0 5 0 ) ) ) )
	?Init
			cp ( !lst #__av__^1 )
			cp ( !val #__av__^0^0 )
			cp ( !wait call ( :get_wait 0 ( #__av__^0 ) ) )
			set ( !res call ( :get_proba 0 ( % ( !lst ) len ( * ( !wait ) ) !val ) ) 10 )
			echo ( mult ( !res 100 ) 10 )
	?ie__
)>

[
MAIN<(
	:Init_Std
	:Math|Init
	?Init
			set ( !it 0 )
			set ( !len 2000 )
			while ( or ( ( inf ( ( !it !len ) )
				) ) (
					set ( !nb !it )
					egal ( ( call ( #Math|IsPrime 0 ( !nb ) ) 1 ) (
							echo ( !nb " is prime\n" )
					) )
					set ( !it add ( !it 1 ) )
			) )
	?ie__
)>
]