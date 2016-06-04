
Dendrite|rplsOth|exec<(
	or ((
			sup ((* (#__oth__ /Dendrite) 0))
			sup ((* (#__oth__ /Cell) 0))
		)(
			egal ((* (#__oth__ /__pid__) @__pid__)(
					set (@__pos__^0 sub (@__pos__^0 div (#__vct__^0 0.4)))
					set (@__pos__^1 sub (@__pos__^1 div (#__vct__^1 0.4)))
				)(
					set (@__pos__^0 sub (@__pos__^0 div (#__vct__^0 2)))
					set (@__pos__^1 sub (@__pos__^1 div (#__vct__^1 2)))
			))
			move
	))
)>

[
	Link NDendrite
]

Dendrite|linkNeuron|exec<(
	sup ((* (#__oth__ /Neuron) 0)(
			set (* (#this /_param ?limit 0) 0)
			cp (* (#__oth__ /Dendrite len (* (#__oth__ /Dendrite))) % (@))
			cp (@Neuron % (* (#__oth__)))
			ret (1)
	))
)>

[
	Atr by Input
]

Dendrite|atrIn|clean<(
	inf ((* (#this /_param ?limit 0) 1)(
			sup ((incr (!time) 5)(
					set (* (#this /_param ?limit 0) 1)
					set (!time 0)
			))
		)(
			sup ((* (#this /_found) 0)(
					set (@__pos__^0 add (@__pos__^0 div (* (#this /_near 0) 0.2)))
					set (@__pos__^1 add (@__pos__^1 div (* (#this /_near 1) 0.2)))
					
					inf ((@GrowEnd 1)(
					cp (!vct call (:get_full_vct 0 (% (@__pos__) % (* (@Neuron /__pos__)))))
					sup ((!vct^2 20)(
							set (!tmp sub (!vct^2 20))
							set (!tmp div (!tmp !vct^2))
							set (!vct^0 mult (!vct^0 !tmp))
							set (!vct^1 mult (!vct^1 !tmp))
							set (@__pos__^0 sub (@__pos__^0 !vct^0))
							set (@__pos__^1 sub (@__pos__^1 !vct^1))
					))
					))
					cp (* (#this /_near) 0)
					move
			))
			decr (* (#this /_param ?limit 0))
	))
)>

Dendrite|exprAxonAtr<(
	sup ((incr (!t) 200)(
			?Init
				set (@GrowEnd 1)
				cp (&atrByAxon^_exec :Utils|findNear|exec (/Axon))
				cp (&atrByAxon^_clean :Dendrite|atrIn|clean)
				cp (&atrByAxon^_param 0 (80 5 ?scope (?oth) ?manual ?limit (1))))

				attach ((:Utils|stopInteraction (/atrByAxon 650)))
			?ie__
			:Utils|freeAndKill
	))
)>

Dendrite|grow<(
	?Init
		cp (&atrByIn^_exec :Utils|findNear|exec (/Input))
		cp (&atrByIn^_clean :Dendrite|atrIn|clean)
		cp (&atrByIn^_param 0 (400 0 ?scope (?oth) ?manual ?limit (1)))
		
		cp (&rplsOth^_exec :Dendrite|rplsOth|exec )
		cp (&rplsOth^_clean :Cell|rplsOther|clean)
		cp (&rplsOth^_param 0 (20 0 ?scope (?oth) ?manual ?limit (1)))

		attach ((:Utils|stopInteraction (/atrByIn 400) :Dendrite|exprAxonAtr))
		attach ((:Utils|stopInteraction (/rplsOth 700)))
	?ie__
	:Utils|freeAndKill
)>

Dendrite|linkNeuron<(
	attach ((
			:Utils|linkWith (
					/linkAxon ?parent
					:Dendrite|linkNeuron|exec
					@Neuron
					nil (
						go_out
						attach ((:Dendrite|grow))
					)
			)
	))
)>

Dendrite<(
	:Utils|init ((
			set (@Dendrite 1)
			:Dendrite|linkNeuron
	))
)>