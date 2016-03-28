
Synapse|new<(
	set (!weight div (sub (mod (rand 100) 50) 100))
	set (!weight 10)
	cp (!res % (0 (#__av__^0 !weight #__av__^1)))
	ret (!res)
)>

[ (to ) (What) (weight) ]

Synapse|SendTo<(
	cp (!to % (* (#__av__^0 #__av__^2)))
	set (* (!to) add (* (!to) mult (#__av__^3 @ (#__av__^1))))
)>