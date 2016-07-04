
[
	double linked List
	lnk => 0 (prev next content)
]

LinkList<(
	{__name__ /linkListl}
	{construct (:linkList|construct)}
	{push_back (:linkList|push_back)}
	{push_front (:linkList|push_front)}
	{insert (:linkList|insert)}
	{pop_back (:linkList|pop_back)}
	{pop_front (:linkList|pop_front)}
	{concat (:linkList|concat)}
	{erase (:linkList|erase)}
	{clear (:linkList|clear)}
	{set_obj (:linkList|set_obj)}
	{for_each (:linkList|for_each)}
	{begin (:linkList|begin)}
	{end (:linkList|end)}
	{size (:linkList|size)}
)>

linkList|construct<( ?this
	cp (* (!prv /begin) 0)
	cp (* (!prv /end) 0)
	cp (* (!prv /size 0))
)>

linkList|push_back<( ?this ?av_s
	call (* (!this /insert) 0 (* (!prv /end) !__av__^0))
)>

linkList|push_front<( ?this ?av_s
	call (* (!this /insert) 0 (0 !__av__^0))
)>

linkList|insert<( ?this
	cp (!tmp % ((#__av__^0 * (#__av__^0 1) #__av__^1)))
	egal ((#__av__^0 0)(
			cp (* (!tmp 1) * (!prv /begin))
			cp (* (* (!prv /begin) 0) !tmp)
			cp (* (!prv /begin) !tmp)
		)(
			cp (* (* (!tmp 0) 1) !tmp)
			cp (* (* (!tmp 1) 0) !tmp) 
	))
	egal ((* (!prv /end) #__av__^0)(cp (* (!prv /end) !tmp)))
	incr (* (!prv /size))
)>

linkList|pop_back<( ?this
	call (* (!this /erase) 0 (* (!prv /end)))
)>

linkList|pop_front<( ?this
	call (* (!this /erase) 0 (* (!prv /begin)))
)>

linkList|concat<( ?this
	cp (!tmp * (#__av__^0 /begin))
	while (sup ((!tmp 0))(
			call (* (!this /insert) * (!tmp 2))
			cp (!tmp * (!tmp 1))
	))
)>

linkList|erase<( ?this
	cp (!tmp #__av__^0)
	decr (* (!prv /size))
	cp (* (* (!tmp 0) 1) * (!tmp 1))
	cp (* (* (!tmp 1) 0) * (!tmp 0))
	egal ((!tmp * (!prv /begin))(cp (* (!prv /begin) * (!tmp 1))))
	egal ((!tmp * (!prv /end))(cp (* (!prv /end) * (!tmp 0))))
)>

linkList|clear<( ?this
	cp (!tmp * (!prv /begin))
	while (no ((egal ((!tmp 0))))(
			cp (!next * (!tmp 1))
			sup ((* (!prv /obj) 0)(cp (* (* (!tmp 2)) 0)))
			cp (* (!tmp) 0)
			cp (!tmp !next)
	))
	cp (* (!prv /begin) 0)
	cp (* (!prv /end) 0)
	cp (* (!prv /size) 0)
)>

linkList|set_obj<( ?this
	cp (* (!prv /obj) #__av__^0)
)>

linkList|for_each<( ?this ?av_s
	cp (!tmp * (!prv /begin))
	while (no ((egal ((!tmp 0))))(
			cp (!next * (!tmp 1))
			call (* (!__av__^0) 0 (* (!tmp 2)))
			cp (!tmp !next)
	))
)>

linkList|begin<( ?this
	* (!prv /begin)
)>

linkList|end<( ?this
	* (!prv /end)
)>

linkList|size<( ?this
	* (!prv /size)
)>