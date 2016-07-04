
Sys|push<(
	cp (#Sys|Stack (len (#Sys|Stack)) * (#__av__^0))
)>

Sys|pop<(
	set (!it sub (len (#Sys|Stack) 1))
	cp (* (#__av__^0) #Sys|Stack (!it))
	erase (#Sys|Stack !it)
)>

Tree($value $tree)<(
	$value $tree
)>

Tree|make<(
	% ((#__av__^0 #__av__^1))
)>

Tree|push<(
	cp (* (#__av__^0 1) (len (* (#__av__^0 1))) #__av__^1)
)>

Tree|show<(
	cp (#Sys|Stack|tmp #__av__)
	call (:Sys|push 0 (% (!)))
	cp (! 0 ({node #Sys|Stack|tmp^0}{fun #Sys|Stack|tmp^1}))
	
	set (!it 0)
	call (* (!fun) 0 (* (!node 0)))
	while (inf ((!it len (* (!node 1))))(
			call (#Tree|show 0 (* (!node 1 !it) !fun))
			incr (!it)
	))
	call (:Sys|pop 0 (% (!)))
)>

showval<(
	echo (#__av__^0 "\n")
)>

test<(
	cp (#Tree|show val (:Tree|show))
	cp (!node % ((10 0 (% ((1 0 (% ((15))))) % ((2))))))
	call (#Tree|show 0 (!node % (val (:showval))))
)>