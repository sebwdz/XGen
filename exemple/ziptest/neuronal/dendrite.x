
Dendrite|managerSynapses<(
	sup ((@PoolZone 0)(
			:Synapse|receptor (/Impulse
					sup ((* (@PoolZone /Impulse) 0)(
							* (@PoolZone /Impulse)
			)))
	))
	sup ((@Impulse 0)(
		incr (* (@NeuronPtr /Impulse) @Impulse)
		set (@Impulse 0)
	))
)>

Dendrite|getPoolZone|exec<(
	sup ((* (#__oth__ /Axon) 0)(
			no ((egal ((* (#__oth__ /__pid__) @__pid__)))(
					cp (@PoolZone (* (#__oth__ /__pid__) 0) * (#__oth__ /PoolZone))
					cp (@PoolZone (* (#__oth__ /__pid__) 1) @Previous (* (#__oth__ /__pid__) 1))
			))
	))
)>

Dendrite|getPoolZone|clean<(
	inf ((* (#this /_param ?limit 0) 1)(
			sup ((incr (!time) 100)(
					set (* (#this /_param ?limit 0) 1)
					cp (@Previous @PoolZone)
					cp (@PoolZone 0)
					set (!time 0)
			))
	)(set (* (#this /_param ?limit 0) 0)))
)>

Dendrite|rplsOth|exec<(
	sup ((* (#__oth__ /Dendrite) 0)(
			egal ((* (#__oth__ /__pid__) @__pid__)(
					set (@__pos__^0 sub (@__pos__^0 div (#__vct__^0 0.1)))
					set (@__pos__^1 sub (@__pos__^1 div (#__vct__^1 0.1)))
				)(
					set (@__pos__^0 sub (@__pos__^0 div (#__vct__^0 1)))
					set (@__pos__^1 sub (@__pos__^1 div (#__vct__^1 1)))
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
			cp (@NeuronPtr % (* (#__oth__)))
			ret (1)
	))
)>

[
	Atr by Input
]

Dendrite|atrIn|clean<(
	inf ((* (#this /_param ?limit 0) 1)(
			sup ((incr (!time) 2)(
					set (* (#this /_param ?limit 0) 1)
					set (!time 0)
			))
		)(
			sup ((* (#this /_found) 0)(
					set (@__pos__^0 add (@__pos__^0 div (* (#this /_near 0) 1050)))
					set (@__pos__^1 add (@__pos__^1 div (* (#this /_near 1) 1050)))
					
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
	sup ((incr (!t) 300)(
			?Init
				set (@GrowEnd 1)
				cp (&atrByAxon^_exec :Utils|findNear|exec (/Axon))
				cp (&atrByAxon^_clean :Dendrite|atrIn|clean)
				cp (&atrByAxon^_param 0 (80 0 ?scope (?oth) ?manual ?limit (1))))

				attach ((:Utils|stopInteraction (/atrByAxon 500)))
			?ie__
			:Utils|freeAndKill
	))
)>

Dendrite|grow<(
	?Init
		[cp (&atrByIn^_exec :Utils|findNear|exec (/Input))
		cp (&atrByIn^_clean :Dendrite|atrIn|clean)
		cp (&atrByIn^_param 0 (300 0 ?scope (?oth) ?manual ?limit (1)))]
		
		cp (&rplsOth^_exec :Dendrite|rplsOth|exec)
		cp (&rplsOth^_clean :Cell|rplsOther|clean)
		cp (&rplsOth^_param 0 (10 0 ?scope (?oth) ?manual ?limit (1)))

		cp (&getPoolZone^_exec :Dendrite|getPoolZone|exec)
		cp (&getPoolZone^_clean :Dendrite|getPoolZone|clean)
		cp (&getPoolZone^_param 0 (30 0 ?scope (?oth) ?manual ?limit (1)))

		attach ((:Utils|stopInteraction (/atrByIn 300) :Dendrite|exprAxonAtr))
		attach ((:Utils|stopInteraction (/rplsOth 500)))
		attach ((:Dendrite|managerSynapses))
	?ie__
	:Utils|freeAndKill
)>

Dendrite|linkNeuron<(
	attach ((
			:Utils|linkWith (
					/linkDendrite ?parent
					:Dendrite|linkNeuron|exec
					@NeuronPtr
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