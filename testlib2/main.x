MAIN<(
	 inf ( ( #canDuplic 1 ) (
			:Cycle ( #crt1 #time1 new_head ( :Cytosol ) 1 4 )
			:Cycle ( #crt3 #time3 new_head ( :Nucleus_Move ) 2 1 )
			:Cycle ( #kill #timex kill 1400 1 )
		)
	)
	:Init ( #init 0 (
			inf ( ( @S_Duplic 1 ) (
					shared ( @S_Duplic )
					set ( @S_Duplic 1 )
					set ( #canDuplic 1 )
				)
			)
			inf ( ( #canDuplic 1 ) new_head ( :Nucleus ) )
		)
	)
	sup ( ( #canDuplic 0 ) (
			:Cycle ( #duplic #time duplic ( ) 50 0 )
			sup ( ( #duplic 500 ) kill )
		)
	)
)>

Cytosol<(
	:Init ( #init :Init_Cytosol )
)>

Nucleus<(
	:Init ( #init :Init_Nucleus )
)>

Nucleus_Move<(
	:Init ( #init :Init_Nucleus_Move )
	:Cycle ( #up #time take_out 10 1 )
	:Cycle ( #stplink #toml :Set_Prop_Chan ( &Link dst ( 0 ) ) 20 1 )
	:Cycle ( #kill #time2 kill 1400 1 )

	:Cycle ( #atrb #time4 0 (
			:Set_Prop_Chan ( &Rpls type ( atr to ) )
			:Set_Prop_Chan ( &Rpls dst ( 40 ) )
		) 50 0 )

	:Cycle ( #atrb2 #time5 0 (
			:Set_Prop_Chan ( &Rpls type ( rpls oth ) )
			:Set_Prop_Chan ( &Rpls dst ( 40 ) )
		) 40 0 ) 
)>

Init_Nucleus_Move<(
	set ( @ImLink 10 )

        :Set_Prop_Chan ( &Link type ( link ) )
        :Set_Prop_Chan ( &Link act ( @ImNucleus @block ) )
        :Set_Prop_Chan ( &Link dst ( 20 ) )
	[ &Link Value as no null after linked -> it's possible to stop it ]
	
        :Make_Rpls_Mv ( &Rpls oth @ImLink @ImLink )
        :Init_Prop_Chan ( &Rpls 10 40 )

	:Make_Rpls_Mv ( &Rpls2 oth @ImLink @ImLink )
	:Init_Prop_Chan ( &Rpls2 20 20 )

        :Make_Atr_Mv ( &Atr oth @ImLink @ImNucleus )    [ replace with link force ]
        :Init_Prop_Chan ( &Atr 15 20 )
)>

Init_Cytosol<(
	set ( @ImCytosol 30 )

        :Make_Rpls_Mv ( &Rpls oth @ImCytosol @ImCytosol )	[ replace with link force ]
       	:Init_Prop_Chan ( &Rpls 10 15 )
)>

Init_Nucleus<(
	set ( @Impulse 10 @ImNucleus 10 )

	:Make_Atr_Mv ( &AtrC oth @ImNucleus @ImCytosol )	[ replace with link force ]
	:Init_Prop_Chan ( &AtrC 10 80 )

	:Make_Rpls_Mv ( &RplsCell1 to @ImNucleus @ImCytosol )
	:Init_Prop_Chan ( &RplsCell1 2 10 )

	:Make_Rpls_Mv ( &RplsCell2 oth @ImNucleus @ImCytosol )
        :Init_Prop_Chan ( &RplsCell2 15 10 )
)>
