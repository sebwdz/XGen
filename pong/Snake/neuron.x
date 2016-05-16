
[ NEURON ]

Neuron|RplsOth|exec<(
	sup ((* (#__oth__ /ImNeuron) 0)(
			cp (@__pos__ 0 (sub (@__pos__^0 #__vct__^0)
				sub (@__pos__^1 #__vct__^1)))
	))
)>

Neuron|RplsOth|clean<(
	move
)>

SetUp<(
	:Init ((
			cp (&RplsOthNeuron 0 (
					{_exec :Neuron|RplsOth|exec}
					{_clean :Neuron|RplsOth|clean}
					{_param 0 (30 0 ?scope (?oth) ?manual ?limit (1))}
			))
	))
	sup ((incr (!t) 50)(
			erase (& /RplsOthNeuron)
			:freeAndKill
	))
)>

get_learn_dir<(
	set (!learn #__av__^0)
	set (!accu * (@Nucleus /Accu))
	sup ((!learn 0)(
			set (!rate sup ((!accu 3)(./ (.- (6 !accu) 3))(./ (!accu 3))))
		)(
			set (!rate sup ((!accu 3)(./ (!accu 6))(./ (.- (6 !accu) 3))))
	))
	sup ((!rate 0)(
			set (!dir sup ((!accu 3)(!learn)(.- (0 !learn))))
			.* (!dir !rate)
	)(set (!dir 0)))
)>

Membrane|DopLearn<(
	cp (!syn #__av__^0)
	egal ((* (* (!syn 1) /SynapsesDest) /Dopamine)(
			sup ((@Dopamine 0.001)(
					sup ((* (@Nucleus /Accu) 3)(
							call (:Synapse|learn 0 (!syn /DopPositive mult (@DopPositive -0.0005)))
						)(
							call (:Synapse|learn 0 (!syn /DopNegative mult (@DopNegative -0.0005)))
					))
				)(
					set (!rate 0.0001)
					call (:Synapse|learn 0 (!syn /DopNegative mult (@DopNegative !rate)))
					call (:Synapse|learn 0 (!syn /DopPositive mult (@DopPositive !rate)))
			))
	))
)>

MembraneLearn<(
	inf ((@Input 1)(
	sup ((* (@Nucleus /Accu) 3)(
			set (@Dopamine @DopPositive)
	)(set (@Dopamine @DopNegative)))
	set (!learn sub (@Dopamine mult (@Peptide 2)))
	no ((egal ((!learn 0)))(
			set (!it 0)
			set (!use call (:get_learn_dir 0 (!learn)) 1)
			while (inf ((!it @Synapses^_size))(
					set (!dir mult (!use div (mod (rand 100) 100)))
					cp (!syn @Synapses^_data (!it))
					sup ((* (* (!syn 1) /LastImpulse) 3)(
							egal ((* (* (!syn 1) /SynapsesDest) /Impulse)(
									call (:Synapse|learn 0 (!syn /Impulse !dir))
								)(
									call (:Membrane|DopLearn 0 (!syn !dir))
							))
					))
					incr (!it)
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
			incr (!it)
	))
	and ((sup ((@Impulse 0)) inf ((* (@Nucleus /Active) 1)))(
			incr (* (@Nucleus /Impulse) div (@Impulse 1))
	))
	set (@Impulse 0)
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