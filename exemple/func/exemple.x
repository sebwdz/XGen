
test<(
	cp (!y 0 ("pas y!"))
	cp (!x nil (
		sup ((!y 0)(
				val (2 ("y!")))
		(!y))
	))
	echo (!x "\n")
)>