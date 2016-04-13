
[ NEURON NUCLEUS ]

Nucleus|Learn<(
	inf ((@Input 1)(
			no ((egal ((@Learn 0)))(
				set (@Biais sub (@Biais div (@Learn 100)))
				[echo ("B = " @Biais " Accu " @Accu "\n")]
				set (@Learn 0)
			))
	)(set (@Biais 0)))
)>

Input<(
	set (@Biais 1)
	:Init ((
			share (/Input)
			set (@Input 1)
			call (:Push 0 (% (* (@Parent /Input)) % (@)))
	))
	:freeAndKill
)>

Output<(
	set (@Output 1)
	:Init ((
			call (:Push 0 (% (* (@Parent /Output)) % (@)))
	))
	:freeAndKill
)>

NeuronDopamine<(
	set (@Biais 1)
	sup ((set (!it add (!it 1)) 5)(
			cp (@SynapsesDest /Dopamine)
			:freeAndKill
	))
	:Init ((call (:Push 0 (% (* (@Parent /Dopamine)) % (@)))))
)>

NeuronPeptide<(
	set (@Biais 1)
	sup ((set (!it add (!it 1)) 5)(
			cp (@SynapsesDest /Peptide)
			:freeAndKill
	))
	:Init ((call (:Push 0 (% (* (@Parent /Peptide)) % (@)))))
)>

IonLeakage<(
	sup ((@Impulse 0)(decr (mult (@Impulse 0.5))))
	inf ((@Impulse 0)(incr (mult (@Impulse 0.5))))
)>

ImpulseNucleus<(
	sup ((@Active 0)(
			set (* (@Axon /Impulse) add (* (@Axon /Impulse) @Impulse))
			set (@Impulse div (@Impulse 2))
			inf ((@Impulse 0.1)(
					sup ((set (!time add (!time 1)) 5)(set (!time 0) set (@Active 0)))
			))
		)(
			sup ((@Impulse @Biais)(
					sup ((incr (@Accu) 20)(set (@Accu 20)))
					set (#LastActive 0)
					set (@Active 1)
					set (@Impulse 15)
			))
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
			attach ((:CreatAxon :IonLeakage))
			set (@Biais div (sub (mod (rand 100) 50) 100))
			sup ((@Input 0)(set (@Biais 1)))
			cp (@CellCode^1 :Neuron)
			cp (@SynapsesDest /Impulse)
			move
	))
	:freeAndKill
)>