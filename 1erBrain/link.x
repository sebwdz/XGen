BASE_DENDR<  
0 (  
	SUP ( @IT 0   
		INF ( @HEAD_LINK 1  
			VAR ( &ATR_HEAD ( PW ( 50 ) ) )  
		)  
		SUP ( @HEAD_LINK 0  
			VAR ( &ATR_HEAD ( PW ( 0 ) ) )  
			SET ( @HEAD_LINK 0 )  
		)  
	)  
	INF ( @IT 1 ADD ( @IT 1 )  
		SET ( @BASE_LINK 20 )  
		:BASE_LINK  
		:BASE_DENDR_CHAN  
		VAR ( &BASE_LINK_ATR ( ACT ( @BASE_LINK @CYTO_CHAN ) ) )  
	)  
	SUP ( @MOVE_IMPULSE 0  
		ADD ( @IMPULSE @MOVE_IMPULSE )  
		SET ( @MOVE_IMPULSE 0 )  
	)  
)  
>  
  
HEAD_DENDR<  
0 (  
	SET ( @HEAD_LINK 20 )  
	INF ( @IT 1 ADD ( @IT 1 )  
		SET ( @HEAD_DENDR 20 )  
		:HEAD_DENDR_CHAN  
	)  
	SUP ( @IMPULSE 0  
		ADD ( @MOVE_IMPULSE @IMPULSE )  
		SET ( @IMPULSE 0 )  
	)  
)  
>  
  
DENDR<  
0 (  
	UNUSE ( @HEAD_LINK @MOVE_IMPULSE )  
	INF ( @IT 1 ADD ( @IT 1 )  
		NEW_HEAD ( :BASE_DENDR )  
		NEW_HEAD ( :HEAD_DENDR )  
	)  
)  
>  