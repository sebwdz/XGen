
clean<(
	set (* (#this /_param ?limit 0) sub (* (#this /_param ?limit 0) 1))
)>

find|exec($chan)<(
	sup ((* (#__oth__ $chan ) 0)(ret (1)))
)>

send|exec($chan)<(
	?Init cp (!message 2 ("Hello World !!!")) ?ie__
	sup ((* (#__oth__ $chan) 0)(
		cp (* (#__oth__ /Message) !message)
	))
)>

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

server<(
	:Init ((
			cp (@__pos__ 0 (-50 0)) move
			set (@Server 10)
			cp (&Find^_exec :find|exec (/Client))
			cp (&Find^_clean :clean)
			cp (&Find^_param 0 (200 0 ?scope (?oth) ?link ?limit (1)))

			cp (&Send^_exec :send|exec (/Client))
			cp (&Send^_clean :clean)
			cp (&Send^_param 0 (0 0 ?scope (?link) ?manual ?limit))
	))
	sup ((set (!t add (!t 1)) 50)(
		set (&Find^_param^?limit^0 1)
		set (&Send^_param^?limit^0 1)
		set (!t 0)
	))
)>

main<([
	:Init ((
		creat ((:server))
		creat ((:client (2 ("client1"))))
		creat ((:client (2 ("client2"))))
		creat ((:client (2 ("client3"))))
	))]
	echo ("Hello World\n")
	echo ("Worl2\n")
)>