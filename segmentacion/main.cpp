#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//La funcion segmentacion abre el archivo que se encuentra en la direccion 'datos' el cual debe ser la derivada de accX^2+accY^2 
//(yo utilice una derivada con un suavizado Savgol de orden polinomial 2 con una ventana de 3 puntos del paquete scipy.signal.savgol de python)
// y crea un archivo con dos columnas que indican correspondientemente los índices del inicio y el final de un evento de movimiento

int segmentacion(string datos, string resultado, int criteria, int tresholds, float tresholdf) {
	bool moving=false;
	//datos y resultado son las direcciones de los archivos cuyos datos quiere segmentar y donde desea almacenar los segmentos respectivamente
	//criteria indica cuantos pasos sin movimiento deben existir para marcar el fin de un evento
	//criteria tambien indica la longitud minima para ser considerado evento
	//tresholds es la amplitud mínimo que debe tener la derivada para marcar el inicio de un evento 
	//si trancurren un número de puntos igual a criteria con una amplitud menor a tresholdf, se marca el fin de un evento en t-criteria
	int eventos=0;
	int count = 0;
	float signal;
	int temp=0;
	ifstream inFile;
	inFile.open(datos);
	ofstream myfile;
  	myfile.open (resultado);
  	int time = 0;
  
	 while (inFile >> signal) {
    	if (moving){
			if (abs(signal)<tresholdf){
				count++;
				if (count>criteria){
					moving=false;					
					if (time-criteria-temp>=criteria){
						eventos++;
						myfile << temp <<"\t"<< time-criteria <<"\n";
					}
				}
			}else
			count=0;
			
		}else{
			if (abs(signal)>tresholds){
				moving=true;
				count=0;
				temp=time;
				
			}
		}
	
	    
    time++;	
	}
	if (moving)
		myfile << temp <<"\t"<< time-criteria <<"\n";
    myfile.close();
return eventos;
}

int main(){
	vector<string> datos={"2020-11-29T133.txt",
"2020-11-29T169.txt",
"2020-11-29T30.txt",
"2020-11-30T11.txt",
"2020-11-30T133.txt",
"2020-11-30T169.txt",
"2020-11-30T30.txt",
"2020-12-01T133.txt",
"2020-12-01T169.txt",
"2020-12-01T30.txt",
"2020-12-02T133.txt",
"2020-12-02T169.txt",
"2020-12-02T30.txt",
"2020-12-03T133.txt",
"2020-12-03T169.txt",
"2020-12-03T30.txt",
"2021-01-10T10.txt",
"2021-01-10T129.txt",
"2021-01-10T79.txt",
"2021-01-11T10.txt",
"2021-01-11T129.txt",
"2021-01-11T79.txt",
"2021-01-12T10.txt",
"2021-01-12T30-2021.txt",
"2021-01-12T79.txt",
"2021-01-13T10.txt",
"2021-01-13T129.txt",
"2021-01-13T30-2021.txt",
"2021-01-13T79.txt",
"2021-01-14T10.txt",
"2021-01-14T30-2021.txt",
"2021-01-14T79.txt",
"2021-01-15T129.txt",
"2021-01-15T30-2021.txt","2021-01-15T79.txt"};
for (string dato : datos)
	cout << segmentacion("C:\\Users\\bicho\\OneDrive\\Documentos\\Balseiro\\maestria\\SensoresInercialesNovDic2020\\derivadas xy\\"+dato,"C:\\Users\\bicho\\OneDrive\\Documentos\\Balseiro\\maestria\\SensoresInercialesNovDic2020\\segmentos xy2\\"+dato,40,200000,650000)<<endl;
return 1;	
}

