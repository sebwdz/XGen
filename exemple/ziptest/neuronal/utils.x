
<
	[
		define for init (inline form)
	]
	?Init 		inf ((!__init__ 1)(;
	?ie__			set (!__init__ 1)));
>

[
	init function
]

Utils|init($code)<(
	inf ((!it 1)($code set (!it 1)))
)>

[
	free and kill the descriptor
]

Utils|freeAndKill<(
	inf ((incr (!it) 2)(free)(kill))
)>

[
	get target for attach descriptor
]

Utils|attach|exec($to)<(
	sup ((* (#__oth__ $to) 0)(
			set (* (#this /_param ?limit 0) 0)
			ret (1)
	))
)>

[
	attach a descriptor to target
]

Utils|attach($code $to $target)<(
	:Utils|init ((
			cp (&Attach^_exec :Utils|attach|exec ($to))
			cp (&Attach^_param 0 (10 0 ?scope ($target) ?attach ?limit (1)))
	))
	sup ((@ ($to) 0)(
			?Init
					attach ($code)
					set (!kill 1)
					erase (& /Attach)
			?ie__
	))
	sup ((!kill 0)(:Utils|freeAndKill))
)>

[
	stop interaction after each cycle
]

Utils|stopInteraction($int $time)<(
	sup ((incr (!time) $time)(
			?Init erase (& $int) ?ie__
			:Utils|freeAndKill
	))
)>

Utils|linkWith($name $scope $block $end $code)<(
	:Utils|actWith ($name ?link $scope $block $end $code)
)>

Utils|actWith($name $type $scope $block $end $code)<(
	:Utils|init ((
			cp (& ($name /_exec) $block)
			cp (& ($name /_param) 0 (10 0 ?scope ($scope) $type ?limit (1)))
	))
	sup ((!kill 0)(:Utils|freeAndKill))
	sup (($end 0)(
			?Init
					$code
					erase (& /name)
					set (!kill 1)
			?ie__
	))
)>

Utils|findNear|exec($find)<(
	sup ((* (#__oth__ $find) 0)(
			and ((
					no ((egal ((@__pid__ * (#__oth__ /__pid__)))))
					or ((
							inf ((#__vct__^2 * (#this /_near 2)))
							inf ((* (#this /_near 2) 1))
					))
				)(
					set (* (#this /_found) 1)
					cp (* (#this /_near) #__vct__)
			))
	))
)>

slab (/name 0)		[ add label to this node ]
slab (/name)			[ remove label ]
glab (:node /name)	[ get labev ptr => 0 (ptr1 ptr2) ]

[ same thing ]
[slab (/name @val^0^1)
slab (/name glab (@myblock /name))
set (slab (/name !x) 0)
]