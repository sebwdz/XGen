

[
	repluse by other cells
]

Cell|rplsOther|exec($target $pow)<(
	sup ((* (#__oth__ $target) 0)(
			decr (@__pos__^0 div (#__vct__^0 $pow))
			decr (@__pos__^1 div (#__vct__^1 $pow))
	))
)>

[
	move cell or wait for next time
]

Cell|rplsOther|clean<(
	inf ((* (#this /_param ?limit 0) 1)(
			sup ((incr (!time) 2)(
					set (!time 0)
					set (* (#this /_param ?limit 0) 1)
			))
	)(move decr (* (#this /_param ?limit 0))))
)>

[
	Gen for repulse by others cells
]

Cell|rplsOther<(
	:Utils|init ((
			cp (&rplsOther^_exec :Cell|rplsOther|exec(/Cell 1))
			cp (&rplsOther^_clean :Cell|rplsOther|clean)
			cp (&rplsOther^_param 0 (10 0 ?scope (?oth) ?manual ?limit (1)))
	))
)>

[
	waiting for nucleus comin
]

Cell|waitNucleus<(
	inf ((@FreeCell 1)(
			?Init
					inf ((* (@NucleusPtr /Initial) 1)(go_out))
					attach ((:Cell|rplsOther))
					set (!kill 1)
			?ie__
	))
	sup ((!kill 0)(:Utils|freeAndKill))
)>

[
	Cell's dna
]

Cell<(
	:Utils|init ((
			set (@Cell 1)
			set (@FreeCell 1)
			attach ((:Cell|waitNucleus))
	))
	:Utils|freeAndKill
)>