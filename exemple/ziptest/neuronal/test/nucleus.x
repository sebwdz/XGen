
[
	After create Cell (Membrane)
	Nuclues come in
]

Nucleus|cominCell|exec<(
	sup ((* (#__oth__ /FreeCell) 0)(
		cp (@CellPtr % (* (#__oth__)))
		set (* (#__oth__ /FreeCell) 0)
		ret (1)
	))
)>

[
	expr cominCell
]

Nucleus|cominCell<(
	:Utils|init ((
			cp (&cominCell^_exec :Nucleus|cominCell|exec)
			cp (&cominCell^_param 0 (10 0 ?scope (?oth) ?comin ?limit (1)))
	))
	sup ((@CellPtr 0)(
			?Init
					erase (& /cominCell)
					cp (* (@CellPtr /NucleusPtr) % (@))
					:Nucleus|exprInitial
					set (!kill 1)
			?ie__
	))
	sup ((!kill 0)(:Utils|freeAndKill))
)>


[
	if is the first nucleus, create others
]

Nucleus|initial<(
	?Init
			set (@son 1)
			share (/son)
			set (!limit @Duplic^limit)
	?ie__
	inf ((incr (!count) !limit)(
			duplic
	)(:Utils|freeAndKill))
)>

[
	expr initial gen
]

Nucleus|exprInitial<(
	:Utils|init ((
			inf ((@son 1)(
					attach ((:Nucleus|initial))
					set (@Initial 1)
			))
	))
)>

[
	expr cell type
]

Nucleus|exprType<(
	sup ((@CellPtr 0)(
			:Utils|init ((
					[ Neuron type ]
					detach ((:Utils|attach ((:Neuron) /Cell ?parent)))
					attach ((:NeuronNucleus))
					set (!kill 1)
			))
	))
	sup ((!kill 0)(:Utils|freeAndKill))
)>

[
	Nucleus, main programme
]

Nucleus<(
	:Utils|init ((
			set (@__pid__ rand)
			share (/__pid__)
			set (@Duplic^limit 22)
			create ((:Cell))
			attach ((:Nucleus|cominCell))
			attach ((:Nucleus|exprType))
	))
)>