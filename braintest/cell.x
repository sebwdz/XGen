
[ CELL ]

Cell<(
	:Init ((
			set (@ImCell 1)
			set (@CellId @Id)
	))
	:freeAndKill
)>

[ MAIN CODE ]

main<(
	inf ((!t3 6)(
			:Init ((
					cp (#Nucleus :Nucleus)
					share (/__pos__ /Parent)
					cp (@Parent % (@))
			))
			inf ((set (!t add (!t 1)) 0)(
					cp (@__pos__ 0 (sub (mod (rand 30) 15) sub (mod (rand 30) 15)))
					new_head ((#Nucleus))
				)(
				inf ((set (!t2 add (!t2 1)) 3)(
						cp (@__pos__ 0 (sub (mod (rand 30) 15) sub (mod (rand 30) 15)))
						egal ((!t2 1)(
								new_head ((#Nucleus :NeuronDopamine))
						)(new_head ((#Nucleus :NeuronPeptide))))
					)(
						cp (@__pos__ 0 (sub (mod (rand 30) 15) sub (mod (rand 30) 15)))
						inf ((set (!t3 add (!t3 1)) 6)(
								inf ((!t3 3)(
										new_head ((#Nucleus :Output))
								)(new_head ((#Nucleus :Input))))
						))
				))
			))
	))
)>