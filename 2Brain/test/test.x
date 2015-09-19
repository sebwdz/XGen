MAIN<  
0 (  
	inf ( @WHO 10 :SENSOR )
	sup ( @WHO 9 :ACT )
	inf ( @it 1 add ( @it 1 )
		set ( @IsAct 10 )
	)
	set ( @Attach 0 )
	set ( @CheckAttach 10 )
	inf ( @IsAct 7 set ( @Attach 20 ) )
	sup ( @Attach 0 set ( @CheckAttach 20 ) )
)
>  
  
SENSOR<
0 (  
	set ( @Impulse @RES )  
	set ( @RES 0 )  
	set ( @Base 0 )
)
>  
  
ACT<  
0 (  
	sup ( @Impulse 0  
		set ( @RES )  
		set ( @Impulse 0 )
	)  
	set ( @Base 10 ) 
)  
>  
