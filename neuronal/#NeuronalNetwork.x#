
Layer<(
	:Init ((
			set (@NeuronId 0)
			set (@Target * (@Conf 1))
			shared (/NeuronId /Target /NoAxon /Center /Input /Brain)
			cp (@__pos__ 0 (mult (@LayerId 40) 0))
			set (@__pos__^0 sub (@__pos__^0 20))
			set (@Center mult (20 div (* (@Conf 0) 2)))
			move
	))
	inf ((@NeuronId * (@Conf 0))(
			new_head ((:Neuron))
			set (@NeuronId add (@NeuronId 1))
	))
)>

make_conf<(
	cp (!conf % (0 (
				0 (2 1)
				0 (3 2)
				0 (1)
	)))
	ret (!conf)
)>

GenerateBrain<(
	:Init ((
			cp (#conf call (:make_conf))
			set (#Len sub (len (* (#conf)) 1))
			set (@NoLayer 1)
			shared (/LayerId /NoAxon /Conf /Input /Brain)
			set (@LayerId -1)
			cp (@Brain % (@))
	))
	inf ((@LayerId #Len)(
			inf ((@LayerId 0)(set (@Input 1))(set (@Input 0)))
			sup ((set (@LayerId add (@LayerId 1)) sub (#Len 1))( set (@NoAxon 1)))
			cp (@Conf % (* (#conf @LayerId)))
			new_head ((:Layer))
		))
	))
)>

get_test<(
	cp (!conf % (0 (
					0 (0 (10 10) 0 (10))
					0 (0 (10 0) 0 (0))
					0 (0 (0 10) 0 (0))
					0 (0 (0 0) 0 (0))
	)))
	ret (!conf)
)>

run_test<(
	:Init ((cp (#test call (:get_test))))
	sup ((set (!time add (!time 1)) 50)(
			set (!it add (!it 1))
			egal ((!it len (* (#test)))(set (!it 0)))
			set (!time 0)
			set (!last 0)
	))
	inf ((!time 40)(
			set (* (@Input^0 /Input) add (* (#test !it 0 0) * (@Input^0 /Input)))
			set (* (@Input^1 /Input) add (* (#test !it 0 1) * (@Input^1 /Input)))
	))
	set (!out * (@Output^0 /Impulse))
	set (!wait * (#test !it 1 0))
	sup ((sub (!time !last) 5)(
			sup ((!out 0)(set (!last !time)))
			or ((sup ((!out !wait)) egal ((!out !wait)))(
					and ((inf ((!wait 1)) sup ((!out 9)))(
							echo ("BAD!")
						)(
							echo ("GOOD!")
					))
				)(
					sup ((!wait 0)(
							echo ("BAD!")
						)(
							echo ("GOOD!")
					))
			))
			echo ("\t\t" !wait " => " !out "\n")
	))
)>

main<(
	:GenerateBrain
	sup ((len (@Output) 0)(:run_test))
)>