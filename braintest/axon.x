
[ AXON ]

Axon|ExecSynapses<(
	set (@LastImpulse * (@Nucleus /Accu))
	sup ((@Impulse 1)(
			no ((egal ((@SynapseDest /Impulse)))(set (@LastImpulse 5)))
			set (!it 0)
			while (inf ((!it @Synapses^_size))(
					cp (!syn @Synapses^_data (!it))
					call (:Synapse|clean 0 (!syn))
					call (:Synapse|exec 0 (!syn /Impulse @Impulse))
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
					go_out
					attach ((:GrowthCone :Axon|ExecSynapses))
	))))
	sup ((!ok 0)(:freeAndKill))
)>

Axon<(
	:Init ((
			set (@ImAxon 10)
			cp (&LinkWithNucleus^_exec :LinkWithNucleus)
			cp (&LinkWithNucleus^_param 0 (10 0 ?scope (?oth) ?link ?limit (1)))
			attach ((:ToGrowthCone))
	))
	:freeAndKill
)>
