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
	?__ 			) );
>
[
		# Call Member Function ( local )
		( $ -> %Obj $ -> FunctionAddr $ -> Args ) -> (void) 
]

_($this $fun $av)<(
	:__push__ ( #this )
	cp ( #this $this )
	cp ( !av $av )
	cp ( !fun $fun )
	call ( * ( #this !fun ) !av )
	:__pop__ ( #this )
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
	:__push__ ( #this )
	cp ( #this #__av__^0 )
	cp ( !av #__av__ )
	call ( * ( !av^1 ) !av^2 )
	:__pop__ ( #this )
)>

[
		# Push node in __stack__
		( $ -> node ) -> (void)
]

__push__($av)<(
	set ( #__stack_it__ add ( set ( !it #__stack_it__ ) 1 ) )
	cp ( # ( /__stack__ !it ) $av )
)>

[
		# Pop node and store it
		( $ -> node ) -> (void)
]

__pop__($av)<(
	set ( #__stack_it__ set ( !it sub ( #__stack_it__ 1 ) ) )
	cp ( $av # ( /__stack__ !it ) )
)>
