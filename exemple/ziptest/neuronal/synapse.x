
Synapse|receptor($to $cond)<(
	sup ((set (!nb $cond) 0)(
			incr (@ ($to) !nb)
	))
)>

Synapse|emettor($to $cond)<(
	sup ((set (!nb $cond) 0)(
			incr (* (@PoolZone $to) !nb)
	))
)>