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
ret 0
	
move &!it, 0
:while
	;; Acces a la
	;; case !it de #tab
mov &tab^!it, 1
	;; 
mov eax, &!it
add eax, 1
mov !it, eax
mov eax, !it
mov ebx, 1000
cmp eax, ebx
jnl %:while
ret 0
