
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
	div (!learn 10)
	sup ((* (@Nucleus /Accu) 3)(
			sup ((!learn 0)(set (!dir !learn))
				(set (!dir !learn)))
		)(
			sup ((!learn 0)(set (!dir sub (0 !learn)))
				(set (!dir sub (0 !learn))))
	))
	ret (div (!dir 10))
)>

Membrane|DopLearn<(
	egal ((* (* (!syn 1) /SynapsesDest) /Dopamine)(
			[echo ("Dopamine !\n")]
			sup ((@Dopamine 0.05)(
					sup ((* (@Nucleus /Accu) 3)(
							call (:Synapse|learn 0 (!syn /DopPositive mult (@DopPositive -0.01)))
						)(
							call (:Synapse|learn 0 (!syn /DopNegative mult (@DopNegative -0.01)))
					))
				)(
					call (:Synapse|learn 0 (!syn /DopNegative mult (@DopNegative 0.0001)))
					call (:Synapse|learn 0 (!syn /DopPositive mult (@DopPositive 0.0001)))
			))
	))
)>

MembraneLearn<(
	inf ((@Input 1)(
	sup ((* (@Nucleus /Accu) 3)(
			set (@Dopamine @DopPositive)
	)(set (@Dopamine @DopNegative)))
	[no ((egal ((@Dopamine 0)))(
				echo ("Positive dop => " @DopPositive "\n")
				echo ("Negative dop => " @DopNegative "\n")
	))]
	set (!learn sub (@Dopamine @Peptide))
	no ((egal ((!learn 0)))(
			set (!it 0)
			set (!dir div (call (:get_learn_dir 0 (!learn)) 1))
			while (inf ((!it @Synapses^_size))(
					cp (!syn @Synapses^_data (!it))
					sup ((* (* (!syn 1) /LastImpulse) 2)(
							egal ((* (* (!syn 1) /SynapsesDest) /Impulse)(
									call (:Synapse|learn 0 (!syn /Impulse !dir))
								)(
									
							))
					))
					set (!it add (!it 1))
			))
			set (* (@Nucleus /Learn) !dir)
			set (@Dopamine set (@Peptide set (@DopNegative set (@DopPositive 0))))
	))
	))
)>

Membrane<(
	set (!it 0)
	while (inf ((!it @Synapses^_size))(
			cp (!syn @Synapses^_data (!it))
			call (:Synapse|get 0 (!syn /Impulse))
			call (:Synapse|get 0 (!syn /DopPositive))
			call (:Synapse|get 0 (!syn /DopNegative))
			call (:Synapse|get 0 (!syn /Peptide))
			cp (* (!syn 4) 0)
			set (!it add (!it 1))
	))
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