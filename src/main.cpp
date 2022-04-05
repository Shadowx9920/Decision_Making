#include <iostream>

using namespace std;

const int NBR_STRATEGY = 4;
const int NBR_DEMANDE = 5;

float tableauDedemande[NBR_DEMANDE] = {5000,10000,15000,20000,30000};
float lesStrategies[NBR_STRATEGY] = {4000,12000,15000,25000};

float matriceDesQuantite[NBR_STRATEGY][NBR_DEMANDE];
float matriceDesAchats[NBR_STRATEGY][NBR_DEMANDE];
float matriceDesSubvention[NBR_STRATEGY][NBR_DEMANDE];
float matriceDesVentes[NBR_STRATEGY][NBR_DEMANDE];
float matriceDesGains[NBR_STRATEGY][NBR_DEMANDE];
float matriceDesRegrets[NBR_STRATEGY][NBR_DEMANDE];

void calculDesQuantiteAchete(){
	for(int i = 0; i < NBR_STRATEGY; i++){
		for(int j = 0; j < NBR_DEMANDE; j++){
			//TODO: check if it's min(demande,strategie) or just strategie
			matriceDesQuantite[i][j] = lesStrategies[i];
		}
	}
}

void calculDesAchats(){
	for(int i = 0; i < NBR_STRATEGY; i++){
		for(int j = 0; j < NBR_DEMANDE; j++){
			float uniteAcheter = lesStrategies[i];
			if (uniteAcheter <= 6000 && uniteAcheter >= 3000){
				matriceDesAchats[i][j] = uniteAcheter * 3.0;
			}else if (uniteAcheter <= 14000 && uniteAcheter >= 6001){
				matriceDesAchats[i][j] = uniteAcheter * 2.75;
			}else if(uniteAcheter <= 22000 && uniteAcheter >= 14001){
				matriceDesAchats[i][j] = uniteAcheter * 2.50;
			}else if(uniteAcheter >= 22001){
				matriceDesAchats[i][j] = uniteAcheter * 2.25;
			}
		} 
	}
}

void calculDesSubvention(){
	for(int i = 0; i < NBR_STRATEGY; i++){
		for(int j = 0; j < NBR_DEMANDE; j++){
			if (matriceDesQuantite[i][j] <= 5000 && matriceDesQuantite[i][j] >= 3000){
				matriceDesSubvention[i][j] = matriceDesAchats[i][j] * 0.01;
			}else if (matriceDesQuantite[i][j] <= 14000 && matriceDesQuantite[i][j] >= 5001){
				matriceDesSubvention[i][j] = matriceDesAchats[i][j] * 0.02;
			}else if(matriceDesQuantite[i][j] <= 22000 && matriceDesQuantite[i][j] >= 14001){
				matriceDesSubvention[i][j] = matriceDesAchats[i][j] * 0.03;
			}else if(matriceDesQuantite[i][j] >= 22001){
				matriceDesSubvention[i][j] = matriceDesAchats[i][j] * 0.05;
			}
		}
	}
}

void calculDesChiffresDaffaires(){
	for(int i = 0; i < NBR_STRATEGY; i++){
		for(int j = 0; j < NBR_DEMANDE; j++){
			switch (j)
			{
			case 0:
				matriceDesVentes[i][j] = min(lesStrategies[i], tableauDedemande[j]) * 4.0;	
				break;
			case 1:
				matriceDesVentes[i][j] = min(lesStrategies[i], tableauDedemande[j]) * 4.5;
				break;
			case 2:
				matriceDesVentes[i][j] = min(lesStrategies[i], tableauDedemande[j]) * 5.0;
				break;
			case 3:
				matriceDesVentes[i][j] = min(lesStrategies[i], tableauDedemande[j]) * 5.5;
				break;
			case 4:
				matriceDesVentes[i][j] = min(lesStrategies[i], tableauDedemande[j]) * 6.0;
				break;
			default:
				break;
			}
		}
	}
}

void calculMatriceDesGains(){
	for(int i = 0; i < NBR_STRATEGY; i++){
		for(int j = 0; j < NBR_DEMANDE; j++){
			matriceDesGains[i][j] = matriceDesVentes[i][j] - matriceDesAchats[i][j] + matriceDesSubvention[i][j]-600;
		}
	}
}

