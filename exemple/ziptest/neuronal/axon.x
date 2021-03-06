
Axon|Transmit<(
	set (@WorkImpulse 0)
	sup ((@Impulse 0.05)(
			incr (@WorkImpulse div (@Impulse 5))
			decr (@Impulse div (@Impulse 5))
	)(set (@Impulse 0)))
)>

Axon|ManagerSynapses<(
	cp (* (@PoolZone) 0)
	:Synapse|emettor (/Impulse sup ((@WorkImpulse 0)(@WorkImpulse)))
)>

[
	Link Nucleus
]

Axon|linkNucleus|exec<(
	sup ((* (#__oth__ /NeuronNucleus) 0)(
			set (* (#this /_param ?limit 0) 0)
			cp (* (#__oth__ /Axon) % (@))
			ret (1)
	))
)>

[
	Link With Nucleus and go out cell
]

Axon|linkNucleus<(
	:Utils|init ((
			cp (&linkNucleus^_exec :Axon|linkNucleus|exec)
			cp (&linkNucleus^_param 0 (10 0 ?scope (?oth) ?link ?limit (1)))
	))
	sup ((@Nucleus 0)(
			?Init
					go_out
					erase (& /linkNucleus)
					set (!kill 1)
			?ie__
	))
	sup ((!kill 0)(:Utils|freeAndKill))
)>

[
	exprime Grow cone code
]

Axon|exprGrowCone<(
	sup ((@Nucleus 0)(
		?Init
			attach ((:GrowCone))
			set (!kill 1)
		?ie__
	))
	sup ((!kill 0)(:Utils|freeAndKill))
)>

[
	Axon code
]

Axon<(
	:Utils|init ((
			set (@Axon 1)
			set (@Input 0)
			attach ((:Axon|linkNucleus :Axon|exprGrowCone))
			attach ((:Axon|Transmit :Axon|ManagerSynapses))
			cp (@PoolZone % (0))
	))
	:Utils|freeAndKill
)>