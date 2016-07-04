
new_vehicle<( ?av_s
	cp (!vehicle call (:new 0 (#New (#__av__^1) 0 (#__av__^2 #__av__^3))))
	cp (!__av__^0 % ((!vehicle !__av__^0)))
)>

test<(
	cp (#New^Car % (:Car))
	cp (#New^Truck % (:Truck))
	cp (#new_vehicle :new_vehicle)

	cp (!list 0)
	cp (!list call (#new_vehicle 0 (!list /Car 2916 24)))
	cp (!list call (#new_vehicle 0 (!list /Truck 2012 24)))
	cp (!list call (#new_vehicle 0 (!list /Car 2011 24)))
	cp (!list call (#new_vehicle 0 (!list /Truck 2000 24)))

	cp (!tmp !list)
	while (sup ((!tmp 0))(
			echo (call (* (* (!tmp 0) /to_string)) "\n")
			call (* (* (!tmp 0) /start))
			call (* (* (!tmp 0) /accelerate))
			cp (!tmp * (!tmp 1))
	))

	set (!x call (:Input|read_int))
	echo (!x "\n")
	set (!x call (:Input|read_float))
	echo (!x "\n")
	cp (!x call (:Input|read 0 (15)))
	echo (!x "\n")
	set (!x | (/input /read_int))
	echo (!x\ "\n")
)>

Input|read_int<(|input^read_int)>
Input|read_float<(|Input^read_float)>
Input|read<(|Input^read (#__av__^0))>

[

|input|read_int					=> $int
|input|read_float				=> $float
|input|read_string ($end)		=> $string
|input|read ($size)				=> $string

|file|open ($name)				=> $fd
|file|close ($fd)				=> ()
|file|open_dir ($name)			=> $dir
|file|list_dir ($dir)			=> ($file ... $file)
|file|type ($name)				=> $type (file, dir, link, ...)

|output|write ($fd $string)		=> $nb
|output|write_int ($fd $int)	=> $nb
|output|write_node ($fd $node)	=> $nb

]