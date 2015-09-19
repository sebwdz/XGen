Cell_Head<
0 (
	inf ( @ready 1
		inf ( @nclCell 1 add ( @nclCell 1 )
			inf ( @canCreate 1
				sup ( @S_Cycle 1 new_head ( :Nucleus_Cell ) )
				inf ( @S_Cycle 2 new_head ( :Nucleus_Cell :Kill_Nucleus_Act ) )
			)
			sup ( @canCreate 0 new_head ( :Nucleus_Cell ) )
		)
		inf ( @nclCytosol 6 add ( @wait 1 )
			sup ( @wait 4
				add ( @nclCytosol 1 )
				set ( @wait 0 )
				new_head ( :Cytosol )
			)
		)
		sup ( @nclCytosol 5 add ( @ready 4 ) )
	)
)
>

Create_Cell<
0 (
	inf ( @act 1 set ( @act 1 )
		set ( @S_Cycle 1 )
		set ( @duplic 10 )
		set ( @S_ToAct 10 )
	)
	inf ( @act 2
		sup ( @wait 30
			inf ( @duplic 1 set ( @duplic 30 )
				add ( @S_Cycle 1 )
				set ( @needCreate 7 )
				add ( @act 1 )
				set ( @S_ToAct 10 )
			)
			set ( @wait 0 )
		)
		add ( @wait 1 )
	)
	sup ( @act 1 inf ( @duplic 1 kill ) )
)
>

Cell_Init<
0 (
	shared ( @S_Crt @S_ToAct @S_Cycle)
	inf ( @cellCrt 1 add ( @cellCrt 1 )
		:Cell_Base_Chan
		set ( @needCreate 10 )
		unuse ( @SklCenter @SklArround )
		set ( @CellChan 10 )
	)
	inf ( @S_Crt 1 set ( @canCreate 1 ) )
	inf ( @S_Crt 2 add ( @S_Crt 1 ) )
)
>

Cell<
0 (
	:Cell_Init
	:Cell_Head
	sup ( @canCreate 0 :Create_Cell )
	sup ( @duplic 0 add ( @create 1 )
		sup ( @create @needCreate
			sub ( @duplic 1 )
			set ( @create 0 )
			duplic ()
		)
	)
	sup ( @KillCell 0 kill )
)
>
