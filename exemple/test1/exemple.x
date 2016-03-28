
[
	Exemple utilisation des blocs
	Utilisation des arguments, porté des variables local
]

Block1<(
	echo ("I'm block1\n")
)>

	echo ("I'm block2\n")
)>

Block3($av1 $av2)<(
	echo ($av1) $av2
)>

test<(
	[ 2 ("str") => specifie à echo que c'est à afficher en tant que string ]
	echo ("Block1 :\n")
	:Block3 (2 ("Who I am ?\n") :Block1)
	echo ("Block2 :\n")
	:Block3 (2 ("Who I am ?\n") :Block2)

	cp (!str 2 ("Local str"))
	cp (#str 2 ("Gloabl str"))
	:Block3 (!str echo (" => Ne fonctionne pas !\n")) [ chaque ! est local au block ]
	:Block3 (#str echo (" => fonctionne!\n")) [ chaque # est local au descriptor ]
	ret (0)		[ ne s'execute qu'une seul fois ]
)>