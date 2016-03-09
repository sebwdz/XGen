
target<(
	:Init ((
			set (@target 1)
			set (@inTarget 1)
			cp (@name 2 ("John Doe"))
			cp (@__pos__ 0 (sub (0 mod (rand 100)) sub (0 mod (rand 100))))
			move
	))
)>

attach|exec<(
	sup ((* (#__oth__ /target) 0)(
			inf ((#__vct__^2 10)(ret (1)))
			set (@__pos__^0 add (@__pos__^0 mult (#__vct__^0 15)))
			set (@__pos__^1 add (@__pos__^1 mult (#__vct__^1 15)))
			move
	))
)>

attach|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

arn<(
	:Init ((
			cp (&attach^_exec :attach|exec)
			cp (&attach^_clean :attach|clean)
			cp (&attach^_param 0 (300 0 ?scope (?oth) ?attach ?limit (0)))
	))
	inf ((@inTarget 1)(
			sup ((set (!i add (!i 1)) 50)(
	 				set (&attach^_param^?limit^0 1)
	 				set (!i 0)
	 		))
		)(
			set (@target 0)
			:Init((echo ("I'm attached to " @name "\n")))
	))
)>

main<(
	:Init ((
			cp (@__pos__ 0 (mod (rand 100) mod (rand 100)))
			move
			creat ((:target))
			detach ((:arn ))
	))
)>