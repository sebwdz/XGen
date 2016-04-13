
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
			inf ((incr (!t) 3)(
					cp (@__pos__ 0 (.- (.% (rand 30) 15) .- (.% (rand 30) 15)))
					new_head ((#Nucleus))
				)(
				inf ((incr (!t2) 3)(
						cp (@__pos__ 0 (.- (.% (rand 30) 15) .- (.% (rand 30) 15)))
						egal ((!t2 1)(
								new_head ((#Nucleus :NeuronDopamine))
						)(new_head ((#Nucleus :NeuronPeptide))))
					)(
						cp (@__pos__ 0 (.- (.% (rand 30) 15) .- (.% (rand 30) 15)))
						inf ((incr (!t3) 4)(
								inf ((!t3 2)(
										new_head ((#Nucleus :Output))
								)(new_head ((#Nucleus :Input))))
						))
				))
			))
	))
)>