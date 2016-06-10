
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
					attach ((:NeuronNucleus|accuImpulse :NeuronNucleus|active))
			))
	))
	:Utils|freeAndKill
)>

[ Accu impulse ]

NeuronNucleus|accuImpulse<(
	sup ((@Impulse 0)(
			incr (@StockImpulse @Impulse)
			set (@Impulse 0)
		)(
			decr (@StockImpulse 0.01)
	))
)>

[ Active Nucleus ]

NeuronNucleus|active<(
	sup ((@StockImpulse @Biais)(
			incr (* (@Axon /Impulse) @StockImpulse)
			set (@StockImpulse 0)
	))
)>