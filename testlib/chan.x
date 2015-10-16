Set_Prop_Chan($name $prop)<
0 (
        var ( $name ( $prop ) )
)
>

Make_Chan($name $to $act $type $mode)<
0 (
	:Set_Prop_Chan ( $name type ( $type $to $mode ) )
        :Set_Prop_Chan ( $name $act )
)
>

Make_Atr_Mv($name $to $act1 $act2)<
0 (
        :Make_Chan ( $name $to act ( $act1 $act2 ) mv atr )
)
>

Make_Rpls_Mv($name $to $act1 $act2)<
0 (	
	:Make_Chan ( $name $to act ( $act1 $act2 ) mv rpls )
)
>

Make_Atr_Chng($name $to $act1 $act2)<
0 (
	:Make_Chan ( $name $to act ( $act1 $act2 ) chng atr )
)
>

Make_Rpls_Chng($name $to $act1 $act2)<
0 (
	:Make_Chan( $name $to act ( $act1 $act2 ) chng rpls )
)
>

Init_Prop_Chan($name $pow $dst)<
0 (
        :Set_Prop_Chan ( $name pw ( $pow ) )
        :Set_Prop_Chan ( $name dst ( $dst ) )
)
>
