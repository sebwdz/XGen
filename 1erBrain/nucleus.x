NUCLEUS_OFF<  
0 (  
	SET ( @IMPULSE 0 )  
	SET ( @WAIT 0 )  
	SET ( @EXEC 0 )  
	SUP ( @EXIT @RES  
		SET ( @MOD 1 )  
		ADD ( @EXIT @PR )  
		SET ( @FU 0 )  
		ADD ( @WAITLNK 1 )  
	)  
	ADD ( @FU 1 )  
	SUP ( @FU 5  
		SUB ( @EXIT 1 )  
		SET ( @FU 0 )  
	)  
)  
>  
  
NUCLEUS_ON<  
0 (  
	INF ( @EXIT 5  
		INF ( @IMPULSE 5  
			SET ( @MOD 0 )  
			SET ( @SLP 20 )  
		)  
	)  
	INF ( @WAIT 1 ADD ( @EXEC 10 ) )  
	SUP ( @WAIT 5  
		SUP ( @EXIT 0  
			SUB ( @EXIT 5 )  
			ADD ( @IMPULSE 5 )  
			SET ( @SKL_CNT 30 )  
		)  
	)  
	ADD ( @WAIT 1 )  
	SUP ( @WAITLNK 3  
		SET ( @WAITLNK 0 )  
		ADD ( @CRTLNK 10 )  
	)  
)  
>  
  
NUCLEUS<  
0 (  
	INF ( @IT 1  
		SET ( @WAIT_DENDR 60 )  
		:NCL_CHAN  
		ADD ( @IT 1 )  
		SET ( @RES 30 )  
		SET ( @PR 40 )  
	)  
	SUP ( @RES 55 ADD ( @NCL_KILL 10 ) )  
	SET ( @NCL_OK 10 )  
	SET ( @NCL_CHAN 10 )  
	SET ( @SKL_CNT 10  )  
	INF ( @MOD 1 :NUCLEUS_OFF )  
	SUP ( @MOD 0 :NUCLEUS_ON )  
	SUP ( @ACTIVE_ACT 0  
		:TO_EXTERN  
	)  
	EGAL ( @ACTIVE_ACT 1 :TO_ACT  SET ( @READY 0 ) )  
	EGAL ( @ACTIVE_ACT 5 :TO_SENS )  
	ADD( @LIFE 1 )  
	SUP ( @LIFE 50  
		SUP ( @READY 20  
			INF ( @CRT_LNK 1  
				CREAT ( :AXON )  
				ADD ( @CRT_LNK 1 )  
			)  
		)  
		SUP ( @IMPULSE 0 ADD ( @READY 1 ) )  
	)  
	ADD ( @LIFE_DENDR 1 )  
	SUP ( @LIFE_DENDR @WAIT_DENDR  
		INF ( @CRT_DENDR 5 ADD ( @CRT_DENDR 1 )  
			CREAT ( :DENDR )  
		)  
		ADD ( @WAIT_DENDR 40 )  
		SET ( @LIFE_DENDR 0 )  
	)  
)  
>  
