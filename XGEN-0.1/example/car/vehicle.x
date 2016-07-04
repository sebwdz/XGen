
Vehicle<(
	?class
		?m /construct		?l :Vehicle|construct ?le

		?m /set_rnumber		?l :Vehicle|set_rnumber ?le
		?m /set_year		?l :Vehicle|set_years ?le
		?m /set_price		?l :Vehicle|set_price ?le

		?m /get_rnumber		?l :Vehicle|get_rnumber ?le
		?m /get_year		?l :Vehicle|get_years ?le
		?m /get_price		?l :Vehicle|get_price ?le

		?m /to_string		?l :Vehicle|to_string ?le

		?m /start			?_ 0 ?_
		?m /accelerate		?_ 0 ?_

		?at /rnumber 		?_ 0 ?_
		?at /year 			?_ 0 ?_
		?at /price 			?_ 0 ?_
	?eclass
)>

Vehicle|construct<( ?this
	set (* (!prv /rnumber) incr (@Vehicle^rnumber))
	set (* (!prv /year) #__av__^0)
	set (* (!prv /price) #__av__^1)
)>

Vehicle|set_rnumber<( ?this
	set (* (!prv /rnumber) #__av__^0)
)>

Vehicle|set_years<( ?this
	set (* (!prv /years) #__av__^0)
)>

Vehicle|set_price<( ?this
	set (* (!prv /price) #__av__^0)
)>

Vehicle|get_rnumber<( ?this
	* (!prv /rnumber)
)>

Vehicle|get_years<( ?this
	* (!prv /year)
)>

Vehicle|get_price<( ?this
	* (!prv /price)
)>

Vehicle|to_string<( ?this
	cp (!year call (:Utils|int_to_string 0 (* (!prv /year))))
	cp (!rnumber call (:Utils|int_to_string 0 (* (!prv /rnumber))))
	cp (!price call (:Utils|int_to_string 0 (* (!prv /price))))
	call (:Utils|concat_str 0 
			(("Vehicle ") !rnumber
				0 (" price = ") !price
				0 (" year = ") !year))
)>