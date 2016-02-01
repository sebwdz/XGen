Link($base $code)<(
	:Install_Link ( $base $code )
)>

Install_Link($base $code)<(
	inf ( ( #install 1 ) (
			:Make_Link ( &LinkBase $base @Block 20 #install )
			:Init ( cp ( &LinkBase^?scope ?scope ( ?parent ) ) )
		) (
			:Init ( take_out )
			$code
		)
	)
)>

Create_Branching_Link($base $code)<(
	:Init ( $code )
	set ( $base 10 )
	splitin
)>
