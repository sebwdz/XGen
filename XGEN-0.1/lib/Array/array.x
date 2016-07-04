
[
	Array class
]

libArray<(
	{__name__ /Arrayl}
	{construct (:Array|construct)}
	{push_back (:Array|push_back)}
	{pop_back (:Array|pop_back)}
	{insert (:Array|insert)}
	{erase (:Array|erase)}
	{append (:Array|append)}
	{clear (:Array|clear)}
	{set (:Array|set)}
	{set_obj (:Array|set_obj)}
	{for_each (:Array|for_each)}
	{find_first (:Array|find_first)}
	{find_last (:Array|find_last)}
	{compare (:Array|compare)}
	{data (:Array|data)}
	{at (:Array|at)}
	{size (:Array|size)}
)>

Array|construct<( ?this
	cp (* (!prv /data) * (#__av__^0))
	set (* (!prv /size) len (* (#__av__^0)))
)>

Array|push_back<( ?this
	cp (* (!prv /data * (!prv /size)) #__av__^0)
	incr (* (!prv /size))
)>

Array|pop_back<( ?this
	decr (* (!prv /size))
	erase (* (!prv /data) * (!prv /size))
)>

Array|insert<( ?this
	cp (!data 0)
	incr (* (!prv /size))
	set (!it 0)
	set (!x 0)
	while (inf ((!x * (!prv /size)))(
			egal ((!x #__av__^0)(
					cp (!tmp (!x) #__av__^1)
				)(
					cp (!tmp (!x) * (!prv /data !it))
					incr (!it)
			))
			incr (!x)
	))
	cp (* (!prv /data) !tmp)
)>

Array|erase<( ?this
	decr (* (!prv /size))
	sup ((* (!prv /obj) 0)(cp (* (* (!prv /data #__av__^0)) 0)))
	erase (* (!prv /data) #__av__^0)
)>

Array|append<( ?this
	set (!x 0)
	set (!it * (!prv /size))
	while (inf ((!x len (* (#__av__^0))))(
			cp (* (!prv /data !it) * (#__av__^0 !x))
			incr (!it)
			incr (!x)
	))
)>

Array|clear<( ?this
	sup ((* (!prv /obj) 0)(
			while (sup ((* (!prv /size) 0))(
					call (* (!this /erase) 0 (0))
			))
		)(
			cp (* (!prv) 0)
	))
)>

Array|set<( ?this
	cp (* (!prv /data) * (#__av__^0))
	set (* (!prv /size) len (* (#__av__^0)))
)>

Array|set_obj<( ?this
	cp (* (!prv /obj) #__av__^0)
)>

Array|for_each<( ?this ?av_s
	set  (!x 0)
	while (inf ((!x * (!prv /size)))(
			call (!__av__^0 0 (* (!prv /data !x)))
			incr (!x)
	))
)>

Array|find_first<( ?this ?av_s
	set (!x 0)
	while (inf ((!x * (!prv /size)))(
			egal ((call (* (!__av__^1) 0 (
				* (!prv /data !x) !__av__^0)) 1)(ret (!x)))
			incr (!x)
	))
	ret (-1)
)>

Array|find_last<( ?this ?av_s
	set (!x 0)
	set (!r -1)
	while (inf ((!x * (!prv /size)))(
			egal ((call (* (!__av__^1) 0 (
				* (!prv /data !x) !__av__^0)) 1)(set (!r !x)))
			incr (!x)
	))
	ret (!r)
)>

Array|compare<( ?this ?av_s
	set (!it 0)
	no ((egal ((* (!prv /size) len (* (!__av__^0)))))(ret (1)))
	while (inf ((!it * (!prv /size)))(
			egal ((
					call (* (!__av__^1) 0 (
						* (!prv /data !it) * (!__av__^0 !it)))
					1
				)(
					ret (1)
			))
			incr (!it)
	))
	ret (0)
)>

Array|data<( ?this
	% (* (!prv /data))
)>

Array|at<( ?this
	* (!prv /data #__av__^0)
)>	

Array|size<( ?this
	* (!prv /size)
)>