Nucleus_Cell_Init<
0 (
	inf ( @init 1
		:Nucleus_Cell_Chan
		:Rpls_Oth_Act
		sup ( @S_Crt 1
			sup ( @S_ToAct 0 :To_Act_Chan :Attach_Act )
		)
		set ( @NclChan 10 )
		inf ( @S_Crt 2 var ( &NclRpls ( type ( oth ) pw ( 20 ) ) ) )
	)
)
>

Nucleus_Cell<
0 (
	:Skl_Center
	:Nucleus_Cell_Init
	sup ( @IS_ACT 0 add ( @act @IS_ACT ) set ( @IS_ACT 0 ) )
	sup ( @act 3 var ( &AtrOth ( pw ( 20 ) ) ) )
	set ( @isAttach 0 )
	sup ( @CHECK_ATTACH 0
		var ( &AtrAct ( pw ( 0 ) ) )
		set ( @isAttach @CHECK_ATTACH ) set ( @CHECK_ATTACH 0 )
		set ( @IsOnAct 10 )
	)
	inf ( @IsOnAct 1 var ( &AtrAct ( pw ( 40 ) ) ) )
	add ( @init 1 )
)
>

Kill_Nucleus_Act<
0 (
	sup ( @S_ToAct 0
                sup ( @crtLife 90 set ( @S_ToAct 0 )
                        inf ( @isAttach 1 set ( @KillCell 10 ) )
                )
                add ( @crtLife 1 )
        ) )
)
>
