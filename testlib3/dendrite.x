Init_Dendrite<(
	set ( @ImDendriteHead 10 )

	:Make_Rpls_Mv ( &RplsCell ?to @ImDendriteHead @ImCell )
	set ( &RplsCell^?pw 10 )
	cp ( &RplsCell^?scope ?scope ( ?link ) )

	cp ( &RplsOth 0 (
			10 0 20
			?act ( @ImDendriteHead @ImDendriteHead )
			?mv ?to ?rpls
			0 0 ?scope ( ?oth )
		)
	)
)>

Install_Dendrite<(
	inf ( ( #install 1 ) (
                        :Make_Link (
                                &LinkCell @ImCell @Block
                                20 #install
                        )
                        cp ( &LinkCell^?scope ?scope ( ?oth ) )
                ) ( :Init ( set ( &RplsCell^?dst 15 ) ) )
        )
)>

Dendrite<(
	:Init ( :Init_Dendrite )
	:Install_Dendrite
	sup ( ( @ImActive 0 ) (
			sub ( @ImActive 1 )
		)
	)
)>
