Case.m
	la liste des couleurs dans l'ordre
	--> incrémentation des couleurs
	getCouleur();
	
Grille3D.m
	tableau 3D de case.m

Fourmi.m
	Direction
	getDirection()
	function Tourner(Couleur) return Direction
	Règles : (Couleur DirectionSuivante Incrémentation?)
	Avancer
	Position (x,y,z)
	
Affichage.m
	On modifie uniquement les cases qui ont été modifiées
	case(x,y,z,new_color)

Monde.m
	Contient une liste de fourmis
	Contient une grille3D
	update : for i in 1..nbreFourmi {Fourmi[i].avancer(Tourner(getCouleur(Fourmi[i].getPosition)))};    ||    Grille3D(getCase(x, y, z)++)
	--> update renvoie la position de la case qui a été modifiée à l'affichage.m (case (x,y,z) est passée à la couleur XXX) + pos fourmis

Main.m
	Init:	Créer un monde, placer toutes les fourmis, dessiner la grille (intéractions avec l'utilisateur : placement des fourmis + nombre)
	boucle 'infinie' : update du Monde.m
