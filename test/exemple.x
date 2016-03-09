
[
		Piscine c++ d01
		()								-> (float)
]

Follow_the_white_rabbit<(
	set (!rabbit 0)
	set (!ret 0)
	while (egal ((!rabbit 0))(
			set (!dice add (mod (rand 37) 1))
			set (!ret add (!ret !dice))
			or ((and ((sup ((!dice 3)) inf ((!dice 7))))
					egal ((!dice 28))
					and ((sup ((!dice 16)) inf ((!dice 22))))
				)(echo ("gauche\n")))
			or ((egal ((!dice 15)) egal ((!dice 23)) egal ((!dice 10))
				)(echo ("devant\n")))
			or ((egal ((!dice 26)) egal ((mod (!dice 8) 0)))
				(echo ("derriere\n")))
			or ((egal ((!dice 13)) sup ((!dice 33)) inf ((!dice 37)))
				(echo ("droite\n")))
			or ((egal ((!dice 1)) egal ((!dice 37)) sup ((!ret 397)))
				(set (!rabbit 1)))
	))
	echo ("LAPIN!!!\n")
	ret (!ret)
)>

[
	sort float tab
	(%(float))	-> ()
]

sortf<(
	set (!move 1)
	set (!len len (* (#__av__^0)))
	while (egal ((!move 1))(
		set (!it 1)
		set (!move 0)
		while (inf ((!it !len))(
			inf ((* (#__av__^0 !it) * (#__av__^0 sub (!it 1)))(
					set (!move 1)
					set (!tmp * (#__av__^0 !it))
					set (* (#__av__^0 !it ) * (#__av__^0 sub (!it 1)))
					set (* (#__av__^0 sub (!it 1)) !tmp)
			))
			set (!it add (!it 1))
		))
	))
)>

[
	compare two numbers
	(float float)		-> (float)
]

cmp<(
	inf ((#__av__^0 #__av__^1)(ret (1)))
)>

sort_listf<(
	cp (!lst #__av__^0)
	set (!move 1)
	while (egal ((!move 1))(
			set (!move 0)
			cp (!prev 0)
			cp (!it !lst)
			while (sup ((!it 0))(
					sup ((!prev 0)(
							inf ((* (!it 0) * (!prev 0))(
									cp (!tmp * (!it 0))
									cp (* (!it 0) * (!prev 0))
									cp (* (!prev 0) !tmp)
									set (!move 1)
							))
					))
					cp (!prev !it)
					cp (!it * (!it 1))
			))
	))
)>

[
	sort any tab by function
	(%(?) (%function(? ?)) -> float))	-> ()
]

show_int<(
	echo (* (#__av__^0) " ")
)>

main<(
	:List|Init
	cp (!cmp :cmp)
	cp (!ish :show_int)
	cp (!ish^0^1 2 ("_AA_"))
	echo ("Test list\n")

	cp (!rec 0)
	cp (!rec call (#List|PushFront 0 (!rec 50)))
	cp (!rec call (#List|PushFront 0 (!rec 10)))
	cp (!rec call (#List|PushFront 0 (!rec 20)))
	cp (!rec call (#List|PushBack 0 (!rec 15)))
	cp (!rec call (#List|PushBack 0 (!rec 35)))
	cp (!rec call (#List|Insert 0 (!rec !rec 22)))
	
	call (#List|ForEach 0 (!rec % (!ish)))
	echo ("\n")

	cp (!rec call (#List|Erase 0 (!rec * (!rec 1))))
	cp (!rec call (#List|PopBack 0 (!rec)))
	cp (!rec call (#List|PopFront 0 (!rec)))

	cp (!ish^0^1 "_")
	call (#List|ForEach 0 (!rec % (!ish)))
	echo ("\n")

	cp (!rec call (#List|PushFront 0 (!rec 50)))
	cp (!rec call (#List|PushFront 0 (!rec 10)))
	cp (!rec call (#List|PushFront 0 (!rec 20)))
	cp (!rec call (#List|PushBack 0 (!rec 15)))
	cp (!rec call (#List|PushBack 0 (!rec 35)))
	cp (!rec call (#List|Insert 0 (!rec !rec 22)))

	call ( :sort_listf 0 (!rec % (!cmp)))

	cp (!len call (:List|GetLen 0 (!rec)))
	echo ("len = " !len "\n")

	cp (!ish^0^1 " ")
	call (#List|ForEach 0 (!rec % (!ish)))
	echo ("\n")
	echo ("\n")
	echo ("\n")

	echo ("Follow_the_white_rabbit\n")

	set (!x call (:Follow_the_white_rabbit))
	echo ("res =>" !x "\n")

	echo ("\n")
	echo ("Sort test\n")

	cp (!arr 0 (24 5 13 9 0 2 17 2 5 3 2 1 6 7 -7 -13 0 5 5 2))
	call (:sortf 0 (% (!arr) % (!cmp)))
	set (!it 0)
	set (!len len (!arr))
	while (inf ((!it !len))(
			echo (!arr (!it) " ")
			set (!it add (!it 1))
	))
	echo ("\n")
	ret (0)
)>

