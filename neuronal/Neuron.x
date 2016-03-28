
setInputOutput<(
	sup ((@Input 0)(
			set (cp (!id /NeuronId) @NeuronId)
			cp (* (@Brain /Input !id) % (@))
		)(sup ((@NoAxon 0)(
			set (cp (!id /NeuronId) @NeuronId)
			cp (* (@Brain /Output !id) % (@))
		))
	))
)>

Neuron<(
	:Init ((
		set (#Biais div (sub (mod (rand 100) 50) 100))
		set (@__pid__ rand )
		shared (/Target)
		set (@Neuron 1)
		set (@__pos__^1 sub (mult (@NeuronId 20) @Center))
		move
		inf ((@NoAxon 1)(new_head ((:Axon))))
		:setInputOutput
	))
	set (@Snake add (@Impulse @Input))
	inf ((#Active 1)(
			sup ((@Input #Biais)(
					set (#Active 1)
					set (@Impulse 15)
					set (@Input 0)
			))
		)(
			sup ((@Axon 0)(set (* (@Axon /Impulse) @Impulse)))
			inf ((@Impulse 1)
				(set (@Impulse 0) set (#Active 0))
				(set (@Impulse div (@Impulse 5)))
			)
	))
)>