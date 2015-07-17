
Axon_Head<
0 (
	set ( @LinkGrow 10 )
	set ( @AxonHead 10 )
	inf ( @headit
		use ( @headit )
		use ( @AxonHead @LinkGrow )
		:Axon_Head_Chan
	)
	sup ( @moveImpuse 0 add ( @Impulse @moveImpulse )
		set ( @moveImpulse 0 ) )
	sup ( @Impulse 20 set ( @Impulse 20 ) )
	set ( @AxonImpulse @Impulse )
)
>


AXON_HEAD<
0 (  
	SET ( @LINK_GROW 10 )  
	SET ( @AXON_HEAD 10 )  
	INF ( @IT_HEAD 1 ADD ( @IT_HEAD 1 )  
		:AXONE_HEAD_CHAN  
	)  
	SUP ( @MOVE_IMPULSE 0  
		ADD ( @IMPULSE @MOVE_IMPULSE )  
		SET ( @MOVE_IMPULSE 0 )  
	)  
	SUP ( @IMPULSE 20 SET ( @IMPULSE 20 ) )  
	SET ( @AXON_IMPULSE @IMPULSE )  
)  
>  
  
IMPULSE_BASE_AXON<  
0 (  
	INF ( @IT_AXON 1 ADD ( @IT_AXON 1 )  
		:BASE_IMPULSE_AXON  
	)  
	SUP ( @IMPULSE 0  
		ADD ( @MOVE_IMPULSE @IMPULSE )  
		SET ( @IMPULSE 0 )  
	)  
)  
>  
  
BASE_LINK_AXON< 
0 (  
	SET ( @LINK_GROW 10 )  
	SET ( @BASE_LINK 20 )  
	INF ( @IT_GROW 1 ADD ( @IT_GROW 1 )  
		:BASE_LINK  
		VAR ( &LINK_UP ( DST ( 80 ) ) )  
	)  
	:IMPULSE_BASE_AXON  
)  
>  
  
AXON<  
0 (  
	UNUSE ( @LINK_GROW @MOVE_IMPULSE )  
	SET ( @AXON 40 )  
	INF ( @IT 1 ADD ( @IT 1 )  
		NEW_HEAD ( :BASE_LINK_AXON )  
		NEW_HEAD ( :AXON_HEAD )  
	)  
)  
>  
