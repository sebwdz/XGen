
[
	Exemple utilisation des blocs
	Utilisation des arguments, porté des variables local
]

Block1<(
	echo ("I'm block1\n")
)>

Block2<(
	echo ("I'm block2\n")
)>

Block3($av1 $av2)<(
	echo ($av1) $av2
)>

data<(
	echo ("hihi\n")
)>

test<(
	{AA 10}
	set (!tmp 12)
	cp (!y 0 ({_dodo (14 15 ({a !tmp}))}))
	echo (1 (!y^_dodo) "\n")
	echo (!y^_dodo^a "\n")
	echo (!y^0^1 "\n")
	cp (!data :data)
	call (!data)
[
	cp (!x 0 (!w !z))
	cp (!x { w 2 ("salut"); z 2 ("salut") })
	echo (!x^w " " !x^z "\n")
	cp (!x { w !w ; z !z })
	echo (!x^w " " !x^z "\n")
]
	[ 2 ("str") => specifie à echo que c'est à afficher en tant que string ]
	ret (0)
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