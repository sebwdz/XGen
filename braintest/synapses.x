
[ SYNAPSE ]

Synapse<(
	cp (!syn % ((#__av__^0 #__av__^1)))
	egal ((@SynapsesDest /Impulse)(
			set (* (!syn 2) sub (div (mod (rand 100) 100) 0.5))
	)(set (* (!syn 2) 1)))
	cp (!av #__av__)
	call (:Push 0 (% (* (!av^0 /Synapses)) !syn))
	call (:Push 0 (% (* (!av^1 /Synapses)) !syn))
)>