
[
	found target
]

GrowCone|goToTarget|exec<(
	sup ((* (#__oth__ /Output) 0)(
			or ((
					inf ((#__vct__^2 * (#this /_near 2)))
					inf ((* (#this /_near 2) 1))
				)(
					set (* (#this /_found) 1)
					cp (* (#this /_near) #__vct__)
			))
	))
)>

[
	clean go To target every each time
]

GrowCone|goToTarget|clean<(
	inf ((* (#this /_param ?limit 0) 1)(
			sup ((incr (!time) 2)(
					set (* (#this /_param ?limit 0) 1)
					set (!time 0)
			))
		)(
			sup ((* (#this /_found) 0)(
					set (@__pos__^0 add (@__pos__^0 div (* (#this /_near 0) @pow)))
					set (@__pos__^1 add (@__pos__^1 div (* (#this /_near 1) @pow)))
					cp (!vct call (:get_full_vct 0 (% (@__pos__) % (* (@Nucleus /__pos__)))))
					inf ((@GrowEnd 1)(
					sup ((!vct^2 40)(
							set (!tmp sub (!vct^2 40))
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

[
	create "to target" interaction
]

GrowCone|goToTarget<(
	:Utils|init ((
			set (@pow 0.3)
			cp (&goToTarget^_exec :GrowCone|goToTarget|exec)
			cp (&goToTarget^_clean :GrowCone|goToTarget|clean)
			cp (&goToTarget^_param 0 (300 0 ?scope (?oth) ?manual ?limit (1)))

			cp (&rplsCell^_exec :Cell|rplsOther|exec(/Neuron 0.8))
			cp (&rplsCell^_clean :Cell|rplsOther|clean)
			cp (&rplsCell^_param 0 (20 0 ?scope (?oth) ?manual ?limit (1)))

			cp (&rplsAxon^_exec :Cell|rplsOther|exec(/Axon 2))
			cp (&rplsAxon^_clean :Cell|rplsOther|clean)
			cp (&rplsAxon^_param 0 (30 0 ?scope (?oth) ?manual ?limit (1)))

			cp (&atrByIn^_exec :Utils|findNear|exec (/Dendrite))
			cp (&atrByIn^_clean :GrowCone|goToTarget|clean)
			cp (&atrByIn^_param 0 (80 0 ?scope (?oth) ?manual ?limit (1)))

			attach ((:Utils|stopInteraction (/goToTarget 500)))
			attach ((:Utils|stopInteraction (/rplsAxon 700)))
			attach ((:Utils|stopInteraction (/rplsCell 300)))
			attach ((:Utils|stopInteraction (/atrByIn 600)))
	))
	sup ((incr (!time) 300)(:Utils|freeAndKill set (@pow 0.5) set (@GrowEnd 1)))
)>

[
	grow cone main code
]

GrowCone<(
	:Utils|init ((
			attach ((:GrowCone|goToTarget ()))
	))
	:Utils|freeAndKill	
)>