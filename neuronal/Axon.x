
[ Go to target layer ]

atrto|exec<(
	and ((
			inf ((* (#__oth__ /NoLayer) 1))
			egal ((@Target * (#__oth__ /LayerId)))
		)(
			set (@__pos__^0 add (@__pos__^0 mult (#__vct__^0 5)))
			set (@__pos__^1 add (@__pos__^1 mult (#__vct__^1 5)))
			inf ((#__vct__^2 10)(
					set (* (#this /_param ?limit 0) 0)
					set (@InTarget 1)
					ret (1)
			))
	))
)>

atrto|clean<(
	set (&GoToTarget^_param^?limit^0 0)
	move
)>

[ Get all layer's neurons ]

getneuron|exec<(
	sup ((* (#__oth__ /Neuron) 0)(
			set (cp (!id /NeuronId) * (#__oth__ /__pid__))
			set (cp (!axonId /AxonId) @__pid__)
			cp (!res call (:Synapse|new 0 (% (* (#__oth__)) % (@))))
			cp (@NeuronList (!id) !res)
			cp (* (#__oth__ /Synapse !axonId) !res)
	))
)>

getneuron|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

[ link with parent ]

link|exec($chan $son $parent)<(
	sup ((* (#__oth__ $chan) 0)(
			set (* (#this /_ok) 1)
			cp (* (#__oth__ $son) % (@))
			cp (@ ($parent) % (* (#__oth__)))
			ret (1)
	))
)>

link|clean<(
	set (* (#this /_param ?limit 0) 0)
)>


Axon|Init<(
	:Init ((
		set (@__pid__ rand )
		cp (&GoToTarget^_exec :atrto|exec)
		cp (&GoToTarget^_clean :atrto|clean)
		cp (&GoToTarget^_param 0 (250 0 0 ?comin ?limit (0)))

		cp (&LinkParent^_exec :link|exec (/Neuron /Axon /Parent))
		cp (&LinkParent^_clean :link|clean)
		cp (&LinkParent^_param 0 (10 0 ?scope (?parent) ?link ?limit (1)))
	))
)>

Axon|ToTarget<(
	inf ((@InTarget 1)(
			sup ((&LinkParent^_ok 0)(
					inf ((!takeout 2)(set (!takeout add (!takeout 1)) take_out))
			))
			sup ((set (!time add (!time 1)) 10)(
					set (!time 0)
					set (&GoToTarget^_param^?limit^0 1)
			))
		)(
			:Init ((
					cp (&GetAllNeuron^_exec :getneuron|exec)
					cp (&GetAllNeuron^_clean :getneuron|clean)
					cp (&GetAllNeuron^_param 0 (250 0 ?scope (?oth) ?manual ?limit (1)))
			))
	))
)>

Axon<(
	:Axon|Init
	:Axon|ToTarget
	sup ((@Impulse 5)(
			set (!len len (@NeuronList))
			set (!it 0)
			while (inf ((!it !len))(
					call (:Synapse|SendTo 0 (* (@NeuronList (!it) 0) /Impulse /Input * (@NeuronList (!it) 1)))
					set (!it add (!it 1))
			))
			set (@Impulse 0)
	))
)>