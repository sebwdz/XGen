
[ NUCLEUS ]

CominCell|exec<(
	egal ((* (#__oth__ /CellId) @Id)(
			set (* (#__oth__ /IsCell) 2)
			set (* (#this /_param ?limit 0) 0)
			set (@ImInCell 1)
			cp (@Cell % (* (#__oth__)))
			cp (* (#__oth__ /Nucleus) % (@))
			ret (1)
	))
)>

InitNucleus<(
	:Init ((
			share (/Id)
			set (@Id rand)
			cp (@CellCode^0 :Cell)
			set (@ImNucleus 1)
			cp (&CominCell^_exec :CominCell|exec)
			cp (&CominCell^_param 0 (10 0 ?scope (?oth) ?comin ?limit (1)))
			go_out
	))
	:freeAndKill
)>

CreatCell<(
	sup ((incr (!t) 3)(:Init ((create (@CellCode)))))
	sup ((@ImInCell 0)(
			set (!ok 1)
			:Init ((erase (& /CominCell)))
	))
	sup ((!ok 0)(:freeAndKill))
)>

Nucleus<(
	:Init ((attach ((:NucleusNeuron :InitNucleus :CreatCell :Nucleus|Learn))))
	:freeAndKill
)>