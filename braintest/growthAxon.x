
[ SYNAPSE SETTER ]

[ Impulse ]

GrowthCone|createSynapse<(
	cp (!syn #__av__^0)
	call (:Synapse|add 0 (!syn /_receptor /Impulse
								% ((/Impulse))))
	call (:Synapse|add 0 (!syn /_emetor /Impulse
								% ((/Impulse))))
)>

[ Dopamine ]

GrowthCone|dopSynapse<(
	cp (!syn #__av__^0)
	call (:Synapse|add 0 (!syn /_receptor /DopPositive
								% ((/Dopamine))))
	call (:Synapse|add 0 (!syn /_receptor /DopNegative
								% ((/Dopamine))))
	call (:Synapse|add 0 (!syn /_emetor /Impulse
								% ((/Dopamine))))
)>

[ Peptide ]

GrowthCone|pepSynapse<(
	cp (!syn #__av__^0)
	call (:Synapse|add 0 (!syn /_receptor /Peptide
								% ((/Peptide))))
	call (:Synapse|add 0 (!syn /_emetor /Impulse
								% ((/Peptide))))
)>

[ GROWTH CONE ]

AtrByNeuron|exec<(
	and ((
			sup ((* (#__oth__ /ImNeuron) 0))
			inf ((* (#__oth__ /Input) 1))
			no ((egal ((* (#__oth__  /CellId) @Id))))
			egal ((* (#__oth__ /SynapsesDest) /Impulse))
		)(
			cp (!syn call (:Synapse 0 (% (* (#__oth__)) % (@))))
			call (@CreateSynapse 0 (!syn))
	))
)>

AtrByNeuron|clean<(
	set (* (#this /_param ?limit 0) 0)
)>

RplsNucleus|exec<(
	and ((
			inf ((#__vct__^2 20))
			sup ((* (#__oth__ /ImNucleus) 0))
		)(
			set (@__pos__^0 sub (@__pos__^0 mult (#__vct__^0 3)))
			set (@__pos__^1 sub (@__pos__^1 mult (#__vct__^1 3)))
	))
)>

RplsNucleus|clean<(
	sup ((* (#this /_param ?limit 0) 0)(
			cp (* (#this /_param ?limit 0) 0)
			move
		)(sup ((set (!time add (!time 1)) 50)(
				cp (* (#this /_param ?limit 0) 1)
				set (!time 1)
		))
	))
)>

AxonLink<(
	:Init ((
			cp (&AtrByNeuron^_exec :AtrByNeuron|exec)
			cp (&AtrByNeuron^_clean :AtrByNeuron|clean)
			cp (&AtrByNeuron^_param 0 (150 1 ?scope (?oth) ?manual ?limit (1)))
	))
	inf ((&AtrByNeuron^_param^?limit^0 1)(
			erase (& /AtrByNeuron)
			:freeAndKill
	))
)>

ExprAtr<(
	sup ((set (!time add (!time 1)) 200)(
			set (!ok 1)
			attach ((:AxonLink))
			erase (& /RplsNucleus)
	))
	sup ((!ok 0)(:freeAndKill))
)>

GrowthCone<(
	:Init ((
			no ((egal ((@SynapsesDest /Impulse)))(
				egal ((@SynapsesDest /Dopamine)(
						cp (@CreateSynapse^0 :GrowthCone|dopSynapse)
					)(
						cp (@CreateSynapse^0 :GrowthCone|pepSynapse)
				))
			)(cp (@CreateSynapse^0 :GrowthCone|createSynapse)))
			cp (&RplsNucleus^_exec :RplsNucleus|exec)
			cp (&RplsNucleus^_clean :RplsNucleus|clean)
			cp (&RplsNucleus^_param 0 (0 0 ?scope (?link) ?manual ?limit (1)))
			attach ((:ExprAtr))
	))
	:freeAndKill
)>