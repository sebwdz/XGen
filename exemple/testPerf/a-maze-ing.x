
[
                # Push node in __stack__
                ( $ -> node ) -> (void)
]

__push__<(
        set ( #__stack_it__ add ( set ( !it #__stack_it__ ) 1 ) )
        cp ( #__stack__ ( !it ) #__av__^0 )
)>

[
                # Pop node and get
                ( $ -> node ) -> (void)
]

__pop__<(
        set ( #__stack_it__ set ( !it sub ( #__stack_it__ 1 ) ) )
        ret ( #__stack__ ( !it ) )
)>


inv_dir<(
	sup ((set (!dir #__av__^0) 1)(decr (!dir 2))(incr (!dir 2)))
)>

get_case<(
	cp (!lst #__av__^0)
	cp (!tmp * (!lst))
	set (!count mod (rand 1))
	while (egal ((1 1))(
			inf ((decr (!count) 0)(
					egal ((!tmp * (!lst))(cp (* (!lst) * (!tmp 1))))
					ret (set (!id * (!tmp 0)))
			))
			cp (!tmp * (!tmp 1))
			egal ((!tmp 0)(cp (!tmp * (!lst))))
	))
)>

aux_check_door<(
	cp (! 0 ({tab #__av__^0}{lst #__av__^2}{dir #__av__^1}{turn 0}))
	set (!id call (:get_case 0 (% (!lst))))
	cp (!arround call (:get_arround 0 (!tab !id)))
	cp (!case % (* (!tab /_data !id)))
	while (inf ((!turn 4))(
			and ((
					inf ((* (!case /_door !dir) 1))
					sup ((* (!arround !dir) -1))
					inf ((* (!tab /_data * (!arround !dir) /_id) 1))
				)(
					set (* (!tab /_data * (!arround !dir) /_id) 1)
					set (* (!case /_door !dir) 1)
					set (!inv call (:inv_dir 0 (!dir)))
					set (* (!tab /_data * (!arround !dir) /_door !inv) 1)
					inf ((* (!tab /_data * (!arround !dir) /_visit) 1)(
							set (* (!tab /_data * (!arround !dir) /_visit) 1)
							cp (!lst % ((* (!arround !dir) !lst)))
					))
			))
		incr (!turn)
		sup ((incr (!dir) 3)(set (!dir 0)))
	))
	!lst
)>

check_door<(
	cp (! 0 ({lst #__av__^1}{lab #__av__^0}))
	while (sup ((!lst 0))(
			set (!dir mod (round (div (rand 1000) 0) 4))
			cp (!lst call (:aux_check_door 0 (!lab !dir !lst)))
	))
)>

generate<(
	cp (!tab % (0 ({_h #__av__^0}{_w #__av__^1})))
	set (!caseId mod (rand mult (#__av__^0 #__av__^1)))
	cp (!lst % ((!caseId)))
	cp (#check_door :check_door)
	set (* (!tab /_data !caseId /_id) 1)
	call (#check_door 0 (!tab !lst))
	!tab
)>

get_arround<(
	cp (! 0 ({from #__av__^1}{tab #__av__^0}))
	set (!tmp add (div (!from * (!tab /_w)) 1))
	% ((
			inf ((div (!from * (!tab /_w)) 1)(val (-1))(sub (!from * (!tab /_w))))
			egal ((add (mod (!from * (!tab /_w)) 1) * (!tab /_w))(val (-1))(add (!from 1)))
			sup ((!tmp * (!tab /_h))(val (-1))(add (!from * (!tab /_w))))
			inf ((mod (!from * (!tab /_w)) 1)(val (-1))(sub (!from 1)))
	))
)>

show_case<(
	cp (!arround #__av__^2)
	egal ((mod (#__av__^1 2) 0)(
			inf ((* (#__av__^0 /_door #__av__^1) 1)(echo ("--"))(echo ("  ")))
			echo (or ((sup ((* (!arround #__av__^1) 0)) inf ((* (!arround 1) 0)))
				(val (2 ("+")))(val (2 ("-")))
			))
		)(
			inf ((* (#__av__^0 /_door #__av__^1) 1)(echo ("|"))(echo (" ")))
			cp (!word 0 (2 ("  ") 2 ("..") 2 (0) 2 ("ST") 2 ("ED")))
			echo (!word (* (#__av__^0 /_state)))
			inf ((* (!arround 1) 0)(echo ("|")))
	))
)>

print_line<(
	cp (!av #__av__)
	set (!it !av^1)
	set (!to add (!av^1 * (!av^0 /_w)))
	while (inf ((!it !to))(
		cp (!arround call (:get_arround 0 (!av^0 !it)))
		egal ((mod (!av^2 2) 0)(egal ((!it !av^1)(echo ("+")))))
		call (:show_case 0 (% (* (!av^0 /_data !it)) !av^2 !arround))
		incr (!it)
	))
	echo ("\n")
)>

show<(
	cp (! 0 ({lab #__av__^0}{case 0}{it 0}))
	while (inf ((!it * (!lab /_h)))(
			call (:print_line 0 (!lab !case 0))
			call (:print_line 0 (!lab !case 3))
			incr (!case * (!lab /_w))
			egal ((add (!it 1) * (!lab /_h))(call (:print_line 0 (!lab !case 2))))
			incr (!it)
	))
)>

debug<(
	cp (!lab #__av__^0)
	set (!it 0)
	while (inf ((!it 30000))(incr (!it)))
	call (:show 0 (!lab))
)>

find<(
	cp (!tmp #__av__)
	call (:__push__ 0 (!))
	cp (! 0 ({lab !tmp^0}{id !tmp^1}{it 0}))
	erase (! /tmp)
	egal ((* (!lab /_data !id /_state) 4)(ret (1)))
	egal ((* (!lab /_data !id /_state) 0)(set (* (!lab /_data !id /_state) 1)))
	cp (!arround call (:get_arround 0 (!lab !id)))
	while (inf ((!it 4))(
			and ((
					egal ((* (!lab /_data !id /_door !it) 1))
					and ((
							sup ((* (!arround !it) -1))
							no ((egal ((* (!lab /_data * (!arround !it) /_state) 1))))
							no ((egal ((* (!lab /_data * (!arround !it) /_state) 3))))
						))
				)(
					sup ((call (#find 0 (!lab * (!arround !it))) 0)(ret (1)))
			))
			incr (!it)
	))
	egal ((* (!lab /_data !id /_state) 1)(set (* (!lab /_data !id /_state) 0)))
	cp (! call (:__pop__))
	val (0)
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
	echo ("show lab\n")
	call (:show 0 (!lab))
)>

[
	t_door : (float * float * float * float)

	t_case :
	{_door : t_door, _visit : float, _state : float, _id : float}

	t_lab :
	{_w : float, _h : float, _data : (t_case * ...)}
]
