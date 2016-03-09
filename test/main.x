
ModuleTest<(
	?Init
			set ( * ( @obj ) add ( * ( @obj ) 1 ) )
			set ( @Food 10 )
			set ( @DopamineAct 10 )
			set ( @__pos__^0 sub ( mod ( rand 200 ) 100 ) )
			set ( @__pos__^1 sub ( mod ( rand 200 ) 100 ) )
			move
	?ie__
	inf ( ( @Food 1 ) ( set ( * ( @obj ) sub ( * ( @obj ) 1 ) ) kill ) )
	set ( @__pos__^0 add ( @__pos__^0 div ( sub ( mod ( rand 200 ) 100 ) 50 ) ) )
	set ( @__pos__^1 add ( @__pos__^1 div ( sub ( mod ( rand 200 ) 100 ) 50 ) ) )
	move
)>

Snake|Init<(
	:Init_Std
	set ( @Snake 10 )
	?c_ &Atr ?. % ( #__Interaction ) ) )
	cp ( &Atr^_exec :Snake|Atr_Exec )
	cp ( &Atr^_clean :Snake|Atr_Clean )
	cp ( &Atr^_param 0 ( 200 0 ?scope ( ?oth ) ?manual ?limit ( 0 ) ) ) 
	inf ( ( @Split 1 ) set ( #split 1 ) )
	set ( @Split 1 )
	shared ( /Split )
)>

Snake<(
	:Init ( ( :Snake|Init ) )
	sup ( ( set ( !time add ( !time 1 ) ) 10 ) (
			?_ &Atr ?. /Exec ?: ( 1 ) ) )
			set ( !time 0 )
	) )
	sup ( ( set ( @Life add ( @Life 1 ) ) 900 ) ( kill ) )
)>

Snake|Atr_Exec<(
	sup ( ( * ( #__oth__ /Food ) 0 ) (
			inf ( ( #__vct__^2 * ( #this /_target /vct 2 ) ) (
					cp ( * ( #this /_target /vct ) #__vct__ )
					cp ( * ( #this /_target /var ) % ( * ( #__oth__ /Food ) ) )
			) )
 	) )
)>

Snake|Atr_Clean<(
	sup ( ( * ( #this /_param ?limit 0 ) 0 ) (
			inf ( ( * ( #this /_target /vct 2 ) 10 ) (
					cp ( !tmp * ( #this /_target /var ) )
					set ( * ( !tmp ) sub ( * ( !tmp ) 3 ) )
					set ( @Life sub ( @Life 20 ) )
			) )
			set ( @__pos__^0 add ( @__pos__^0 mult ( * ( #this /_target /vct 0 ) 10 ) ) )
			set ( @__pos__^1 add ( @__pos__^1 mult ( * ( #this /_target /vct 1 ) 10 ) ) )
			move
			cp ( * ( #this /_target /vct ) 0 ( 0 0 500 ) )
			cp ( * ( #this /_target /var ) 0 )
			set ( * ( #this /_param ?limit 0 ) 0 )
	) )
)>

MAIN<(
	:Init ( (
			:Init_Std
			cp ( @obj call ( #__new__) )
			shared ( /obj )
	) )
	set ( #split 0 )
	sup ( ( set ( !it add ( !it 1 ) ) 15 ) (
			echo ( * ( @obj ) "\n" )
			creat ( 0 ( :ModuleTest ) )
			set ( !it 0 )
	) )
	sup ( ( !snk 1 ) ( set ( !it2 0 ) ) )
	sup ( ( set ( !it2 add ( !it2 1 ) ) 300 ) (
			creat ( 0 ( :Snake ) )
			set ( !it2 0 )
			set ( !snk add ( !snk 1 ) )
	) )
)>