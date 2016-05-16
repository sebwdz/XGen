
<
	?empty	0;
	?block 	1;
	?wall 	2;
	?bombe 	3;
	?player 4;
	?def	5;
>

Init($code)<(inf ((!it 1)($code set (!it 1))))>

get_type<(
	set (!tmp mod (rand 100))
	sup ((!tmp 10)(ret (?block))(
			inf ((!tmp 2)(ret (?empty)))
			ret (?wall)
	))
)>

make_map<(
		cp (#map 0 (
			{_size  100}
			{_width 10}
		))
		while (inf ((!it #map^_size))(
				cp (!case % ((
						{_type call (:get_type)}
						{_pos !it}
				)))
				cp (#map^_case (!it) !case)
				incr (!it)
		))
		set (* (#map^_case (0) /_type) ?empty)
		set (* (#map^_case (1) /_type) ?empty)
		set (* (#map^_case (2) /_type) ?empty)
		set (* (#map^_case (sub (#map^_size 1)) /_type) ?empty)
		set (* (#map^_case (sub (#map^_size 2)) /_type) ?empty)
		set (* (#map^_case (sub (#map^_size 3)) /_type) ?empty)
)>

show_map<(
	cp (!co 0 (" #@*UM"))
	cp (!str 2 ())
	set (!it 0)
	while (inf ((!it #map^_size))(
			egal ((!it #MPos)(
					set (!str^0 "$")
			)(set (!str^0 !co (* (#map^_case (!it) /_type)))))
			echo (!str " ")
			egal ((mod (add (!it 1) #map^_width) 0)(echo ("\n")))
			egal ((* (#map^_case (!it) /_type) ?def)(
					set (* (#map^_case (!it) /_type) ?empty)
			))
			incr (!it)
	))
	echo ("\n")
)>

break_block<(
	set (!it 0)
	cp (!bombe #__av__^0)
	set (!c * (!bombe /_pos))
	egal ((* (!bombe /_dist #__av__^2) * (!bombe /_range))(ret (0)))
	and ((egal ((#__av__^1 -1)) egal ((mod (!c 10) 0)))(ret (0)))
	while (inf ((!it * (!bombe /_dist #__av__^2)))(
			incr (!c #__av__^1)
			inf ((!c 1)(ret (0)))
			and ((egal ((#__av__^1 1)) egal ((mod (!c 10) 0)))(ret (0)))
			cp (!case #map^_case (!c))
			no ((egal ((* (!case /_type) ?def)))(
					no ((egal ((* (!case /_type) ?empty)))(
							egal ((* (!case /_type ?bombe))(
									set (* (!case /_time) 0)
								)(
									egal ((* (!case /_type) ?block)(
											set (* (!case /_type) ?def)
									))
									set (* (!bombe /_dist #__av__^2) * (!bombe /_range))
									ret (0)
							))
					)(set (* (!case /_type) ?def)))
			))
			and ((egal ((#__av__^1 -1)) egal ((mod (!c 10) 0)))(ret (0)))
			incr (!it)
	))
	incr (* (!bombe /_dist #__av__^2))
)>

check_bombe<(
	:Init ((cp (#break_block :break_block)))
	set (!it 0)
	set (!len len (#map^_bombe))
	while (inf ((!it !len))(
			cp (!bombe #map^_bombe (!it))
			inf ((* (!bombe /_time) 1)(
					sup ((.+ (* (!bombe /_range) * (!bombe /_time)) 0)(
							call (#break_block 0 (!bombe 1 0))
							call (#break_block 0 (!bombe -1 1))
							call (#break_block 0 (!bombe #map^_width 2))
							call (#break_block 0 (!bombe .-(0 #map^_width) 3))
							decr (* (!bombe /_time))
							incr (!it)
						)(
							set (* (!bombe /_type) ?empty)
							erase (#map^_bombe !it)
							set (!len len (#map^_bombe))
					))
			)(decr (* (!bombe /_time)) incr (!it)))
	))
)>

add_bombe<(
		cp (!case #map^_case (#MPos))
		egal ((* (!case /_type) ?empty)(
				set (* (!case /_type) ?bombe)
				set (* (!case /_time) 2)
				set (* (!case /_range) 10)
				cp (* (!case /_dist) 0)
				cp (#map^_bombe (len (#map^_bombe)) !case)
		))
)>

exec<(
	inf ((!move 2)(
			incr (#MPos)
		)(
			egal ((!move 2)(
					:add_bombe
				)(
						inf ((!move 5)(
								decr (#MPos)
						)(
							sup ((!move 8)(
								set (!move -1)
							))
						))
			))
	))
	incr (!move)
)>

main<(
	:Init ((
		:make_map ()
		set (#MPos 0)
	))
	inf ((incr (!it) 50)(
			:exec ()
			:check_bombe ()
			:show_map ()
	))
)>
