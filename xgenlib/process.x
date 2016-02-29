
Process|New_Process<(
	:Init ( ( shared ( /__shared_pid__ /__pid__ ) ) )
	set ( @__shared_pid__ add ( rand 1 ) )
	detach ( 0 ( * ( #__av__^0 ) ) )
)>

Process|Init<(
	:Init ( (
			sup ( ( @__pid__ 0 ) (
					cp ( @__parent__ @__pid__ )
					cp ( @__pid__ @__shared_pid__ )
				) ( set ( @__pid__ add ( rand 1 ) ) ) 
			)
	) )
)>
