
atrto|exec<(
	and ((
			inf ((* (#__oth__ /NoLayer) 1))
			egal ((@Target * (#__oth__ /LayerId)))
		)(
			set (@__pos__^0 add (@__pos__^0 mult (#__vct__^0 5)))
			[set (@__pos__^1 add (@__pos__^1 mult (#__vct__^1 5)))]
			inf ((mult (#__vct__^0 #__vct__^2) 10)(
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

link|exec($chan)<(
	sup ((* (#__oth__ $chan) 0)(
			set (* (#this /_ok) 1)
			cp (* (#__oth__ /Axon) % (@))
			ret (1)
	))
)>

link|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

getneuron|exec<(
	sup ((* (#__oth__ /Neuron) 0)(
			cp (@NeuronList (* (#__oth__ /NeuronId) 0) % (* (#__oth__)))
			cp (@NeuronList (* (#__oth__ /NeuronId) 1) div (sub (mod (rand 10) 5) 10))
	))
)>

getneuron|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

Axon|Init<(
	:Init ((
		cp (&GoToTarget^_exec :atrto|exec)
		cp (&GoToTarget^_clean :atrto|clean)
		cp (&GoToTarget^_param 0 (150 0 0 ?comin ?limit (0)))

		cp (&LinkParent^_exec :link|exec (/Neuron))
		cp (&LinkParent^_clean :link|clean)
		cp (&LinkParent^_param 0 (10 0 ?scope (?parent) ?link ?limit (1)))
	))
)>

Axon|ToTarget<(
	inf ((@InTarget 1)(
			sup ((&LinkParent^_ok 0)(
					inf ((!takeout 2)(set (!takeout add (!takeout 1)) take_out))
			))
			sup ((set (!time add (!time 1)) 100)(
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
			set (!it 1)
			while (inf ((!it !len))(
					cp (!to % (* (@NeuronList (!it 0) /Impulse)))
					set (* (!to) add (* (!to) mult (@NeuronList (!it 1) @Impulse)))
					set (!it add (!it 1))
			))
			set (@Impulse 0)
	))
)>

Neuron<(
	:Init ((
		shared (/Target)
		set (@Neuron 1)
		set (@__pos__^1 sub (mult (@NeuronId 20) 10))
		move
		inf ((@NoAxon 1)(new_head ((:Axon))))
	))
	egal ((@LayerId 0)(
			set (@Impulse add (@Impulse 1))
	))
	set (@Snake @Impulse)
	sup ((@Impulse 10)(
			set (* (@Axon /Impulse) @Impulse)
			set (@Impulse 0)
	))
)>

Layer<(
	:Init ((
			set (@NeuronId 0)
			shared (/NeuronId /Target /NoAxon /LayerId)
			cp (@__pos__ 0 (mult (@LayerId 30) 0))
			set (@__pos__^0 sub (@__pos__^0 20))
			move
	))
	inf ((@NeuronId 4)(
			new_head ((:Neuron))
			set (@NeuronId add (@NeuronId 1))
	))
)>

main<(
	:Init ((
			set (@NoLayer 1)
			shared (/LayerId /Target /NoAxon)
			set (@LayerId -1)
			set (#Max 5)
	))
	inf ((@LayerId #Max)(
			sup ((set (@LayerId add (@LayerId 1)) sub (#Max 1))( set (@NoAxon 1)))
			creat ((:Layer))
			set (@Target add (@Target 1))
	))
)>