Set_Prop_Chan($name $prop)<(
        var ( $name ( $prop ) )
)>

Make_Chan($name $type $act)<(
	:Set_Prop_Chan ( $name $type )
        :Set_Prop_Chan ( $name $act )
)>

Make_Atr_Mv($name $to $act1 $act2)<(
        :Make_Chan ( $name
		type ( $to mv atr )
		act ( $act1 $act2 )
	)
)>

Make_Rpls_Mv($name $to $act1 $act2)<(	
	:Make_Chan ( $name
                type ( $to mv rpls )
                act ( $act1 $act2 ) 
        )
)>

Make_Atr_Chng($name $to $act1 $act2)<(
	:Make_Chan ( $name
                type ( $to chng atr )
                act ( $act1 $act2 ) 
        )
)>

Make_Rpls_Chng($name $to $act1 $act2)<(
	:Make_Chan ( $name
                type ( $to chng rpls )
                act ( $act1 $act2 ) 
        )
)>

Init_Prop_Chan($name $pow $dst)<(
        :Set_Prop_Chan ( $name pw ( $pow ) )
        :Set_Prop_Chan ( $name dst ( $dst ) )
)>

Make_Spe_Chan($name $act1 $act2 $type $dst)<(
	:Set_Prop_Chan ( $name type ( $type ) )
	:Set_Prop_Chan ( $name act ( $act1 $act2 ) )
	:Set_Prop_Chan ( $name dst ( $dst ) )
)>

Make_Give_Chan($name $from $to)<(
	:Make_Chan ( $name type ( chng atr to ) act ( $from $to ) )
	:Set_Prop_Chan ( $name pw ( 10 ) )
)>

Give_Cycle($name $active $dstOn $dstOff)<(
	:Set_Prop_Chan ( $name dst ( $dstOff ) )
	sup ( ( $active 0 )
		( :Set_Prop_Chan ( $name dst ( $dstOn ) ) )
	)
)>
