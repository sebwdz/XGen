
[
	Neuron code
]

Neuron|exprDendrites<(
	sup ((incr (!time) 600)(
			share (/__pid__)
			inf ((#Dendrites 4)(
					new_head ((:Dendrite))
					incr (#Dendrites)	
			)(:Utils|freeAndKill))
	))
)>

Neuron<(
	:Utils|init ((
			set (@Neuron 1)
			inf ((@Initial 1)(
					inf ((@Sens 1)(
							set (&rplsOther^_param^0 40)
					)(set (&rplsOther^_param^0 0)))
					cp (&rplsOther^_exec :Cell|rplsOther|exec (/Neuron 1))
			))

			inf ((@Sens 1)(
					cp (&rplsOut^_exec :Cell|rplsOther|exec(/Output 0.1))
					cp (&rplsOut^_clean :Cell|rplsOther|clean)
					cp (&rplsOut^_param 0 (40 0 ?scope (?oth) ?manual ?limit (1)))

					cp (&rplsInput^_exec :Cell|rplsOther|exec(/Input 0.2))
					cp (&rplsInput^_clean :Cell|rplsOther|clean)
					cp (&rplsInput^_param 0 (40 0 ?scope (?oth) ?manual ?limit (1)))
					
					attach ((:Utils|stopInteraction (/rplsOut 300)))
					attach ((:Utils|stopInteraction (/rplsInput 220)))
			))
			attach ((:Utils|stopInteraction (/rplsOther 400)))

			inf ((@WithoutDendrite 1)(
					attach ((:Neuron|exprDendrites))
			))
			attach ((:Neuron|transmitImpulse))
	))
	:Utils|freeAndKill
)>

Neuron|transmitImpulse<(
	sup ((@Impulse 0)(
			incr (* (@NucleusPtr /Impulse) @Impulse)
			set (@Impulse 0)
	))
)>