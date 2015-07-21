MAIN<  
0 (  
	INF ( @WHO 10 :SENSOR )
	SUP ( @WHO 9 :ACT )
	INF ( @it 1 ADD ( @it 1 )
		SET ( @IsAct 10 )
	)
	SET ( @Attach 0 )
	SET ( @CheckAttach 10 )
	INF ( @IsAct 7 SET ( @Attach 20 ) )
	SUP ( @Attach 0 SET ( @CheckAttach 20 ) )
)
>  
  
SENSOR<
0 (  
	SET( @Impulse @RES )  
	SET ( @RES 0 )  
	SET ( @Base 0 )
)
>  
  
ACT<  
0 (  
	SUP ( @Impulse 0  
		SET ( @RES )  
		SET ( @Impulse 0 )
	)  
	SET ( @Base 10 ) 
)  
>  
