[
	#
	#	Basic function of std
	#
]


[
	# Copy Functions to Variable # 
]

<
	?Init 		inf ((!__init__ 1)(;
	?ie__			set (!__init__ 1)));
>

Init_Std<(
	:Init ( (
			[ Basic Function ]
			cp ( #__construct__ :__construct__ )
			cp ( #__obj__ :__obj_call__ )
			cp ( #__new__ :__new__ )
			cp ( #__push__ :__push__ )
			cp ( #__pop__ :__pop__ )

			[ Object ]
			cp ( #__Array :Array|Construct )
			cp ( #__LinkList :LinkList|Construct )
			cp ( #__Interaction :Interaction|Construct )
			cp ( #__Class :Class|Construct )
			cp ( #__Module :Module|Construct )
			cp ( #__Descriptor :Descriptor|Construct )
	) )
)>

Init($code)<(
	inf ((!it 1)($code set (!it 1)))
)>

__new__<(
	cp (!local 0)
	cp (!ptr % ( !local^0))
	ret (!ptr)
)>

[
	#count node's son number
	( % ( ) ) -> (int)
]

get_pid<(
	cp (@__pid__ rand ())
)>

count<(
	set (!it 0)
	set (!len len (* ( #__av__^0 )))
	set (!res 0)
	while (inf ((!it !len))(
			egal ((* (#__av__^0 !it) #__av__^1)
				(set (!res add (!res 1)))
			)
			set (!it add (!it 1))
	))
	ret (!res)
)>

[
	sort tab
	( %function % () ) -> ()
]

sort<(
	set (!move 1)
	set (!len len (* (#__av__^0)))
	cp (!av #__av__^0)
	cp (!f #__av__^1)
	while (egal ((!move 1))(
		set (!it 1)
		set (!move 0)
		while (inf ((!it !len))(
				egal ((call (* (!f) (* (!av !it) * (!av sub (!it 1)))) 1)(
						set (!move 1)
						cp (!tmp * (!av !it))
						cp (* (!av !it) * (!av sub (!it 1)))
						cp (* (!av sub (!it 1)) !tmp)
				))
				set (!it add (!it 1))
		))
	))
)>
[
	check if only av are present
	( % () ())	-> (float)
]

only<(
	set (!it 0 )
	set (!len len (* (#__av__^0)))
	set (!av len (#__av__ ))
	while (inf ((!it !len ))(
			set (!i 1 )
			set (!ok 0 )
			while (inf ((!i !av ))(
					egal ((* ( #__av__^0 !it ) #__av__ (!i))(
							set (!i !av)
							set (!ok 1)
					))
					set (!i add (!i 1))
			))
			egal ((!ok 0)(ret (0)))
			set (!it add (!it 1))
	))
	ret (1)
)>

[
	get float from string
	( () ) -> (float)
]

get_nbr<(
	set (!it #__av__^1)
	set (!len len ( #__av__^0))
	set (!nb 0)
	set (!decimal 0)
	while (and ((
					inf ((!it !len))
					no ((egal ((#__av__^0 (!it) ".") (set (!decimal 1)))))
		))(
			set (!nb mult (!nb 10))
			set (!nb add (!nb sub ( #__av__^0 (!it) "0")))
			set (!it add (!it 1))
	))
	egal ((!decimal 1)(
		set (!div pow (10 sub (!len add (!it 1))))
		cp (!str #__av__^0)
		call (#__push__ 0 (!nb))
		cp (!res call (#GetNbr 0 (!str add (!it 1))))
		set (!nb add (call (#__pop__) div (!res !div)))
	))
	ret (!nb)
)>
