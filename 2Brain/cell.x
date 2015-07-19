Cell_Head<
0 (
	inf ( @ready 1
		inf ( @nclCell 1 add ( @nclCell 1 )
			new_head ( :Nucleus_Cell )
		)
		inf ( @nclCytosol 7 add ( @wait 1 )
			sup ( @wait 4
				add ( @nclCytosol 1 )
				set ( @wait 0 )
				new_head ( :Cytosol )
			)
		)
		sup ( @nclCytosol 6 add ( @ready 4 ) )
	)
)
>

Create_Cell<
0 (
	inf ( @act 1 set ( @act 1 )
		set ( @duplic 10 )
		set ( @S_ToAct 10 )
	)
	inf ( @act 2
		sup ( @wait 30
			inf ( @duplic 1 set ( @duplic 15 )
				set ( @needCreate 5 )
				add ( @act 1 )
				set ( @S_ToAct 0 )
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
	shared ( @S_Crt @S_ToAct )
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
			duplic ( 0 )
		)
	)
	sup ( @KillCell 0 kill )
)
>
