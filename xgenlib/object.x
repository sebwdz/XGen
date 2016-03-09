[
		# Basic function of objects
]

[
		Obj Call define
]
<
	?c_			call ( #__construct__ 0 ( % (;
	?_			call ( #__obj__ 0 ( % (;
	?.			);
	?:			0;
	?__ 		) );
>
[
		# Call Member Function ( local )
		( $ -> %Obj $ -> FunctionAddr $ -> Args ) -> (void) 
]

_($this $fun $av)<(
	cp ( !av $av )
	cp ( !this $this )
	cp ( !fun $fun )
	call ( #__push__ 0 ( #this ) )
	cp ( #this !this )
	cp ( !res call ( * ( #this !fun ) !av ) )
	cp ( #this call ( #__pop__ ) )
	ret ( !res )
)>

[
		# Call Member Function ( volatil )
		( %Obj FunctionAddr Args ) -> (void)
]

__obj_call__<(
	:_ ( #__av__^0 #__av__^1 #__av__^2 )
)>

[
		# Construct New Obj
		( %Obj %Constructor Args ) -> (void)
]

__construct__<(
	cp ( !av #__av__ )
	call ( #__push__ 0 ( #this ) )
	cp ( #this !av^0 )
	call ( * ( !av^1 ) !av^2 )
	cp ( #this call ( #__pop__ ) )
)>

[
		# Push node in __stack__
		( $ -> node ) -> (void)
]

__push__<(
	set ( #__stack_it__ add ( set ( !it #__stack_it__ ) 1 ) )
	cp ( #__stack__ ( !it ) #__av__^0 )
)>

[
		# Pop node and get
		( $ -> node ) -> (void)
]

__pop__<(
	set ( #__stack_it__ set ( !it sub ( #__stack_it__ 1 ) ) )
	ret ( #__stack__ ( !it ) )
)>