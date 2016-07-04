
sort_list<(
	cp (!list #__av__^0)
	set (!move 1)
	while (egal ((!move 1))(
			set (!move 0)
			cp (!tmp !list)
			cp (!prev 0)
			while (sup ((!tmp 0))(
					sup ((!prev 0)(
							sup ((* (!prev 0) * (!tmp 0))(
									set (!x * (!prev 0))
									set (* (!prev 0) * (!tmp 0))
									set (* (!tmp 0) !x)
									set (!move 1)
							))
					))
					cp (!tmp * (cp (!prev !tmp) 1))
			))
	))
)>

rev_list<(
	cp (!tmp #__av__^0)
	cp (!res 0)
	while (sup ((!tmp 0))(
			cp (!res % ((* (!tmp 0) !res)))
			cp (!tmp * (!tmp 1))
	))
	ret (!res)
)>

show_list<(
	cp (!tmp #__av__^0)
	while (sup ((!tmp 0))(
		no ((egal ((!tmp #__av__^0)))(echo (" -> ")))
		echo (* (!tmp 0))
		cp (!tmp * (!tmp 1))
	))
	echo ("\n")
)>

len_list<(
	cp (!tmp #__av__^0)
	set (!len 0)
	while (sup ((!tmp 0))(
			set (!len add (!len 1))
			cp (!tmp * (!tmp 1))
	))
	ret (!len)
)>

concat_list<(
	cp (!tmp #__av__^0)
	while (sup ((!tmp 0))(
			egal ((* (!tmp 1) 0)(
					cp (* (!tmp 1) #__av__^1)
					ret (0)
			))
			cp (!tmp * (!tmp 1))
	))
)>

test<(
	cp (!liste % ((3 % ((2 % ((0 % ((1 % ((5 % ((4)))))))))))))
	cp (!liste2 % ((8 % ((12 % ((-5)))))))
	[ Push Front ]
	cp (!liste % ((10 !liste)))
	echo ("liste 1\t\t = \t") call (:show_list 0 (!liste))
	echo ("liste 2\t\t = \t") call (:show_list 0 (!liste2))
	call (:concat_list 0 (!liste !liste2))
	echo ("result\t\t = \t") call (:show_list 0 (!liste))
	[ Pop Front ]
	cp (!liste * (!liste 1))
	echo ("after pop\t = \t") call (:show_list 0 (!liste))
	[ Sort list ]
	call (:sort_list 0 (!liste))
	echo ("sorted list\t = \t") call (:show_list 0 (!liste))
	cp (!liste2 call (:rev_list 0 (!liste)))
	echo ("rev list\t = \t") call (:show_list 0 (!liste2))
	ret (0)
)>
