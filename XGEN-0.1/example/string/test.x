
pushthis<(
	cp (#Obj|this % ((#this #Obj|this)))
)>

popthis<(
	cp (#this * (#Obj|this 0))
	cp (#Obj|this * (#Obj|this 1))
)>

obj_call<(
	cp (!tmp #__av__)
	no ((egal ((#this !tmp^0)))(
			:pushthis
			cp (#this !tmp^0)
			set (!push 1)
	)(set (!push 0)))
	cp (!res call (* (#this !tmp^1) !tmp^1))
	sup ((!push 0)(:popthis))
	ret (!res)
)>

Sys|new<(
	cp (#Obj|this % ((#this #Obj|this)))
	cp (!tmp #__av__)
	cp (#this cp (!this % (0)))
	call (#__mod__ (!tmp^0 /new) !tmp^1)
	cp (#this * (#Obj|this 0))
	cp (#Obj|this * (#Obj|this 1))
	ret (!this)
)>

<
	?.		call (:obj_call 0; 
	?_.		);

	?alloc 	0; [ correction cp (/av (#var)) => fonctionne pas ]
	?new 	% (#__mod__) ?alloc;
>

String|split<(
	cp (!res % (0))
	cp (!tmp % (2))
	set (!it 0)
	while (inf ((!it len (* (#this /_data))))(
			egal ((* (#this /_data !it) " ")(
					sup ((len (* (!tmp)) 0)(
							cp (* (!res len (* (!res))) !tmp)
							cp (!tmp % (2))
					))
				)(
					set (* (!tmp len (* (!tmp))) * (#this /_data !it))
			))
			incr (!it)
	))
	sup ((len (* (!tmp)) 0)(cp (* (!res len (* (!res))) !tmp)))
	ret (!res)
)>

String|upper<(
	set (!it 0)
	while (inf ((!it len (* (#this /_data))))(
			and ((
					sup ((* (#this /_data !it) sub ("a" 1)))
					inf ((* (#this /_data !it) add ("z" 1)))
				)(
					decr (* (#this /_data !it) sub ("a" "A"))
			))
			incr (!it)
	))
	ret (!str)
)>

String|display<(
	echo (* (#this /_data))
)>

String<(
	cp (* (#this) 0 (
			{display :String|display}
			{split :String|split}
			{upper :String|upper}
			{_data set (#__av__^0 2)}
			{_size len (#__av__^0)}
	))
)>

test<(
	:test_1
)>

test_1<(
	cp (#__mod__ (?alloc) :Sys|new)
	cp (#__mod__ (/String /new) :String)
	cp (!str ?.(?new (/String 0 (#str_av^0)))?_.)
	set (!xxx 0)

	[:pushthis]
	cp (#this !str)
	?.(!str /upper)?_.
	cp (!strs ?.(!str /split)?_.)
	set (!it 0)
	while (inf ((!it len (* (!strs))))(
			echo ("> " * (* (!strs !it)) "\n")
			incr (!it)
	))
	[:popthis]
)>

test_3<(
	cp (#__mod__ (?alloc) :Sys|new)
	cp (#__mod__ (/String /new) :String)
	cp (!str ?.(?new (/String 0 (#str_av^0)))?_.)
	set (!xxx 0)

	:pushthis
	cp (#this !str)
	call (* (#this /upper))
	cp (!strs call (* (#this /split)))
	set (!it 0)
	while (inf ((!it len (* (!strs))))(
			echo ("> " * (* (!strs !it)) "\n")
			incr (!it)
	))
	:popthis
)>

test_2<(
	cp (#this % (2))
	cp (* (#this /_data) #str_av^0)

	set (!xxx 0)
	call (:String|upper)
	cp (!strs call (:String|split))
	set (!it 0)
	while (inf ((!it len (* (!strs))))(
			echo (">" * (* (!strs !it)) "\n")
			incr (!it)
	))
)>