
echo<( ?av_s
	echo (* (call (* (!__av__^0 /substr) 0 (1 10))) "\n")
[	echo (* (call (* (!__av__^0 /data))) "\n")]
)>

test<(
	:Utils|init ((
			cp (#new|List % (:LinkList))
			cp (#new|String % (:String))

			cp (#list call (:new 0 (#new|List)))
			call (* (#list /set_obj) 0 (1))
			call (* (#list /push_back) 0 (
				call (:new 0 (#new|String 0 (% (("Salut")))))))
			call (* (#list /push_back) 0 (
				call (:new 0 (#new|String 0 (% (("Ahaha")))))))
			call (* (#list /push_back) 0 (
				call (:new 0 (#new|String 0 (% (("othto")))))))
			call (* (#list /push_back) 0 (
				call (:new 0 (#new|String 0 (% (("ah")))))))
			
			cp (!lst % ((("Salut")
				% (((("Ahaha")
					% ((("ohto")
						% ((("ah")))))))))))
	))
	call (* (#list /for_each) 0 (% (:echo)))
	[call (* (#list /clear))
	cp (* (#list) 0)]
)>
