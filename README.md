Projet FAR --Role du robot--

Herreros Vincent
Thevenon Romain

Pour compiler :
1) nous avons un fichier principal.c qui est le programme principal sans aucun serveur (car lorqu'on utilise ses derniers nous obtenons un erreur de compilation), ce qui permet de faire fonctionner notre robot en entrant nous meme des coordonnées et ne pouvant pas prendre de ballon ni verifier si but valide
		donc pour compiler gcc principal.c gopigo.c -o principal 
		

2) il y a donc le fichier principal2.c qui lui possède certains serveurs comme conectbeebot.c serveur_robot.c mais cela ne compile pas (erreur)
		donc pour compiler gcc principal2.c gopigo.c conectbeebot.c serveur_robot.c  -o principal2



ce qui marche : le programme principal sans serveur c'est à dire on rentre a la main les coordonnées du debut, celles du distributeur, le robot va au distributeur s'arrete 4 secondes et repart direction cage adversaire (calculé selon le y de debut)

ce qui marche pas encore : la connexion au beebot au debut du programme, dans conectbeebote.C on a créer la fonction qui permet d'envoyer nos informations mais cela ne marche pas, pareillement on n'aarive pas a executer le programme car pour le serveur de distributeur de ballon il nous renvoie une erreur. il reste également a implementer le validateur de but et le serveur de position


