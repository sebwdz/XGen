
make_list<(
	cp (#lst 0)
	set (!it 0)
	while (inf ((!it 5000))(
			set (#lst (!it) mod (rand 200000))
			incr (!it 1)
	))
)>


put_list<(
	set (!it 0)
	set (!len len (#lst))
	while (inf ((!it !len))(
		echo (#lst (!it) "\n")
		incr (!it 1)
	))
)>

sort_lst<(
	set (!mv 1)
	set (!len len (#lst))
	while (egal ((!mv 1))(
			set (!mv 0)
			set (!it 1)
			while (inf ((!it !len))(
					sup ((#lst (!it) #lst (sub (!it 1)))(
							set (!tmp #lst (!it))
							set (#lst (!it) #lst (sub (!it 1)))
							set (#lst (sub (!it 1)) !tmp)
							set (!mv 1)
					))
					incr (!it 1)
			))
	))
)>

fun<(
	decr (!it 15)
)>

Empty<(
)>

test<(
	cp (#fun :Empty)
	cp (#fun^0 val (echo ("Salut\n")))
	cp (#fun^1 val (echo ("Ouai!\n")))
	call (#fun)
	cp (#fun^0 val (echo ("NONO ")))
	cp (!x val(set))
	call (#fun)

	cp (!x % (!a))
	set (* (!x) 10)
	:make_list
	:sort_lst
	:put_list
	[
	cp (#fun :fun)
	call (#fun)
	echo (@Ok "\n")

	cp (#fun^0^0 val (@Ok))
	set (#fun^0^1 10)
	call (#fun)
	echo (@Ok "\n")
	cp_one (#fun^0 val (set))
	call (#fun)
	echo (@Ok "\n")
[
	set (!x (+ 10 (- 20 10)))
	while (inf ((!it 10))(
			cp (!x 0)
			cp (!x^10 0)
			echo (% (! (/x 10)) "\n")
			cp (!a^11 10)
			echo ("....\n")
			incr (!it)
	))
]
)>