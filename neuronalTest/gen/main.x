
main<(
	nil (
		?Init
			set (@Sens 1)
			set (@Output 1)
			set (@WithoutAxon 1)
			share (/Sens /Output /WithoutAxon)
			set (@son 1)
			attach ((:Nucleus))
			sup ((@Impulse 0)(echo ("Impulse\n")))
		?ie__
	)
	nil (
		sup ((incr (!time 1) 50)(
				set (!time 1)
				incr (@Impulse 1)
		))
		?Init
			set (@Sens 1)
			set (@Input 1)
			set (@WithoutDendrite 1)
			share (/Sens /Input /WithoutDendrite)
			set (@son 1)
			attach ((:Nucleus))
		?ie__
	)
)>
