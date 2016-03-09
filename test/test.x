
[
	Rpls other food and snake
]

rplsoth|exec<(
	set (@__pos__^0 sub (@__pos__^0 mult (#__vct__^0 add (1 * (#__oth__ /Snake)))))
	set (@__pos__^1 sub (@__pos__^1 mult (#__vct__^1 add (1 * (#__oth__ /Snake)))))
)>

[
	stop interaction and move if is necessary
]

rplsoth|clean<(
	sup ((* (#this /_param ?limit 0) 0)(
			set (* (#this /_param ?limit 0) 0)
			move
	))
)>

[
	cell code
]

cell<(
	:Init ((
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
	and ((sup ((* (#__oth__ /Food) 0))
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
			cp (@target 0)
			sup ((* (#this /_target 0) 0)(
					cp (@target * (#this /_target 0))
					cp (* (#this /_target) 0)
			))
	))
)>

[
	repuls other snake
]

rplsSnake|exec<(
	sup ((* (#__oth__ /Snake) 0)(
		set (@__pos__^0 sub (@__pos__^0 mult (#__vct__^0 1.4)))
		set (@__pos__^1 sub (@__pos__^1 mult (#__vct__^1 1.4)))
		))
	))
)>

rplsSnake|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

[
	move snake to this target
]

Snake|Move<(
	sup ((set (!move add (!move 1)) 50)(
			set (!move 0)
			sup ((@target 0)(
					cp (!vct 0 (
							sub (* (@target /__pos__ 0) @__pos__^0)
							sub (* (@target /__pos__ 1) @__pos__^1)
					))
					set (!len add (mult (!vct^0 !vct^0) mult (!vct^1 !vct^1)))
					set (!len div (sqrt(!len)))
					cp (!vct 0 (div (mult (!vct^0 10) !len) div (mult (!vct^1 10) !len)))
					cp (@__pos__ 0 (add (@__pos__^0 !vct^0) add (@__pos__^1 !vct^1)))
					inf ((!len 10)(set (* (@target /Food) sub (* (@target /Food 1)))))
					set (#life sub (#life 10))
					move
			))
	))
)>

[
	snake code
]

Snake<(
	:Init ((
		set (@Snake 5)
		cp (&gettarget^_exec :gettarget|exec)
		cp (&gettarget^_clean :gettarget|clean)
		cp (&gettarget^_param 0 (200 0 ?scope (?oth) ?manual ?limit (0)))
		cp (&rplsSnake^_exec :rplsSnake|exec)
		cp (&rplsSnake^_clean :rplsSnake|clean)
		cp (&rplsSnake^_param 0 (100 0 ?scope (?oth) ?manual ?limit (0)))
	))
	sup ((set (!t add (!t 1)) 100)(
			cp (&gettarget^_param^?limit^0 1)
			cp (&rplsSnake^_param^?limit^0 1)
			set (!t 0)
	))
	:Snake|Move
	set (!cycle add (!cycle 1))
	sup ((set (#life add (#life 1)) 3000)(kill ))
)>

[
	generate food and snake
]

main<(
	set (@Snake 10)
	set (!t add (!t 1))
	sup ((!t 30)(
			creat (0 (:cell))
			set (!it add (!it 1))
			set (!t 0)
	))
	sup ((set (!eat add (!eat 1)) 250)(
			set (!eat 0)
			creat (0 (:Snake))
	))
)>