
[
	wait for axon linkage
]

NeuronNucleus|waitAxon<(
	sup ((@Axon 0)(
			?Init
					cp (* (@Axon /Nucleus) % (@))
					set (!kill 1)
			?ie__
	))
	sup ((!kill 0)(:Utils|freeAndKill))
)>

[
	expr Axon
]

NeuronNucleus|exprAxon<(
	sup ((incr (!time) 100)(
			?Init
					create ((:Axon))
					attach ((:NeuronNucleus|waitAxon))
			?ie__
			:Utils|freeAndKill
	))
)>

[
	code of Neuron Nucleus
]

NeuronNucleus<(
	:Utils|init ((
			set (@NeuronNucleus 1)
			share (/__pid__)
			inf ((@WithoutAxon 1)(
					attach ((:NeuronNucleus|exprAxon))
			))
	))
	:Utils|freeAndKill
)>