void printMatrice(float matrice[][NBR_DEMANDE]){
	cout << "\t\t";
	for (int i = 0; i < NBR_DEMANDE; i++)
	{
		cout << "Chef " << i << "\t\t"; 
	}
	cout << endl;
	for(int i = 0; i < NBR_STRATEGY; i++){
		cout << "Strategie " << i+1 << "\t\t";
		for(int j = 0; j < NBR_DEMANDE; j++){
			cout << matrice[i][j] << "\t\t";
		}
		cout << endl;
	}
	cout << endl;
}

void critereDeWALD(float matrice[][NBR_DEMANDE]){

	// Calcul de des Minimum de chaque strategie
	float minimum[NBR_STRATEGY];
	for(int i = 0; i < NBR_STRATEGY; i++){
		minimum[i] = matrice[i][0];
		for(int j = 1; j < NBR_DEMANDE; j++){
			if (minimum[i] > matrice[i][j]){
				minimum[i] = matrice[i][j];
			}
		}
		cout << "Minimum de la strategie " << i+1 << ": " << minimum[i] << endl;
	}

	//Maximum Des Minimum
	float tmpMax = minimum[0];
	int indexMax = 0;
	for (int i = 0; i < NBR_STRATEGY; i++)
	{
		if (tmpMax < minimum[i]){
			tmpMax = minimum[i];
			indexMax = i;
		}
	}

	cout << "Le critere de Wald a Choisis : Strategie " << indexMax +1 << endl;
}

void critereLAPLACE(float matrice[][NBR_DEMANDE]){
	float laplace[NBR_STRATEGY];
	for(int i = 0; i < NBR_STRATEGY; i++){
		float somme = 0;
		for(int j = 0; j < NBR_DEMANDE; j++){
			somme += matrice[i][j];
		}
		laplace[i] = somme / NBR_DEMANDE;
		cout << "Laplace " << i+1 << " : " << laplace[i] << endl;
	}
	float tmpMax = laplace[0];
	int indexMax = 0;
	for (int i = 0; i < NBR_STRATEGY; i++)
	{
		if (tmpMax < laplace[i]){
			tmpMax = laplace[i];
			indexMax = i;
		}
	}
	cout << "Le critere de LAPLACE a Choisis : Strategie " << indexMax +1 << endl;
}

void critereHurwicz(float matrice[][NBR_DEMANDE]){
	float Max[NBR_STRATEGY];
	float Min[NBR_STRATEGY];
	float calcul[NBR_STRATEGY];
	for(int i = 0; i < NBR_STRATEGY; i++){
		Max[i] = matrice[i][0];
		Min[i] = matrice[i][0];
		for(int j = 0; j < NBR_DEMANDE; j++){
			if (Max[i] < matrice[i][j]){
				Max[i] = matrice[i][j];
			}
			if (Min[i] > matrice[i][j]){
				Min[i] = matrice[i][j];
			}
		}
		calcul[i] = Max[i]*0.3 + Min[i]*0.7;
		cout << "Strategie " << i+1 << " : " << calcul[i] << endl;
	}
	float tmpMax = calcul[0];
	int indexMax = 0;
	for (int i = 0; i < NBR_STRATEGY; i++)
	{
		if (tmpMax < calcul[i]){
			tmpMax = calcul[i];
			indexMax = i;
		}
	}
	cout << "Le critere d'Hurwicz a Choisis : Strategie " << indexMax+1 << endl;
}

void calculMatriceDesRegrets(){
	float MaxColonne[NBR_DEMANDE];

	//get max of each column
	for(int i = 0; i < NBR_DEMANDE; i++){
		MaxColonne[i] = matriceDesGains[0][i];
		for(int j = 1; j < NBR_STRATEGY; j++){
			if (MaxColonne[i] < matriceDesGains[j][i]){
				MaxColonne[i] = matriceDesGains[j][i];
			}
		}
	}


	for(int i = 0; i < NBR_STRATEGY; i++){
		for(int j = 0; j < NBR_DEMANDE; j++){
			matriceDesRegrets[i][j] = -(matriceDesGains[i][j] - MaxColonne[j]);
		}
	}
}

