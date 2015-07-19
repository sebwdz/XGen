MAIN<  
0 (  
	INF ( @WHO 10 :SENSOR )
	SUP ( @WHO 9 :ACT )
	INF ( @IT 1 ADD ( @IT 1 )
		SET ( @IS_ACT 10 )
		var (
			&Rpls (
				type ( mv oth rpls )
				act ( @IMACT @IMACT )
				dst ( 40 )
				pw ( 40 )
			)
		)
		SET ( @IMACT 20 )
	)
	SET ( @ATTACH 0 )
	SET ( @CHECK_ATTACH 10 )
	INF ( @IS_ACT 7 SET ( @ATTACH 20 ) )
	SUP ( @ATTACH 0 SET ( @CHECK_ATTACH 20 ) )
)
>  
  
SENSOR<
0 (  
	SET( @IMPULSE @RES )  
	SET ( @RES 0 )  
	SET ( @BASE 0 )
)
>  
  
ACT<  
0 (  
	SUP ( @GOOD 0  
		ADD ( @ATR @GOOD )  
		SET ( @GOOD 0 )  
	)  
	SUP ( @IMPULSE 0  
		SET ( @RES @IMPULSE )  
		SET ( @IMPULSE 0 )  
	)  
	SET ( @BASE 10 ) 
)  
>  
