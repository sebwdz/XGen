	.data
	msg :               .asciz "Hello, World !\n"
	len = . - msg
	                    .bss
	                    .text
	                    .global _start

	_start :
	                     movl $msg,%ecx
	                     movl $len,%edx
	                     movl $1,%ebx
	                     movl $4,%eax
	                     int  $0x80           # appel système

	exit :
	                     movl $0,%ebx
	                     movl $1,%eax
	                     int  $0x80 