void critereSavage(){
	// Calcul de des Maximum de chaque strategie
	float maximum[NBR_STRATEGY];
	for(int i = 0; i < NBR_STRATEGY; i++){
		maximum[i] = matriceDesRegrets[i][0];
		for(int j = 1; j < NBR_DEMANDE; j++){
			if (maximum[i] < matriceDesRegrets[i][j]){
				maximum[i] = matriceDesRegrets[i][j];
			}
		}
	}
	//find minimum in Maximum
		float tmpMin = maximum[0];
		int indexMin = 0;
		for (int i = 0; i < NBR_STRATEGY; i++)
		{
			if (tmpMin > maximum[i]){
				tmpMin = maximum[i];
				indexMin = i;
			}
		}
		cout << "Le critere de Savage a Choisis : Strategie " << indexMin+1 << endl;
}

void critereMINIMAX(){
	float min[NBR_STRATEGY];
	for(int i = 0; i < NBR_STRATEGY; i++){
		min[i] = matriceDesGains[i][0];
		for(int j = 1; j < NBR_DEMANDE; j++){
			if (min[i] > matriceDesGains[i][j]){
				min[i] = matriceDesGains[i][j];
			}
		}
	}
	float tmpMax = min[0];
	int indexMax = 0;
	for (int i = 0; i < NBR_STRATEGY; i++)
	{
		if (tmpMax < min[i]){
			tmpMax = min[i];
			indexMax = i;
		}
	}
	cout << "Le critere de MINIMAX a Choisis : Strategie " << indexMax+1 << endl;
}

void critereMAXIMAX(){
	float max[NBR_STRATEGY];
	for(int i = 0; i < NBR_STRATEGY; i++){
		max[i] = matriceDesGains[i][0];
		for(int j = 1; j < NBR_DEMANDE; j++){
			if (max[i] < matriceDesGains[i][j]){
				max[i] = matriceDesGains[i][j];
			}
		}
	}
	float tmpMax = max[0];
	int indexMin = 0;
	for (int i = 0; i < NBR_STRATEGY; i++)
	{
		if (tmpMax < max[i]){
			tmpMax = max[i];
			indexMin = i;
		}
	}
	cout << "Le critere de MAXIMAX a Choisis : Strategie " << indexMin+1 << endl;
}


int main(int argc, char *argv[])
{
	//Question 1 : Matrice des Gains:
	//----------------------------------------------------------------
	calculDesQuantiteAchete();
	cout << "Matrice des Quantité : " << endl << endl;
	printMatrice(matriceDesQuantite);

	calculDesAchats();
	cout << "Matrice des Achats : " << endl << endl;
	printMatrice(matriceDesAchats);

	calculDesSubvention();
	cout << "Matrice des Subvention : " << endl << endl;
	printMatrice(matriceDesSubvention);

	calculDesChiffresDaffaires();
	cout << "Matrice des Chiffres d'affaires : " << endl << endl;
	printMatrice(matriceDesVentes);

	calculMatriceDesGains();
	cout << "Matrice des Gains : " << endl << endl;
	printMatrice(matriceDesGains);
	cout << endl << endl;
	//----------------------------------------------------------------


	//Question 2 : critére de WALD
	//----------------------------------------------------------------
	critereDeWALD(matriceDesGains);
	cout << endl << endl;
	//----------------------------------------------------------------

	//Question 3 : critere LAPLACE
	//----------------------------------------------------------------
	critereLAPLACE(matriceDesGains);
	cout << endl << endl;
	//----------------------------------------------------------------

	//Question 4 : critere d'Hurwicz
	//----------------------------------------------------------------
	critereHurwicz(matriceDesGains);
	cout << endl << endl;
	//----------------------------------------------------------------

	//Question 5 : matrice des Regrets
	//----------------------------------------------------------------
	calculMatriceDesRegrets();
	cout << "Matrice des Regrets : " << endl << endl;
	printMatrice(matriceDesRegrets);
	critereSavage();
	//----------------------------------------------------------------

	//Question 6 : critere MINIMAX
	//----------------------------------------------------------------
	critereMINIMAX();
	//----------------------------------------------------------------

	//Question 7 : critere MAXIMAX
	//----------------------------------------------------------------
	critereMAXIMAX();
	//----------------------------------------------------------------
}