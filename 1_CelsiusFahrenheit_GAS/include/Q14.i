@;----------------------------------------------------------------
@;  Declaració de constants GAS per al tractament de dades 
@;	en format Coma Fixa 1:17:14.
@;----------------------------------------------------------------
@;	pere.millan@urv.cat
@;	santiago.romani@urv.cat
@;	(Març 2021)
@;----------------------------------------------------------------

	@; MÀSCARES per als camps de bits de valors 1:17:14
MASK_SIGN = 0x80000000				@; bit 31:		signe
MASK_INT  = 0x7FFFC000				@; bits 30..14:	part entera
MASK_FRAC =	0x00003FFF				@; bits 13..0:	part fraccionària
