[
	Rpls other food and snake
]

rplsoth|exec<(
	set (@__pos__^0 sub (@__pos__^0 mult (#__vct__^0 add (1 div (* (#__oth__ /Snake) 3)))))
	set (@__pos__^1 sub (@__pos__^1 mult (#__vct__^1 add (1 div (* (#__oth__ /Snake) 3)))))
)>

[
	stop interaction and move if is necessary
]

rplsoth|clean<(
	sup ((* (#this /_param ?limit 0) 0)(
			move
			set (* (#this /_param ?limit 0) 0)
	))
)>

[
	cell code
]

cell<(
	:Init ((
			inf ((@Head 0)(
					cp (@__pos__ 0 (mod (rand 150) mod (rand 150)))
			))
			set (@Food 20)
			cp (&rplsOth^_exec :rplsoth|exec)
			cp (&rplsOth^_clean :rplsoth|clean)
			cp (&rplsOth^_param 0 (40 0 ?scope (?oth) ?manual ?limit (0)))
	))
	sup ((set (!t add (!t 1)) 50)(
			inf ((@Food 1)(kill ))
			set (&rplsOth^_param^?limit^0 1)
			set (!t 0)
	))
)>

[
	find the nearest food
]

gettarget|exec<(
	and ((
			sup ((* (#__oth__ /Food) 0))
			or ((
					egal ((* (#this /_target 0) 0))
					inf ((#__vct__^2 * (#this /_target 1)))
			))
		)(
			cp (* (#this /_target 0) % (* (#__oth__)))
			cp (* (#this /_target 1) #__vct__^2)
	))
)>

[
	apply target
]

gettarget|clean<(
	sup ((* (#this /_param ?limit 0) 0)(
			cp (* (#this /_param ?limit 0) 0)
			cp (@target * (#this /_target 0))
			cp (* (#this /_target) 0)
	))
)>

[
	repuls other snake
]

rplsSnake|exec<(
	sup ((* (#__oth__ /SnakeHead) 0)(
		set (@__pos__^0 sub (@__pos__^0 mult (#__vct__^0 2)))
		set (@__pos__^1 sub (@__pos__^1 mult (#__vct__^1 2)))
	))
)>

rplsSnake|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

[
	move snake to this target
]

Snake|Move<(
	sup ((set (!move add (!move 1)) 10)(
			set (!move 0)
			sup ((@target 0)(
					cp (!vct call (:get_full_vct 0 (% (* (@target /__pos__)) % (@__pos__))))
					cp (!vct 0 (div (mult (!vct^0 10) !vct^2) div (mult (!vct^1 10) !vct^2)))
					call (:add_vct 0 (% (@__pos__) !vct))
					inf ((!len 10)(
							set (* (@target /Food) sub (* (@target /Food 1)))))
							set (@eat add (@eat 1))
							sup ((@eat 5)(
									:Init((
											set (@eat 0)
											new_head ((:Snake|tail))
									))
							))
							set (#life sub (#life 5))
					))
					move
			))
	))
)>

[
	snake code
]

Snake<(
	:Init ((
			set (@Impulse 10) [ For color ]
			cp (@Head % (@))
			set (@Len 25)
			shared (/Head /Len)
			set (@Snake 5)
			set (@SnakeHead 5)
			cp (&gettarget^_exec :gettarget|exec)
			cp (&gettarget^_clean :gettarget|clean)
			cp (&gettarget^_param 0 (200 0 ?scope (?oth) ?manual ?limit (0)))
			cp (&rplsSnake^_exec :rplsSnake|exec)
			cp (&rplsSnake^_clean :rplsSnake|clean)
			cp (&rplsSnake^_param 0 (50 0 ?scope (?oth) ?manual ?limit (0)))
	))
	sup ((set (!t add (!t 1)) 100)(
			cp (&gettarget^_param^?limit^0 1)
			cp (&rplsSnake^_param^?limit^0 1)
			set (!t 0)
	))
	sup ((set (#life add (#life 1)) 5000)(:Snake|kill))
)>

Snake|kill<(
	set (@Snake 0)
	creat ((:cell))
	set (!kill add (!kill 1))
	sup ((!kill 1)(kill ))
)>

Snake|tail<(
	:Init ((
			set (@Len sub (@Len 1))
			cp (#Head @Head)
			shared (/Head /Len)
			cp (@Head % (@))
			take_out
			set (@Snake 5)
			set (@Impulse 10)	[ For color ]
	))
	inf ((* (#Head /Snake) 1)(:Snake|kill))
	sup ((set (!t add (!t 1)) 5)(
			set (!t 0)
			cp (!vct call (:get_full_vct 0 (% (* (#Head /__pos__)) % (@__pos__))))
			cp (!vct 0 (div (mult (!vct^0 10) !vct^2) div (mult (!vct^1 10) !vct^2) !vct^2))
			sup ((!vct^2 15)(
					call (:add_vct 0 (% (@__pos__) !vct))
					move
			))
			sup ((* (#Head /eat) 15)(
				set (@life 0)
				inf ((set (!split add (!split 1)) 2)(
					sup ((@Len 0)(splitin ))
					set (@eat 0)
				)(set (@eat 16)))
				set (* (#Head /eat) 0)
			))
	))
)>

[
	generate food and snake
]

main<(
	set (@Snake 10)
	?Init set (!eat 1000) ?ie__
	set (!t add (!t 1))
	sup ((!t 50)(set (!t 0) creat ((:cell))))
	sup ((set (!snake add (!snake 1)) 1550)(
			creat ((:Snake :Snake|Move))
			set (!snake 0)
	))
)>
