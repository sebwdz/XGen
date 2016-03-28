
[ UTILS ]

freeAndKill<(
	:Init ((free ))
	sup ((set (!t add (!t 1)) 1)(kill ))
)>

Push<(
	cp (* (#__av__^0 /_data * (#__av__^0 /_size)) #__av__^1)
	set (* (#__av__^0 /_size) add (* (#__av__^0 /_size) 1))
)>

[ SYNAPSE ]

Synapse<(
	cp (!syn % ((#__av__^0 #__av__^1)))
	egal ((@SynapsesDest /Impulse)(
			set (* (!syn 2) sub (div (mod (rand 100) 100) 5))
	)(set (* (!syn 2) 1)))
	cp (!av #__av__)
	call (:Push 0 (% (* (!av^0 /Synapses)) !syn))
	call (:Push 0 (% (* (!av^1 /Synapses)) !syn))
)>

[ GROWTH CONE ]

AtrByNeuron|exec<(
	and ((
			sup ((* (#__oth__ /ImNeuron) 0))
			inf ((* (#__oth__ /Input) 1))
			no ((egal ((* (#__oth__  /CellId) @Id))))
			egal ((* (#__oth__ /SynapsesDest) /Impulse))
		)(
			call (:Synapse 0 (% (* (#__oth__)) % (@)))
	))
)>

AtrByNeuron|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

RplsNucleus|exec<(
	and ((
			inf ((#__vct__^2 20))
			sup ((* (#__oth__ /ImNucleus) 0))
		)(
			set (@__pos__^0 sub (@__pos__^0 mult (#__vct__^0 3)))
			set (@__pos__^1 sub (@__pos__^1 mult (#__vct__^1 3)))
	))
)>

RplsNucleus|clean<(
	sup ((* (#this /_param ?limit 0) 0)(
			cp (* (#this /_param ?limit 0) 0)
			move
		)(sup ((set (!time add (!time 1)) 50)(
				cp (* (#this /_param ?limit 0) 1)
				set (!time 1)
		))
	))
)>

AxonLink<(
	:Init ((
			cp (&AtrByNeuron^_exec :AtrByNeuron|exec)
			cp (&AtrByNeuron^_clean :AtrByNeuron|clean)
			cp (&AtrByNeuron^_param 0 (150 1 ?scope (?oth) ?manual ?limit (1)))
	))
	inf ((&AtrByNeuron^_param^?limit^0 1)(
			erase (& /AtrByNeuron)
			:freeAndKill
	))
)>

ExprAtr<(
	sup ((set (!time add (!time 1)) 200)(
			set (!ok 1)
			attach ((:AxonLink))
			erase (& /RplsNucleus)
	))
	sup ((!ok 0)(:freeAndKill))
)>

GrowthCone<(
	:Init ((
			cp (&RplsNucleus^_exec :RplsNucleus|exec)
			cp (&RplsNucleus^_clean :RplsNucleus|clean)
			cp (&RplsNucleus^_param 0 (0 0 ?scope (?link) ?manual ?limit (1)))
			attach ((:ExprAtr))
	))
	:freeAndKill
)>

[ AXON ]

Axon|ExecSynapses<(
	set (@LastImpulse add (div (@LastImpulse 2) @Impulse))
	sup ((@Impulse 1)(
			set (!it 0)
			while (inf ((!it @Synapses^_size))(
					cp (!syn @Synapses^_data (!it))
					set (!val * (* (!syn 0) @SynapsesDest))
					set (!val add (mult (@Impulse * (!syn 2)) !val))
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
					set (!ok)
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
	inf ((!learn 0)(
			sup ((* (@Nucleus /Active) 0)(
					set (!dir !learn)
			)(set (!dir sub (0 !learn))))
		)(
			sup ((* (@Nucleus /Active) 0)(
					set (!dir !learn)
			)(set (!dir sub (0 !learn))))
	))
	ret (!dir)
)>

MembraneLearn<(
	set (!learn sub (@Dopamine @Peptide))
	no ((egal ((!learn 0)))(
			set (!it 0)
			set (!dir div (call (:get_learn_dir 0 (!learn)) 10))
			while (inf ((!it @Synapses^_size))(
					cp (!syn @Synapses^_data (!it))
					and ((
							egal ((* (* (!syn 1) /SynapsesDest) /Impulse))
							sup ((* (* (!syn 1) /LastImpulse) 1))
						)(
							set (!tmp * (!syn 2))
							set (!tmp add (!tmp !dir))
							set (* (!syn 2) set (* (!syn 2) !tmp))
							sup ((* (!syn 2) 10)(set (* (!syn 2) 10)))
							inf ((* (!syn 2) -10)(set (* (!syn 2) -10)))
					))
					set (!it add (!it 1))
			))
			set (* (@Nucleus /Learn) !dir)
			set (@Dopamine set (@Peptide 0))
	))
)>

Membrane<(
	sup ((@Impulse 0)(
			inf ((* (@Nucleus /Active) 1)(
					set (* (@Nucleus /Impulse) add (* (@Nucleus /Impulse) @Impulse))
			))
			set (@Impulse 0)
	))
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

[ CELL ]

Cell<(
	:Init ((
			set (@ImCell 1)
			set (@CellId @Id)
	))
	:freeAndKill
)>

[ NUCLEUS ]

Nucleus|Learn<(
	no ((egal ((@Learn 0)))(
		set (@Biais add (@Biais sub (0 @Learn)))
		set (@Learn 0)
	))
)>

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
			shared (/Id)
			set (@Id rand )
			cp (@CellCode^0 :Cell)
			set (@ImNucleus 1)
			cp (&CominCell^_exec :CominCell|exec)
			cp (&CominCell^_param 0 (10 0 ?scope (?oth) ?comin ?limit (1)))
			take_out
	))
	:freeAndKill
)>

CreatCell<(
	sup ((set (!t2 add (!t2 1)) 15)(:Init ((creat (@CellCode)))))
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

[ NEURON NUCLEUS ]

Input<(
	:Init ((set (@Input 1) call (:Push 0 (% (* (@Parent /Input)) % (@)))))
	:freeAndKill
)>

Output<(
	:Init ((call (:Push 0 (% (* (@Parent /Output)) % (@)))))
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
	sup ((@Impulse 1)(set (@Impulse sub (@Impulse 0.1))))
)>

ImpulseNucleus<(
	sup ((@Active 0)(
			set (* (@Axon /Impulse) add (* (@Axon /Impulse) @Impulse))
			set (@Impulse div (@Impulse 2))
			inf ((@Impulse 1)(
					sup ((set (!time add (!time 1)) 20)(set (!time 0) set (@Active 0)))
			))
		)(
			sup ((@Impulse @Biais)(
					set (@Active 1)
					set (@Impulse 15)
			))
	))
)>

CreatAxon<(
	sup ((@ImInCell 0)(
		set (!in 1)
		:Init ((creat ((:Axon))))
	))
	sup ((@Axon 0)(attach ((:ImpulseNucleus)) :freeAndKill))
)>

NucleusNeuron<(
	:Init ((
			shared (/SynapsesDest)
			attach ((:CreatAxon :IonLeakage))
			set (@Biais div (sub (mod (rand 100) 50) 10))
			cp (@CellCode^1 :Neuron)
			cp (@SynapsesDest /Impulse)
			move
	))
	:freeAndKill
)>

[ MAIN CODE ]

main<(
	inf ((!t3 4)(
			:Init ((
					shared (/__pos__ /Parent)
					cp (@Parent % (@))
			))
			inf ((set (!t add (!t 1)) 7)(
					cp (@__pos__ 0 (sub (mod (rand 30) 15) sub (mod (rand 30) 15)))
					new_head ((:Nucleus))
				)(
				inf ((set (!t2 add (!t2 1)) 3)(
						cp (@__pos__ 0 (sub (mod (rand 30) 15) sub (mod (rand 30) 15)))
						egal ((!t2 1)(
								new_head ((:Nucleus :NeuronDopamine))
						)(new_head ((:Nucleus :NeuronPeptide))))
					)(
						cp (@__pos__ 0 (sub (mod (rand 30) 15) sub (mod (rand 30) 15)))
						inf ((set (!t3 add (!t3 1)) 4)(
								egal ((!t3 1)(
										new_head ((:Nucleus :Output))
								)(new_head ((:Nucleus :Input))))
						))
				))
			))
	))
)>