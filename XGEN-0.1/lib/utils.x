
Utils|find_str<(
	set (!it 0)
	while (inf ((!it len (* (#__av__^1))))(
			egal ((* (#__av__^1 !it) #__av__^0)(ret (1)))
			incr (!it)
	))
	ret (0)
)>

Utils|init($code)<(
	inf ((!x 1)(set (!x 1) $code))
)>

Utils|concat_str<(
	cp (!res 0)
	set (!it 0)
	set (!x 0)
	while (inf ((!it len (#__av__)))(
			set (!tmp 0)
			while (inf ((!tmp len (#__av__ (!it))))(
					set (!res (!x) #__av__ (!it !tmp))
					incr (!x)
					incr (!tmp)
			))
			incr (!it)
	))
	ret (!res)
)>

Utils|int_to_string<(
	cp (! 0 ({int #__av__^0}))
	cp (!str 0)
	set (!tmp 1)
	while (sup ((div (!int !tmp) 10))(set (!tmp .* (!tmp 10))))
	while (sup ((!tmp 0.1))(
			set (!val round (div (!int !tmp) 0))
			decr (!int .* (!val !tmp))
			set (!str (len (!str)) add (!val "0"))
			set (!tmp ./ (!tmp 10))
	))
	ret (!str)
)>