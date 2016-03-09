
List|Init<(
	cp (#List|Length :List|GetLen)
	cp (#List|Sort :List|Sort)
	cp (#List|Insert :List|Insert)
	cp (#List|PushBack :List|PushBack)
	cp (#List|PushFront :List|PushFront)
	cp (#List|Erase :List|Erase)
	cp (#List|PopBack :List|PopBack)
	cp (#List|PopFront :List|PopFront)
	cp (#List|ForEach :List|ForEach)
)>

[
	get len of list
	(% ((x % (...))))	-> (float)
]

List|GetLen<(
	set (!len 0)
	cp (!item #__av__^0)
	while (sup ((!item 0))(
					set (!len add (!len 1 ))
					cp (!item * (!item 1))
	))
	ret (!len)
)>

[
	sort liste
	( %function % ((x % (...)) -> ()
]

List|Sort<(
	cp (!lst #__av__^0)
	cp (!f #__av__^1)
	set (!move 1)
	while (egal ((!move 1))(
			set (!move 0)
			cp (!prev 0)
			cp (!it !lst)
			while (sup ((!it 0))(
					sup ((!prev 0)(
							egal ((call (* (!f) (* (!it 0) * (!prev 0))) 1)(
									cp (!tmp * (!it 0))
									cp (* (!it 0) * (!prev 0))
									cp (* (!prev 0) !tmp)
									set (!move 1)
							))
					))
					cp (!prev !it)
					cp (!it * (!it 1))
			))
	))
)>

[
	insert elm in list
	(% ((x % (...))) % ((x % (...))) (...))	-> ()
]

List|Insert<(
	cp (!item % ((#__av__^2)))
	sup ((#__av__^1 0)(
			cp (* (!item 1) * (#__av__^1 1))
			cp (* (#__av__^1 1) !item)
		)(
			sup ((#__av__^0 0)(
					cp (* (!item 1) #__av__^0)
			))
			ret (!item)
	))
	ret (#__av__^0)
)>

List|PushFront<(
	ret (cp (!item % ((#__av__^1 #__av__^0))))
)>

List|PushBack<(
	cp (!it #__av__^0)
	cp (!item % ((#__av__^1)))
	cp (!prev 0)
	while (sup ((!it 0))(
		cp (!prev !it)
		cp (!it * (!it 1))
	))
	sup ((!prev 0)(
		cp (* (!prev 1) !item)
	)(ret (!item)))
	ret (#__av__^0)
)>

List|Erase<(
	cp (!it #__av__^0)
	cp (!prev 0)
	while (no ((egal ((!it #__av__^1))))(
		cp (!prev !it)
		cp (!it * (!it 1))
	))
	sup ((!prev 0)(
			cp (* (!prev 1) * (#__av__^1 1))
		)(
			ret (* (#__av__^0 1))
	))
	ret (#__av__^0)
)>

List|PopFront<(
	ret (* (#__av__^0 1))
)>

List|PopBack<(
	cp (!it #__av__^0)
	cp (!prev 0)
	while (and ((sup ((!it 0)) sup ((* (!it 1) 0))))(
		cp (!prev !it)
		cp (!it * (!it 1))
	))
	sup ((!prev 0)(
			cp (* (!prev 1) 0)
	)(ret (!prev)))
	ret (#__av__^0)
)>

List|ForEach<(
	cp (!av #__av__)
	cp (!tmp #__av__^0)
	while (sup ((!tmp 0))(
		 	call (* (!av^1) 0 (% (* (!tmp 0))))
		 	cp (!tmp * (!tmp 1))
	))
)>