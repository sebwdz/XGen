
[ Network connection ]

clean<(
	set (* (#this /_param ?limit 0) sub (* (#this /_param ?limit 0) 1))
)>

find|exec($chan)<(
	sup ((* (#__oth__ $chan ) 0)(ret (1)))
)>

[ Client ]

client($name)<(
	:Init ((
			cp (@__pos__ 0 (50 sub (mod (rand 100) 50))) move
			set (@Client 10)
			cp (@Name $name)
	))
	sup ((@Message 0)(
			echo (@Name " say : " @Message "\n")
			cp (@Message 0)
	))
)>

[ send data ]

send|exec($chan)<(
	set (@count add (@count 1))
	echo (@count "\n")
	sup ((* (#__oth__ $chan) 0)(
		cp (* (#__oth__ /Message) * (#this /_message))
	))
)>

send|response<(
	set (@real add (@real * (#__res__^_gl^count)))
	set (@real)
	set (* (#this /_real) add (* (#this /_real * (#__res__^_inter^_count)))
)>

Server<(
	:Init ((
			cp (@Name 2 ("Server X!"))
			cp (@__pos__ 0 (-50 0)) move
			set (@Server 10)
[			cp (&Find^_exec :find|exec (/Client))
			cp (&Find^_clean :clean)
			cp (&Find^_param 0 (200 0 ?scope (?oth) ?link ?limit (1)))
]
			cp (&Send^_exec :send|exec (/Client))
			cp (&Send^_clean :clean)
			cp (&Send^_response :send|response)
			cp (&Send^_param 0 (0 0 ?scope (?network) ?manual ?limit))

			cp (&Send^_message 2 ("Hello World 2.0!!!"))
	))
	sup ((set (!t add (!t 1)) 200)(
[		set (&Find^_param^?limit^0 1)
]		set (&Send^_param^?limit^0 1)
		set (!t 0)
	)(set (&Send^_param^?limit^0 0)))
)>

main_client<(
	:Init ((
			echo ("Client!\n")
			:get_pid
	))
	:client (2 ("client1"))
)>

main_server<(
	:Init ((
			echo ("Server!\n")
			:get_pid
	))
	:Server
)>

main<([
	:Init ((
		creat ((:server))
		creat ((:client (2 ("client1"))))
		creat ((:client (2 ("client2"))))
		creat ((:client (2 ("client3"))))
	))]
)>