MAIN<(
	inf ( ( #canDuplic 1 ) (
			:Cycle ( #crt1 #time1 new_head ( :Cytosol ) 3 6 )
			:Cycle ( #crt3 #time3 new_head ( :Nucleus_Move ) 2 1 )
		)
	)
	:Init ( #init 
		0 (
			new_head ( :Nucleus )
			inf ( ( @S_Duplic 1 ) (
					shared ( @S_Duplic )
					set ( @S_Duplic 1 )
					set ( #canDuplic 1 )
				)
			)
		)
	)
	sup ( ( #canDuplic 0 ) (
			:Cycle ( #duplic #time duplic ( )  20 30 )
			sup ( ( #duplic 29 ) kill )
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
)>

Init_Nucleus_Move<(
	set ( @ImLink 10 )

        :Set_Prop_Chan ( &Link type ( link ) )
        :Set_Prop_Chan ( &Link act ( @ImNucleus @block ) )
        :Set_Prop_Chan ( &Link dst ( 20 ) )                     [ stop when is linked ]
	
        :Make_Rpls_Mv ( &Rpls oth @ImLink @ImLink )
        :Init_Prop_Chan ( &Rpls 10 60 )

        :Make_Atr_Mv ( &Atr oth @ImLink @ImNucleus )    [ replace with link force ]
        :Init_Prop_Chan ( &Atr 15 20 )
)>

Init_Cytosol<(
	set ( @ImCytosol 30 )

        :Make_Rpls_Mv ( &Rpls oth @ImCytosol @ImCytosol )	[ maybe replace with link force ]
       	:Init_Prop_Chan ( &Rpls 10 10 )
)>

Init_Nucleus<(
	set ( @Impulse 10 @ImNucleus 10 )

	:Make_Atr_Mv ( &AtrC oth @ImNucleus @ImCytosol )	[ maybe replace with force link force ]
	:Init_Prop_Chan ( &AtrC 5 60 )

	:Make_Rpls_Mv ( &RplsCell1 to @ImNucleus @ImCytosol )
	:Init_Prop_Chan ( &RplsCell1 2 10 )

	:Make_Rpls_Mv ( &RplsCell2 oth @ImNucleus @ImCytosol )
        :Init_Prop_Chan ( &RplsCell2 15 10 )
)>
