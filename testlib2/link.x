Init_Base_Link($to)<(
	set ( @ImBaseLink 10 )
	set ( @ImBase 10 )

	:Make_Spe_Chan ( &LinkTo $to @Block link 50 )

	:Make_Give_Chan ( &GiveBase @ImBase @ImLink )

	:Make_Atr_Mv ( &AtrElm oth @ImBaseLink $to )
	:Init_Prop_Chan ( &AtrElm 10 70 )

	:Make_Atr_Mv ( &AtrTo to @ImBaselink $to )
	:Init_Prop_Chan ( &AtrTo 20 70 )
)>

Install_Base_Link($link)<(
	:CycleL ( :Set_Prop_Chan ( &LinkTo dst ( 0 ) ) 5 1 )
        :CycleL ( :Make_Spe_Chan ( &CominLink $link @Block comin 40 ) 10 1 ) 
        :CycleL ( :Set_Prop_Chan ( &CominLink dst ( 0 ) ) 15 1 )
        :CycleL ( :Init_Prop_Chan ( &GiveBase 20 250 ) 20 1 )
        :CycleL ( :Set_Prop_Chan ( &GiveBase dst ( 0 ) ) 35 1 )
        :CycleL ( set ( #finish 1 ) 35 1 )
)>

Base_Link($to $link)<(
	:Init ( :Init_Base_Link ( $to ) )
	inf ( ( #finish 1 ) ( :Install_Base_Link ( $link ) ) )
)>

Init_Link($to $link $base)<(
	set ( @ImLink 10 )
	creat ( :Base_Link ( $to $link ) $base )
)>

Link($to $link $base $head)<(
	:Init ( :Init_Link ( $to $link $base ) )
	sup ( ( @ImBase 0 ) (
			:Init ( take_out ) 
		 	:Init ( new_head ( :Head_Link $head ) )
		)
	)
)>

Init_Head_Link<(
	shared ( @ImSplit )
	inf ( ( @ImSplit 1 ) (
			set ( @ImMain 10 )
			set ( @ImSplit 10 )
		) ( set ( @ImMain 0 ) )
	)
)>

Head_Link<(
	:Init ( :Init_Head_Link ( ) )

        sup ( ( @ImMain 0 ) (
			:Init ( :Init_Head_Link_Code ( ) )
			:CycleL ( unshared ( @ImSplit ) 2 1 )
                ) (
			:Init ( :Init_Head_Link_Split ( ) )
			inf ( ( #finish 1 ) (
					:CycleL ( :Set_Prop_Chan ( &Link dst ( 0 ) ) 10 1 )
					:CycleL ( take_out 10 1 )
					:CycleL ( set ( #finish 1 ) 120 1 )
				)
			)
		)
        )
)>

Init_Head_Link_Code<(
	set ( @ImHeadLink 10 )

	:Make_Atr_Mv ( &AtrHead to @ImHeadLink @ImHeadLinkSplit )
        :Init_Prop_Chan ( &AtrHead 20 70 )

	:Make_Atr_Mv ( &AtrToHead oth @ImHeadLink @ImHeadLinkSplit )
        :Init_Prop_Chan ( &AtrToHead 20 70 )

	split ( )
)>

Init_Head_Link_Split<(
	set ( @ImHeadLinkSplit 10 )
	unshared ( @ImSplit )

	:Make_Spe_Chan ( &Link @ImHeadLink @Block link 50 )
)>
