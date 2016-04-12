
[ SYNAPSE ]

[
	create synapses
	from -> to -> syn
]

Synapse<(
	cp (!syn % ((#__av__^0 #__av__^1)))
	egal ((@SynapsesDest /Impulse)(
			set (* (!syn 2) sub (div (mod (rand 100) 100) 0.5))
	)(set (* (!syn 2) 1)))
	cp (!av #__av__)
	call (:Push 0 (% (* (!av^0 /Synapses)) !syn))
	call (:Push 0 (% (* (!av^1 /Synapses)) !syn))
	ret (!syn)
)>

[
	type = emetor-> from -> % (to) -> ()
	type = receptor -> from -> % (to)  -> ()
]

Synapse|add<(
	cp (!av #__av__)
	and ((egal ((!av^1 /_receptor)) egal ((!av^2 /Impulse)))(
			set (* (!av^3 1) sub (div (mod (rand 100) 100) 0.5))
	)(set (* (!av^3 1) 1)))
	call (:Push 0 (% (* (!av^0 3 !av^1 !av^2)) !av^3))
)>

[
	%synapse -> from -> value -> ()
]

Synapse|exec<(
	cp (!av #__av__)
	cp (!use % (* (!av^0 3 /_emetor !av^1 /_data)))
	set (!len len (* (!use)))
	set (!it 0)
	while (inf ((!it !len))(
			cp (!emit * (!use !it))
			set (* (!av^0 4 * (!emit 0))
					add (* (!av^0 4 * (!emit 0))
						mult (* (!emit 1) !av^2)))
			set (!it add (!it 1))
	))
)>

Synapse|clean<(
	cp (* (!av^0 4) 0)
)>

[
	%synapse -> to -> ()
]

Synapse|learn<(
	cp (!av #__av__)
	cp (!use % (* (!av^0 3 /_receptor !av^1 /_data)))
	set (!len len (* (!use)))
	set (!it 0)
	while (inf ((!it !len))(
			cp (!emit * (!use !it))
			set (!tmp * (!emit 1))
			set (!tmp add (!tmp div (!av^2 10)))
			[echo (!av^2 " => " * (!emit 1) " ")]
			sup ((!tmp 10)(set (!tmp 10)))
			inf ((!tmp -10)(set (!tmp -10)))
			set (* (!emit 1) !tmp)
			set (!it add (!it 1))
	))
)>

[
	get value from synapse
	%syn -> from -> ()
]

Synapse|get<(
	cp (!av #__av__)
	cp (!use % (* (!av^0 3 /_receptor !av^1 /_data)))
	set (!len len (* (!use)))
	set (!it 0)
	while (inf ((!it !len))(
			cp (!emit * (!use !it))
			set (!tmp mult (* (!emit 1) * (!av^0 4 * (!emit 0))))
			set (@ (!av^1) add (!tmp @ (!av^1)))
			set (!it add (!it 1))
	))
)>