MAIN<(
	echo ( 10 )
	set ( #val 5 )
	set ( #length 1000 )
	
	call ( :TT 0 ( #length ) )
	[inf ( ( #it 1000 ) ( :Bcl ) )]
	add ( !it 1 )
)>

Bcl<(
	set ( !it 0 )

	while ( inf ( ( !it #length ) ) (
			echo ( #it 32 !it 10 )
			set ( # ( /tab #it !it ) #val )
			add ( #val !it )
			add ( !it 1 )
		)
	)
)>

TT<(
	echo ( !av^0 10 )
)>


[bytecode-state-1]
[
:Main ( 0 (
		set ( # ( /val ) 5 )
		set ( # ( /length ) 1000 )
		while ( inf ( 0 ( ! ( /it ) 1000 ) )
			0 (
				:Bcl ( 0 (
						set ( ! ( /it ) 0 )
						while ( inf ( 0 ( ! ( /it ) # ( /length ) ) )
							0 (
								set ( # ( /tab ! ( /it ) ) # ( /val ) )
								add ( ! ( /it ) 1 )
							)
						)
					)
				)
			)
		)
	)
)

[bytecode-state-2]
[sg]
[g]
0x000|#val
1x000|#length
2x000|#tab
[0]
[l]
0x100|!it
[c]
set|#val|5|
set|#length|1000|
add|!it|1|
call|1|
inf|!it|1000|
jmp|-6

[1]
[l]
0x200|!it
1x200|!tmp
[c]
set|!it|0|
ref|!tmp|#tab|
mv|!tmp|!it|
set|!tmp|#val|
add|!it|1|
inf|!it|#length|
jmp|-15

[ASM-state-3]

[0]
mov &#val, 5
mov &#length, 1000
:while
mov eax, &!it
add eax, 1
mov &!it, eax
call &[1]
mov eax, &!it
mov ebx, 1000
cmp eax, ebx
jnl %:while
ret

[1]
move &!it, 0
:while
//
//
//
mov eax, &!it
add eax, 1
mov !it, eax
mov eax, !it
mov ebx, 1000
cmp eax, ebx
jnl %:while
ret
