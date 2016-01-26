<
        ?dst            0;
        ?mindst         1;
        ?pw             2;
        ?act            3;
        ?type           4;
        ?target         5;
        ?dir            6;
	?reduce		7;
	?limit		8;
	?scope		9;

	[ type ]
        ?mv             0;
        ?chng           1;
	?comin		13;
	?link		12;

	[ target ]
        ?oth            1;
        ?to             0;

	[ dir ]
        ?rpls           1;
        ?atr            0;

	[ reduce ]
	?auto		0;
	?fix		1;

	[ scope ]
	?parent		0;
	?oth		1;
	?son		2;
	?link		12;

	[interaction]
	?need		0;
	?forbiden	1;
>

Make_Atr_Mv($name $to $act1 $act2)<(
        cp ( $name 0 (
			0 0 0
                	?act ( $act1 $act2 )
			?mv $to ?atr
			?reduce ( ?auto 1 )
			
		)
        )
)>

Make_Rpls_Mv($name $to $act1 $act2)<(   
        cp ( $name 0 (
                	0 0 0   
                	?act ( $act1 $act2 )
                	?mv $to ?rpls
			?reduce ( ?auto 1 )
		)
        )
)>

Make_Atr_Chng($name $to $act1 $act2)<(
        cp ( $name 0 (
                	0 0 0
                	?act ( $act1 $act2 )
                	?chng ?to ?atr
			?reduce ( ?auto 1 )
		)
        )
)>

Make_Rpls_Chng($name $to $act1 $act2)<(
        cp ( $name 0 (
                	0 0 0 
                	?act ( $act1 $act2 )
                	?chng $to ?rpls
			?reduce ( ?auto 1 )
		)
        )
)>

Make_Give_Chan($name $act1 $act2)<(
	cp ( $name 0 (
			0 0 0
			?act ( $act1 $act2 )
			?chng ?to ?atr
			?reduce ( ?auto 1 )
		)
	)
)>

Make_Spe_Chan($name $act1 $act2 $type $dst)<(
	cp ( $name 0 (
			$dst 0 0
			?act ( $act1 $act2 )
			$type ?to ?atr
		)
	)
)>

Make_Link($name $act1 $act2 $dst $limit)<(
	inf ( ( $limit 1 ) (
			cp ( $name 0 (
					$dst 0 0
					?act ( $act1 $act2 )
					?link 0 0
					?reduce ?limit ( 1 )
				)
			)
			inf ( ( $name ( ?limit 0 ) 1 ) (
					set ( $name ( ?dst ) 0 )
					set ( $limit 1 )
				)
			)
		)
	)
)>
