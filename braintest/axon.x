
[ AXON ]

Axon|ExecSynapses<(
	set (@LastImpulse @Impulse)
	sup ((@Impulse 1)(
			set (!it 0)
			while (inf ((!it @Synapses^_size))(
					cp (!syn @Synapses^_data (!it))
					set (!val * (* (!syn 0) @SynapsesDest))
					set (!val add (mult (div (@Impulse 1) * (!syn 2)) !val))
					set (* (* (!syn 0) @SynapsesDest) !val)
					set (!it add (!it 1))
			))
			set (@Impulse div (@Impulse 10))
	))
)>

LinkWithNucleus<(
	sup ((* (#__oth__ /ImNucleus) 0)(
			set (* (#this /_param ?limit 0) 0)
			cp (@Nucleus % (* (#__oth__)))
			cp (* (#__oth__ /Axon) % (@))
			ret (set (@LinkOk 1))
	))
)>

ToGrowthCone<(
	sup ((@LinkOk 0)(
			:Init ((
					set (!ok 1)
					erase (& /LinkWithNucleus)
					set (@LinkOk 0)
					take_out
					attach ((:GrowthCone))
	))))
	sup ((!ok 0)(:freeAndKill))
)>

Axon<(
	:Init ((
			set (@ImAxon 10)
			cp (&LinkWithNucleus^_exec :LinkWithNucleus)
			cp (&LinkWithNucleus^_param 0 (10 0 ?scope (?oth) ?link ?limit (1)))
			attach ((:ToGrowthCone :Axon|ExecSynapses))
	))
	:freeAndKill
)>
