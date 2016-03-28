
[ NEURON ]

Neuron|RplsOth|exec<(
	sup ((* (#__oth__ /ImNeuron) 0)(
			set (@__pos__^0 sub (@__pos__^0 #__vct__^0))
			set (@__pos__^1 sub (@__pos__^1 #__vct__^1))
	))
)>

Neuron|RplsOth|clean<(
	move
)>

SetUp<(
	:Init ((
			cp (&RplsOthNeuron^_exec :Neuron|RplsOth|exec)
			cp (&RplsOthNeuron^_clean :Neuron|RplsOth|clean)
			cp (&RplsOthNeuron^_param 0 (25 0 ?scope (?oth) ?manual ?limit (1)))
	))
	sup ((set (!t add (!t 1)) 50)(
		erase (& /RplsOthNeuron)
		:freeAndKill
	))
)>

get_learn_dir<(
	set (!learn #__av__^0)
	echo ("Frequence = " * (@Nucleus /Accu) "\n")
	sup ((* (@Nucleus /Accu) 3)(
			sup ((!learn 0)(set (!dir 0.5))
				(set (!dir -1)))
		)(
			sup ((!learn 0)(set (!dir -0.5))
				(set (!dir 1)))
	))
	ret (!dir)
)>

MembraneLearn<(
	inf ((@Input 1)(
	set (!learn sub (@Dopamine mult (@Peptide 1)))
	no ((egal ((!learn 0)))(
			set (!it 0)
			set (!dir div (call (:get_learn_dir 0 (!learn)) 1))
			while (inf ((!it @Synapses^_size))(
					cp (!syn @Synapses^_data (!it))
					and ((
							egal ((* (* (!syn 1) /SynapsesDest) /Impulse))
							sup ((* (* (!syn 1) /LastImpulse) 1))
						)(
							set (!tmp * (!syn 2))
							echo (!tmp " ")
							set (!tmp add (!tmp div (!dir 10)))
							echo (!dir " => " !tmp " ")
							set (* (!syn 2) !tmp)
					))
					set (!it add (!it 1))
			))
			set (* (@Nucleus /Learn) !dir)
			set (@Dopamine 0)
			set (@Peptide 0)
	))
	))
)>

Membrane<(
	sup ((@Impulse 0)(
			inf ((* (@Nucleus /Active) 1)(
					set (* (@Nucleus /Impulse) add (* (@Nucleus /Impulse) div (@Impulse 10)))
			))
			set (@Impulse 0)
	)(set (@Impulse 0)))
)>

ExprMembrane<(
	sup ((@Nucleus 0)(
			:Init ((set (!ok 1) attach ((:Membrane :MembraneLearn))))
	))
	sup ((!ok 0)(:freeAndKill))
)>

Neuron<(
	:Init ((
			set (@ImNeuron 1)
			attach ((:ExprMembrane :SetUp))
	))
	:freeAndKill
)>