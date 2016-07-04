
[
	string class
]

libString<(
	{__name__ /Stringl}
	{substr (:String|substr)}
	{find (:String|find)}
	{find_first (:String|find_first)}
	{find_last (:String|find_last)}
	{find_first_not (:String|find_first_not)}
	{find_last_not (:String|find_last_not)}
	{compare (:String|compare)}
	{ncompare (:String|ncompare)}
)>

String|substr<( ?this
	cp (!res % (0))
	set (!it #__av__^0)

	egal ((#__av__^1 0)(
			set (!len * (!prv /size))
		)(
			set (!len add (#__av__^0 #__av__^1))
	))
	set (!x 0)
	while (inf ((!it !len))(
			cp (* (!res !x) * (!prv /data !it))
			incr (!x) incr (!it)
	))
	ret (!res)
)>

String|find<( ?this
	set (!x 0)
	set (!it 0)
	while (inf ((!it * (!prv /size)))(
			egal ((* (!prv /data !it) * (#__av__^0 !x))(
					incr (!x)
				)(
					set (!x 0)
			))
			egal ((!x len (* (#__av__^0)))(ret (sub (!it sub (!x 1)))))
			incr (!it)
	))
	ret (-1)
)>

String|find_first<( ?this ?av_s
	call (* (!this /__array__ /find_first) 0 (
			!__av__^0 * (!prv /find_str)
	))
)>

String|find_last<( ?this ?av_s
	call (* (!this /__array__ /find_last) 0 (
			!__av__^0 * (!prv /find_str)
	))
)>

String|find_first_not<(?this ?av_s
	set (!it 0)
	while (inf ((!it * (!prv /size)))(
			no ((egal ((call (* (* (!prv /find_str)) 0 
				(* (!prv /data !it) !__av__^0)) 1)))(ret (!it)))
			incr (!it)
	))
	ret (-1)
)>

String|find_last_not<(?this ?av_s
	set (!it 0)
	set (!res -1)
	while (inf ((!it * (!prv /size)))(
			no ((egal ((call (* (* (!prv /find_str)) 0 
				(* (!prv /data !it) !__av__^0)) 1)))(set (!res !it)))
			incr (!it)
	))
	ret (!res)
)>

String|compare<( ?this ?av_s
	call (* (!this /__array__ /compare) 0 (
			!__av__^0
			val ((egal ((#__av__^0 #__av__^1)(ret (0))(ret (1)))))
	))
)>

String|ncompare<( ?this ?av_s
	set (!it 0)
	while (inf ((!it !__av__^1))(
			no ((egal ((* (!prv /data !it) * (!__av__^0 !it))))(ret (1)))
			incr (!it)
	))
	ret (0)
)>