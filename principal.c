#include "gopigo.h"
#include <stdio.h>


// fonction qui fait avancer le robot en prenant un entier en paramètre, celui-ci correspond au nombre de cases que l'on doit avancer.
void avance(int a){
	fwd();
	sleep(1.894*a);   //avance pendant le temps indiqué dans sleep. 1.894 -> le temps qu'il met pour parcourir une case.
	stop();
}

// fonction qui fait reculer le robot en prenant un entier en paramètre, celui-ci correspond au nombre de cases que l'on doit reculer.
void recule(int a){
	bwd();
	sleep(1.894*a);  //avance pendant le temps indiqué dans sleep. 1.894 -> le temps qu'il met pour parcourir une case.
	stop();
}

// fonction qui permet au robot de tourner sur la droite (angle de 45 degre)
void tourneDroite() {
	left();   //on met left car notre robot déconne quand on met right il tourne a gauche et inversement
	sleep(1.8);
	stop();
}

// fonction qui permet au robot de tourner sur la gauche (angle de 45 degre)
void tourneGauche() {
	right();
	sleep(1.8);
	stop();
}


// fonction principale, prend en paramètre la case de départ(x,y) et la case d'arrivée(x,y). Pour l'instant on part dans l'optique que le robot part toujours orienté vers le nord (voir dessin fourni dans le dossier)
char deplacement(int debX,int debY, int finX, int finY, char orientation){
	int deplaX = finX - debX;   //on calcule la différence x de la case de fin et x de la case du debut
	int deplaY = finY - debY;   //de meme pour y

	//on regarde le deplacement en x

	if(deplaX!=0){       //Si la différence de x est non nul (le robot a besoin de se déplacer en x)
		if(deplaX>0){
			if(orientation == 'N'){         //si la différence de x est superieur a 0 (le robot doit se diriger vers l'est)
				tourneDroite();
			}else if(orientation =='S'){
				tourneGauche();
			}else if(orientation == 'O'){
				tourneDroite();
				tourneDroite();
			}     
			avance(deplaX);
			orientation = 'E';
			//on regarde maintenant le cas du deplacement en y

			if(deplaY<0){      	  //si la difference de y est inférieur a 0 (le robot doit se diriger vers le nord)
				tourneDroite(); 
				avance(deplaY);
				orientation = 'S';
			}
			else if(deplaY>0){    //si la différence de y est superieur a 0 (le robot doit se diriger vers le sud)
				tourneGauche();			//il tourne donc a droite et avance du nombre de case egale a la différence de y il tourne ensuite 2 fois a gauche pour se remettre en direction vers le nord
				avance(deplaY);
				orientation = 'N';
			}
		}
		else{                    //si la différence de x est inferieur a 0 (le robot doit se diriger vers l'ouest)
			if(orientation == 'N'){         //si la différence de x est superieur a 0 (le robot doit se diriger vers l'est)
				tourneGauche();
			}else if(orientation =='S'){
				tourneDroite();
			}else if(orientation == 'E'){
				tourneGauche();
				tourneGauche();
			}     
			avance(deplaX);
			orientation = 'O';

			//on regarde maintenant le cas du deplacement de y 
			if(deplaY<0){   //si la difference de y est inferieur a 0 (le robot doit se diriger vers le nord)
				tourneGauche();  //il tourne donc a droite et avance du nombre de case egale a la difference de y
				avance(deplaY);
				orientation = 'S';
			}
			else if(deplaY>0){    //si la differnce de y est superieur a 0 (le robot doit se diriger vers le sud)
				tourneDroite();    //il tourne donc a gauche et avance du nombre de case egale a la difference de y et tourne 2 fois a droite pour se remettre en orientation vers le nord
				avance(deplaY);
				orientation = 'N';
			}
		}
	} else {      //si la difference en x est nulle (le robot n'a pas besoin de bouger en x)
		if(orientation == 'O'){
			tourneDroite();
			orientation = 'N';
		}else if (orientation == 'E'){
			tourneGauche();
			orientation = 'N';
		}
		//on regarde donc le cas du deplacement en y
		if(deplaY<0){          //si la differnce de y est inferieur a 0 on avance du nombre de case egale a la difference de y
			if(orientation == 'S'){
				avance(deplaY);
			}else{
				recule(deplaY);
			}
		}else if(deplaY>0){    //sinon si la difference est superieur a 0 on recule du nombre de case egale a la difference de y
			if(orientation == 'S'){
				recule(deplaY);
			}else{
				avance(deplaY);
			}

		}
	}
	return orientation;
}


int main(void) {
	int posdebX;
	int posdebY;
	int posfinX;
	int posfinY;
	int finalY;
	int rep = 1;
	char orientation = 'N';

	if(init()==-1)
		exit(1);
	led_on(1);
	
	//on rentre la position initiale du robot
	printf("Entrer position x de debut :");
	scanf("%d",&posdebX);
	printf("Entrer position y de debut :");
	scanf("%d",&posdebY);
	if(posdebY == 0){
		finalY = 11;
	}else{
		finalY = 0;
	}

	//on rentre la position du distributeur de ballon
	printf("Entrer position x distributeur :");
	scanf("%d",&posfinX);
	printf("Entrer position y distributeur :");
	scanf("%d",&posfinY);
	
	//Effectue le déplacement du robot vers distributeur
	orientation = deplacement(posdebX,posdebY,posfinX,posfinY,orientation);
	posdebX = posfinX;
	posdebY = posfinY;
	//char* buffer;
	//buffer=server();
	sleep(4);
	//Effectue le deplacement du robot vers final
	orientation=deplacement(posdebX,posdebY,posdebX,finalY,orientation);
	
	return 0;  

	

}
