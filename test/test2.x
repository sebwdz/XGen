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
	sup ((* (#this /_param ?limit 0) 0)(move
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
	sup ((* (#__oth__ /Snake) 0)(
		set (@__pos__^0 sub (@__pos__^0 mult (#__vct__^0 1.4)))
		set (@__pos__^1 sub (@__pos__^1 mult (#__vct__^1 1.4)))
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
					set (!vct^0 sub (* (@target /__pos__ 0) @__pos__^0))
					set (!vct^1 sub (* (@target /__pos__ 1) @__pos__^1))
					set (!len sqrt(add (mult (!vct^0 !vct^0) mult (!vct^1 !vct^1))))
					cp (!vct 0 (div (mult (!vct^0 10) !len) div (mult (!vct^1 10) !len)))
					cp (@__pos__ 0 (add (@__pos__^0 !vct^0) add (@__pos__^1 !vct^1)))
					inf ((!len 10)(
							set (* (@target /Food) sub (* (@target /Food 1)))))
							set (@eat add (@eat 1))
							sup ((@eat 5)(
									:Init((set (@eat 0)
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
			cp (@Head % (@))
			set (@Len 15)
			shared (/Head /Len)
			set (@Snake 5)
			set (@DopamineAct 100)
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
	sup ((set (#life add (#life 1)) 3000)(:Snake|kill))
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
	))
	:Init ((take_out ))
	set (@Snake 15)
	inf ((* (#Head /Snake) 1)(:Snake|kill))
	sup ((set (!t add (!t 1)) 5)(
			set (!t 0)
			set (!vct^0 sub (* (#Head /__pos__ 0) @__pos__^0))
			set (!vct^1 sub (* (#Head /__pos__ 1) @__pos__^1))
			set (!len sqrt (add (mult (!vct^0 !vct^0) mult (!vct^1 !vct^1))))
			cp (!vct 0 (div (mult (!vct^0 10) !len) div (mult (!vct^1 10) !len)))
			sup ((!len 15)(
					set (@__pos__^0 add (@__pos__^0 !vct^0))
					set (@__pos__^1 add (@__pos__^1 !vct^1))
			))
			move
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
	inf ((set (!it add (!it 1)) 2)(set (!eat 1000)))
	set (!t add (!t 1))
	sup ((!t 30)(set (!t 0) creat ((:cell))))
	sup ((set (!eat add (!eat 1)) 550)(
			creat ((:Snake :Snake|Move))
			set (!eat 0)
	))
)>