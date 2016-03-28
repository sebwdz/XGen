
[
	Exemple utilisation des modules et interactions
]

execRplsOth<(
)>

cleanRpls<(
)>

Module<(
	:Init ((
			cp (&Rpls^_exec :execRplsOth)
			cp (&Rpls^_clean :cleanRpls)
			cp (&Rpls^_param 0 (20 0 ?scope (?oth) ?manual ?limit (1)))
	))
)>

main<(
	inf ((set (!t add (!t 1)) 10)(
			creat (:Module)
	))
)>