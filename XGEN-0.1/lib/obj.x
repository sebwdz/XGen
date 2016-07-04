
[
	tools for POO concept
]

<
	?l 			) nil (cp (!tmp ;
	?le 		) cp_one (!tmp^this^1 !this)
				cp_one (!tmp^private^1 !prv) !tmp));
	?this		{this cp_one (!this 10)}{private cp_one (!prv 10)};
	?av_s		cp (!__av__ #__av__);
	?class 		cp (!this #__av__^0) cp (!prv #__av__^1);
	?eclass 	!this;
	?m 			cp (* (!this;
	?at 		cp (* (!prv;
	?_			);
	?inhb		call (;
	?inhc		0 (!this !prv)) cp (* (!this;
	?pl 		?l :obj_call (;
	?ple		) ?le;
>

obj_call($code)<( ?this
	$code (#__av__)
)>

new<( ?av_s
	cp (!this % (0))
	cp (!prv % (0))
	call (* (!__av__^0) 0 (!this !prv))
	call (* (!this /construct) !__av__^1)
	ret (!this)
)>

[
	example class:
	
	define class test
	test|construct<( ?this
		cp (* (!prv /_text) "salut")
	)>

	test|hello<( ?this
		echo (* (!prv /_text) "\n")
	)>

	test<(
		?class
			?m /hello ?l :test|hello ?le
			?m /construct ?l :test|construct ?le
		?eclass
	)>

	example inherit :

	test2|hello<( ?this
		echo ("inherit => ")
		call (* (!this /__obj__ /hello))
	)>

	obj2<(
		?class
			?inhb :obj ?inhc /__obj__ ?_ * (!this) ?_
			?m /hello ?l :obj2|hello ?le
		?eclass
	)>

	usage :

	cp (#new|test % (:obj2))
	cp (!obj call (:new 0 (#new|test 0 (("salut")))))
	call (* (!obj /hello))

]