Set_Prop_Chan<
0 (
        var ( $0 ( $1 ) )
)
>

Make_Chan<
0 (
	:Set_Prop_Chan ( $0 type ( $3 $1 $4 ) )
        :Set_Prop_Chan ( $0 $2 )
)
>

Make_Atr_Mv<
0 (
        :Make_Chan ( $0 $1 act ( $2 $3 ) mv atr )
)
>

Make_Rpls_Mv<
0 (	
	:Make_Chan ( $0 $1 act ( $2 $3 ) mv rpls )
)
>

Make_Atr_Chng<
0 (
	:Make_Chan ( $0 $1 act ( $2 $3 ) chng atr )
)
>

Make_Rpls_Chng<
0 (
	:Make_Chan( $0 $1 act ( $2 $3 ) chng rpls )
)
>

Init_Prop_Chan<
0 (
        :Set_Prop_Chan ( $0 pw ( $1 ) )
        :Set_Prop_Chan ( $0 dst ( $2 ) )
)
>
