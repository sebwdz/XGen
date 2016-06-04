
[
	cal a sigmoide function
]
Math|Sigmoide<(
	set (!tmp pow (2.71828 sub (0 #__av__^0)))
	ret (div (1 add (!tmp 1)))
)>

[
	make vct by two position
]

get_vct<(
	set (!vct^0 sub (* (#__av__^0 0) * (#__av__^1 0)))
	set (!vct^1 sub (* (#__av__^0 1) * (#__av__^1 1)))
	ret (!vct)
)>

[
	get vct with len
]

get_full_vct<(
	cp (!av #__av__)
	cp (!vct call (:get_vct 0 (!av^0 !av^1)))
	cp (!vct^2 sqrt (add (mult (!vct^0 !vct^0) mult (!vct^1 !vct^1))))
	ret (!vct)
)>

[
	add two vct
]

add_vct<( 
	[<
		?vct2 #__av__^0
		?vct2 #__av__^1
	>]
	cp (!pos #__av__^0)
	set (* (!pos 0) add (* (!pos 0) #__av__^1^0))
	set (* (!pos 1) add (* (!pos 1) #__av__^1^1))
)>