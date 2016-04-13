
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

[Bytes code]
<
	[]
	!it
	!len
	#lst
>

[ real  ]
set !it 9
len #lst /tmp
set !len /tmp
while:
jmp %:end
	get_chan #lst !it /tmp
	echo /tmp
	incr !it
	jmp %:while
:end

[ .. ]

set !it 0
len #lst !len
inf !it !len
jmp %:end
	get_chan #lst !it [t]0
	echo [t]0
	incr !it !it
:end

[ => ]

set [l]0 0
len [l]2 [l]1
while:
inf [l]0 [l]1
jmp %:end
	get_chan [l]2 [l]0 [t]0
	echo [t]0
	incr [l]0 1
	jmp %:while
:end

[i] = 1o
[l] = 1o
[v] = 4o
[t] = 1o
[][][][] = 1o

[ => ]

[i]0[l]0[v]0
[i]1[l]2[l]1
[i]2[l]0[l]1
[i]6[v]%:end
[i]3[l]0[t]0
[i]4[t]0
[i]5[l]0[v]1
[i]6[v]%:while

[ => ]

0[l][v][][]0 0	=> 7
1[l][l][][]2 1	=> 4
2[l][l][][]0 1	=> 4
6[v][][][]26	=> 6
3[l][t][][]0 0	=> 4
4[t][][][]0		=> 3
5[l][v][][]0 1	=> 7
6[v][][][]-24	=> 6

=> 41o

sort_lst<(
	set (!mv 1)
	set (!len len (#lst))
	while (egal ((!mv 1))(
			set (!mv 0)
			set (!it 1)
			while (inf ((!it !len))(
					set (!prev sub (!it 1))
					sup ((#lst (!it) #lst (!prev))(
							set (!tmp #lst (!it))
							set (#lst (!it) #lst (!prev))
							set (#lst (!prev !tmp)
							set (!mv 1)
					))
					incr (!it 1)
			))
	))
)>X

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