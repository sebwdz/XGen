
[
	Neuron code
]

Neuron|exprDendrites<(
	sup ((incr (!time) 200)(
			share (/__pid__)
			inf ((#Dendrites 2)(
					echo ("n Dendrites " @__pid__ "\n")
					new_head ((:Dendrite))
					incr (#Dendrites)	
			)(:Utils|freeAndKill))
	))
)>

Neuron<(
	:Utils|init ((
			set (@Neuron 1)
			set (&rplsOther^_param^0 40)
			set (&rplsOther^_exec :Cell|rplsOther|exec (/Neuron 2))

			inf ((@Sens 1)(
					cp (&rplsOut^_exec :Cell|rplsOther|exec(/Output 0.1))
					cp (&rplsOut^_clean :Cell|rplsOther|clean)
					cp (&rplsOut^_param 0 (30 0 ?scope (?oth) ?manual ?limit (1)))

					cp (&rplsInput^_exec :Cell|rplsOther|exec(/Input 0.2))
					cp (&rplsInput^_clean :Cell|rplsOther|clean)
					cp (&rplsInput^_param 0 (30 0 ?scope (?oth) ?manual ?limit (1)))
					
					attach ((:Utils|stopInteraction (/rplsOther 600)))
					attach ((:Utils|stopInteraction (/rplsOut 600)))
			))
			attach ((:Utils|stopInteraction (/rplsInput 420)))

			inf ((@WithoutDendrite 1)(
					attach ((:Neuron|exprDendrites))
			))
	))
	:Utils|freeAndKill
)>