
[ NEURON NUCLEUS ]

Nucleus|Learn<(
	inf ((@Input 1)(
			no ((egal ((@Learn 0)))(
				set (@Biais .- (@Biais div (@Learn 100)))
				set (@Learn 0)
			))
	))
)>

Input<(
	sup ((@ImNucleus 0)(
			set (@Biais 0.5)
			:Init ((
					share (/Input)
					set (@Input 1)
					call (:Push 0 (% (* (@Parent /Input)) % (@)))
			))
			set (!ok 1)
	))
	sup ((!ok 0)(:freeAndKill))
)>

Output<(
	set (@Output 1)
	:Init ((call (:Push 0 (% (* (@Parent /Output)) % (@)))))
	:freeAndKill
)>

NeuronDopamine<(
	sup ((@ImNucleus 0)(
			set (@Biais 0.5)
			cp (@SynapsesDest /Dopamine)
			:freeAndKill
	))
	:Init ((call (:Push 0 (% (* (@Parent /Dopamine)) % (@)))))
)>

NeuronPeptide<(
	sup ((@ImNucleus 0)(
			set (@Biais 0.5)
			cp (@SynapsesDest /Peptide)
			:freeAndKill
	))
	:Init ((call (:Push 0 (% (* (@Parent /Peptide)) % (@)))))
)>

ImpulseNucleus<(
	sup ((@Active 0)(
			set (* (@Axon /Impulse) add (* (@Axon /Impulse) @Impulse))
			set (@Impulse div (@Impulse 2))
			inf ((@Impulse 0.1)(
					sup ((incr (!time) 0)(
							set (!time 0)
							set (@Active 0)
					))
			))
		)(
			sup ((@Impulse @Biais)(
					sup ((incr (@Accu) 20)(set (@Accu 20)))
					set (#LastActive 0)
					set (@Active 1)
					set (@Impulse 15)
			))
			decr (@Impulse mult (@Impulse 0.9))
	))
	sup ((set (#LastActive add (#LastActive 1)) 10)(
			sup ((@Accu 1)(set (@Accu sub (@Accu mult (@Accu 0.05)))
			)(set (@Accu sub (@Accu 0.1))))
			inf ((@Accu 0)(set (@Accu 0)))
	))
)>

CreatAxon<(
	sup ((@ImInCell 0)(
		set (!in 1)
		:Init ((create ((:Axon))))
	))
	sup ((@Axon 0)(attach ((:ImpulseNucleus)) :freeAndKill))
)>

NucleusNeuron<(
	:Init ((
			share (/SynapsesDest /Output)
			set (@ImNucleus 1)
			attach ((:CreatAxon))
			set (@Biais div (sub (mod (rand 100) 50) 100))
			cp (@CellCode^1 :Neuron)
			cp (@SynapsesDest /Impulse)
			move
	))
	:freeAndKill
)>
