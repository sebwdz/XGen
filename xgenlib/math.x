
Math|Init<(
	:Init ( (
			cp ( #Math|Factorial :Math|Factorial )
			cp ( #Math|IsPrime :Math|IsPrime )
			cp ( #Math|Sigmoide :Math|Sigmoide )
	) )
)>

Math|Sigmoide<(
	set ( !tmp pow ( 2.71828 sub ( 0 #__av__^0 ) ) )
	ret ( div ( 1 add ( !tmp 1 ) ) )
)>

Math|Factorial<(
	set ( !tmp #__av__^0 )
	call ( #__push__ 0 ( !val ) )
	set ( !val !tmp )
	sup ( ( !val 1 ) (
			set ( !tmp call ( #Math|Factorial 0 ( sub ( !val 1 ) ) ) )
			set ( !res mult ( !tmp !val ) )
		) ( set ( !res 1 ) )
	)
	set ( !val call ( #__pop__ ) )
	ret ( !res )
)>

Math|IsPrime<(
	set ( !i 2 )
	set ( !stop div ( #__av__^0 2 ) )

	while ( or ( ( inf ( ( !i !stop ) )
		) ) (
			and ( (
					egal ( ( mod ( #__av__^0 !i ) 0 ) )
					no ( ( egal ( ( !i #__av__^0 ) ) ) ) 
				) (
					ret ( set ( !res 0 ) )
			) )
			set ( !i add ( !i 1 ) )
	) )
	ret ( set ( !res 1 ) )
)>