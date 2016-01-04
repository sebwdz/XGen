<
	?dst		0;
	?mindst		1;
	?pw		2;
	?act		3;
	?type		4;
	?target		5;
	?dir		6;

	?mv		0;
	?chng		1;

	?oth		0;
	?to		1;

	?rpls		0;
	?atr		1;
>

MAIN<([
	set ( @Main 10 )]
[
	set ( &Rpls^?dst 50 )
	set ( &Rpls^?pw 10 )
	set ( &Rpls^?act^0 @MAIN )
	set ( &Rpls^?act^1 @MAIN )
	set ( &Rpls^?target ?oth )
	set ( &Rpls^?dir ?rpls )
	set ( &Rpls^?type ?mv )
]
[	cp ( &Rpls 0 (
			50 0 10
			?act ( @MAIN @MAIN )
			?mv ?oth ?rpls
		)
	)]
[
	sup ( ( !cmp 100 ) ( duplic set ( !cmp 0 ) ) )
	add ( !cmp 1 )
][
	cp ( !tt 0 )
	set ( @ ( /A !tt ) 15 )
	echo ( @A^0 10 )
]
[	shared ( /MAIN )]
	set ( #val 10 )
	set ( #length 100 )

	inf ( ( #it #length ) ( :BCL ) )
[	inf ( ( @MAIN 4 ) ( add ( @MAIN 1 ) duplic ) )]
	add ( #it 1 )

)>

BCL<(
	cp ( !it 0 )

	[set ( # ( /tab #it 1000 ) 0 )]
	[ ref ( !ref # ( /tab #it ) ) ]
	while ( inf ( ( !it #length ) ) (
[			echo ( #it 32 !it 10 )]
			[
				set ( % ( ! ( /ref ) !t ) 
				next ( !ref )
				add ( !it 1 )
			]
			set ( # ( /tab #it !it ) #val )
			add ( !it 1 )
		)
	)
)>

[ byte code - state 1 ]

:MAIN ( 0 (
		set ( # ( /val ) 10 )
		set ( # ( /length ) 1000 )
		inf ( ( # ( /it ) # ( /length ) ) (
				:BCL ( 0 (
						set ( ! ( /it ) 0 )
						while ( inf ( ( ! ( /it ) # ( /length ) ) ) (
								echo ( # ( /it ) 32 ! ( /it ) 10 )
								set ( ! ( /tab # ( /it ) ! ( /it ) ) )
								add ( ! ( /it ) 1 )
							)
						)
					)
				)
				add ( # ( /it ) 1 )
			)
		)
	)
)

[ byte code - state 2 ]

:Main
set #val, 10
set #val, 1000

cmp #it ,#length
sup %End
call %:BCL
add #it ,1
End:

:BCL
set !it, 0
		[ son !tab, #it, $tmp ]
While:
cmp !it, #length
sup %End
echo #it, 32, !it
echo 10
[ref]
son !tab, #it, $tmp	[ X ]
son $tmp, !it, $tmp	[ $tmp, !it, $tmp2 ]
[endref]
set $tmp, !it		[ $tmp2, !it ]
add !it, 1
jump %While
End:

[ byte code - state 3 ]


