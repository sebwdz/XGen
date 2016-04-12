[
	t_door : (float * float * float * float)

	t_case :
	{_door : t_door, _visit : float, _state : float, _id : float}

	t_lab :
	{_w : float, _h : float, _data : (t_case * ...)}
]

inv_dir<(
	set (!dir #__av__^0)
	sup ((!dir 1)(decr (!dir 2))(incr (!dir 2)))
	ret (!dir)
)>

get_case<(
	cp (!lst #__av__^0)
	cp (!tmp * (!lst))
	set (!count mod (rand 21))
	while (egal ((1 1))(
			inf ((!count 1)(
				set (!id * (!tmp 0))
				egal ((!tmp * (!lst))(
						cp (* (!lst) * (!tmp 1))
				))
				ret (!id)
			))
			decr (!count 1)
			cp (!tmp * (!tmp 1))
			egal ((!tmp 0)(cp (!tmp * (!lst))))
	))
	ret (0)
)>

aux_check_door<(
	cp (!av #__av__)
	cp (!lst !av^2)
	set (!id call (:get_case 0 (% (!lst))))
	set (!dir !av^1)
	set (!turn 0)
	cp (!arround call (:get_arround 0 (!av^0 !id)))
	cp (!case % (* (!av^0 /_data !id)))
	while (inf ((!turn 4))(
			and ((
					inf ((* (!case /_door !dir) 1))
					sup ((* (!arround !dir) -1))
					inf ((* (!av^0 /_data * (!arround !dir) /_id) 1))
				)(
					[call (:debug 0 (!av^0))]
					set (* (!av^0 /_data * (!arround !dir) /_id) 1)
					set (* (!case /_door !dir) 1)
					set (!inv call (:inv_dir 0 (!dir)))
					set (* (!av^0 /_data * (!arround !dir) /_door !inv) 1)
					inf ((* (!av^0 /_data * (!arround !dir) /_visit) 1)(
							set (* (!av^0 /_data * (!arround !dir) /_visit) 1)
							cp (!lst % ((* (!arround !dir) !lst)))
					))
			))
		incr (!turn)
		sup ((incr (!dir) 3)(set (!dir 0)))
	))
	ret (!lst)
)>

check_door<(
	cp (!av #__av__)
	cp (!lst !av^1)
	while (sup ((!lst 0))(
	[		call (:debug 0 (!av^0))]
			set (!dir mod (round (div (rand 1000) 0) 4))
			cp (!lst call (:aux_check_door 0 (!av^0 !dir !lst)))
	))
)>

generate<(
	cp (!tab % (0))
	set (* (!tab /_h) #__av__^0)
	set (* (!tab /_w) #__av__^1)
	cp (#check_door :check_door)
	set (!caseId mod (rand mult (#__av__^0 #__av__^1)))
	cp (!lst % ((!caseId)))
	set (* (!tab /_data !caseId /_id) 1)
	call (#check_door 0 (!tab !lst))
	ret (!tab)
)>

get_arround<(
	set (!from #__av__^1)
	cp (!tab #__av__^0)
	cp (!arround % (0 (-1 -1 -1 -1)))
	no ((inf ((div (!from * (!tab /_w)) 1)))(
			set (* (!arround 0) sub (!from * (!tab /_w))) 
	))
	no ((egal ((add (mod (!from * (!tab /_w)) 1) * (!tab /_w))))(
			set (* (!arround 1) add (!from 1))
	))
	no ((sup ((add (div (!from * (!tab /_w)) 1) * (!tab /_h))))(
			set (* (!arround 2) add (!from * (!tab /_w)))
	))
	no ((inf ((mod (!from * (!tab /_w)) 1)))(
			set (* (!arround 3) sub (!from 1))
	))
	ret (!arround)
)>

show_case<(
	cp (!arround #__av__^2)
	egal ((mod (#__av__^1 2) 0)(
			inf ((* (#__av__^0 /_door #__av__^1) 1)(echo ("--"))(echo ("  ")))
			or ((
					sup ((* (!arround #__av__^1) 0))
					inf ((* (!arround 1) 0))
				)(
					echo ("+")
				)(
					echo ("-")
			))
		)(
			inf ((* (#__av__^0 /_door #__av__^1) 1)(echo ("|"))(echo (" ")))
			egal ((* (#__av__^0 /_state) 3)(echo ("ST")))
			egal ((* (#__av__^0 /_state) 4)(echo ("ED")))
			egal ((* (#__av__^0 /_state) 1)(echo ("..")))
			egal ((* (#__av__^0 /_state) 0)(echo ("  ")))
			inf ((* (!arround 1) 0)(echo ("|")))
	))
)>

print_line<(
	cp (!av #__av__)
	set (!it !av^1)
	set (!to add (!av^1 * (!av^0 /_w)))
	while (inf ((!it !to))(
		cp (!arround call (:get_arround 0 (!av^0 !it)))
		egal ((mod (!av^2 2) 0)(
				egal ((!it !av^1)(echo ("+")))
		))
		call (:show_case 0 (% (* (!av^0 /_data !it)) !av^2 !arround))
		incr (!it)
	))
	echo ("\n")
)>

show<(
	cp (!av #__av__)
	set (!case 0)
	set (!it 0)
	while (inf ((!it * (!av^0 /_h)))(
			call (:print_line 0 (!av^0 !case 0))
			call (:print_line 0 (!av^0 !case 3))
			incr (!case * (!av^0 /_w))
			egal ((add (!it 1) * (!av^0 /_h))(
				call (:print_line 0 (!av^0 !case 2))
			))
			incr (!it)
	))
)>

debug<(
	cp (!av #__av__)
	set (!it 0)
	while (inf ((!it 30000))(
		incr (!it)
	))
	call (:show 0 (!av^0))
)>

find<(
	cp (!tmp #__av__)
	[call (:debug 0 (!tmp^0))]
	call (:__push__ 0 (!id))
	call (:__push__ 0 (!it))
	call (:__push__ 0 (!arround))
	call (:__push__ 0 (!av))
	cp (!av !tmp)
	set (!id !av^1)
	egal ((* (!av^0 /_data !av^1 /_state) 4)(
			ret (1)
	))
	egal ((* (!av^0 /_data !av^1 /_state) 0)(
			set (* (!av^0 /_data !av^1 /_state) 1)
	))
	cp (!arround call (:get_arround 0 (!av^0 !av^1)))
	set (!it 0)
	while (inf ((!it 4))(
			egal ((* (!av^0 /_data !av^1 /_door !it) 1)(
					and ((
							sup ((* (!arround !it) -1))
							no ((egal ((* (!av^0 /_data * (!arround !it) /_state) 1))))
							no ((egal ((* (!av^0 /_data * (!arround !it) /_state) 3))))
						)(
							cp (!res call (#find 0 (!av^0 * (!arround !it))))
							sup ((!res 0)(ret (1)))
					))
			))
			incr (!it)
	))
	egal ((* (!av^0 /_data !av^1 /_state) 1)(
			set (* (!av^0 /_data !av^1 /_state) 0)
	))
	cp (!av call (:__pop__))
	cp (!arround call (:__pop__))
	cp (!it call (:__pop__))
	cp (!id call (:__pop__))
	ret (0)
)>

solve<(
	cp (!lab #__av__^0)
	set (!start mult (mod (rand * (!lab /_h)) * (!lab /_w)))
	set (!end mult (mod (rand * (!lab /_h)) * (!lab /_w)))
	incr (!end sub (* (!lab /_w) 1))
	set (* (!lab /_data !start /_state) 3)
	set (* (!lab /_data !end /_state) 4)
	cp (#find :find)
	call (#find 0 (!lab !start))
)>

main<(
	cp (!lab call (:generate 0 (30 40)))
	call (:solve 0 (!lab))
	call (:show 0 (!lab))
)>
