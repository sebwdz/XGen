
ecosystem<(
	set (@EcoCentre 10)
	sup ((@Elm 0)(
			creat ((@Elm^0))
			cp (@Elm 0)
	))
)>

send|exec<(
	sup ((* (#__oth__ /EcoCentre) 0)(
			echo (* (#this /_what) "\n")
			cp (* (#__oth__ /Elm) 1 (* (#this /_obj)))
	))
)>

sendfood<(
	:Init ((
		cp (&SendFood^_what 2 ("New food!"))
		cp (&SendFood^_obj :cell)
		cp (&SendFood^_exec :send|exec)
		cp (&SendFood^_param 0 (0 0 ?scope (?network) ?manual ?limit (1)))
	))
	sup ((set (!time add (!time 1)) 72)(
			set (&SendFood^_param^?limit^0 1)
			set (!time 0)
	)(set (&SendFood^_param^?limit^0 0)))
)>

sendsnake<(
	:Init ((
		cp (&SendSnake^_what 2 ("New Snake!"))
		cp (&SendSnake^_obj :Snake)
		cp (&SendSnake^_exec :send|exec)
		cp (&SendSnake^_param 0 (0 0 ?scope (?network) ?manual ?limit (1)))
	))
	sup ((set (!time add (!time 1)) 1989)(
			set (&SendSnake^_param^?limit^0 1)
			set (!time 0)
	)(set (&SendSnake^_param^?limit^0 0)))
)>