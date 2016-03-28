
[ UTILS ]

freeAndKill<(
	:Init ((free ))
	sup ((set (!t add (!t 1)) 1)(kill ))
)>

Push<(
	cp (* (#__av__^0 /_data * (#__av__^0 /_size)) #__av__^1)
	set (* (#__av__^0 /_size) add (* (#__av__^0 /_size) 1))
)>