#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include <string>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int segmentacion(string datos, string resultado, int criteria, int treshold) {
	bool moving=false;
	//criteria indica cuantos pasos sin movimiento deben existir para marcar el fin de un evento
	//treshold indica la amplitud mínima que se considera como movimiento 
	int count = 0;
	float signal;
	ifstream inFile;
	inFile.open(datos);
	ofstream myfile;
  	myfile.open (resultado);
  	int time = 0;
  
	 while (inFile >> signal) {
    	if (moving){
			if (abs(signal)<treshold){
				count++;
				if (count>criteria){
					moving=false;
					myfile << time-criteria <<"\n";
				}
			}else
			count=0;
			
		}else{
			if (abs(signal)>treshold){
				moving=true;
				count=0;
				myfile << time <<"\t";
			}
		}
	
	    
    time++;	
	}
	if (moving)
		myfile << time-1;
    myfile.close();
return 0;
}
int main(){

	segmentacion("C:\\Users\\bicho\\Desktop\\derivada.txt","C:\\Users\\bicho\\Desktop\\segmentos.txt",5000,5);
	return 0;
}

