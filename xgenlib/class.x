
Class|Construct<(
	cp ( * ( #this /_gl ) )
	cp ( * ( #this /Init ) :Class|Init )
)>

Class|Init<(
	cp ( * ( #this /_gl ) % ( @ ) )
	cp ( * ( #this /_parent ) @__parent__ )
	set ( * ( * ( @__parent__ /_gl ) /A ) 10 )
	cp ( @__parent__ @__this__ )
)>

Init_Class($av)<(
	sup ( ( @__im__ 1 ) (
			cp ( @__this__ @__im__ )
			cp ( @__im__ 0 )
		) (
			cp ( @__this__ call ( #__new__ ) )
			?c_ * ( @__this__ ) ?. % ( $av ) ) )
	) )
	set ( * ( @__this__ /x ) 10 )
	?_ *  ( @__this__ ) ?. /Init ) )
)>


NewModule($av $code)<(
	:Init ( ( shared ( /__im__ /__parent__ ) ) )
	cp ( @__im__ call ( #__new__ ) )
	set ( @__im__ 1 )
	?c_ * ( @__im__ ) ?. % ( #__Module ) ) )
	cp ( @__parent__ @__this__ )
	$av ( 0 ( $code ) )
)>