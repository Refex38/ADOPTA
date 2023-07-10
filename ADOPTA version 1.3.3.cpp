#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include <unistd.h>
#define BAR_SIZE 50
//Rafael Lopez Lara 182239
//Eric Leonardo Velazquez Hernandez 179798
//Proyecto Programacion I 
void portada(void);//prototipo portada;
void bienvenida(void);
void menu();
int crear_Registro(struct datos_Registro *datos, int n, int d, int m, int a);
void imprimir_por_edad(struct datos_Registro *datos, int *n);
void imprimir_por_nombre(struct datos_Registro *datos, int n);
void imprimir_por_esterilizado(struct datos_Registro *datos, int n);
void imprimir_por_adoptado(struct datos_Registro *datos, int n);
void imprimir_por_talla(datos_Registro *datos, int n, int opcTalla);
void adoptar(struct datos_Registro *datos, int n);
void actualiza_Registro(struct datos_Registro *datos, int n, int d, int m, int a); 
bool validarEnteros(char c[]);
bool validarCaracteres(char c[]);
void ficha_Adopcion(datos_Registro *datos, int id_Adopcion);
//Funcion gotoxy
void gotoxy(int x,int y){  
	COORD pos = {x, y};
   	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
} 
 
 typedef struct datos_Registro{
	int id;
	char nombre[10];
	int edad;
	int talla;
	int dia;
	int mes;
	int anio;
	int esterilizado;
	int adoptado;
}datos;
 
	
int main (){  //Funcion Main
	time_t tiempo;
	time(&tiempo);
	struct tm *tiempoActual = localtime(&tiempo);
 	int d = tiempoActual->tm_mday;
	int m = tiempoActual->tm_mon+1;
	int a = tiempoActual->tm_year+1900;
	
	
	datos_Registro datos[100];
	int numero_Registros = 0;
	int seleccion;
	bool salida;
	char sec[50];
	char dato[50];
	int n=0;
	int id_actual = 1;
	bool veri_Enteros;
	portada();
	printf("\n\n\n\n\n\n");
	system("pause");
	system("cls");
	bienvenida();
	system("pause");
	system("cls");
	do{
		int opc;
		salida=false;
		menu();
		do{
			veri_Enteros=false;
			fflush(stdin);
			scanf("%s", sec);
			veri_Enteros = validarEnteros(sec);
		}while(veri_Enteros==true);
		seleccion = atoi(sec);
		switch (seleccion){
			case 1:
				system("cls");
				n+= crear_Registro(datos, n, d, m, a);
				break;
			case 2:
			    do {
					system("cls");
			        printf("Seleccione una opcion:\n1.-Buscar por edad\n2.-Buscar por nombre\n3.-Buscar por esterilizacion\n4.-Buscar por adopcion\n5.-Regresar al menu principal\n");
			        do{
			        	fflush(stdin);
						scanf("%s", &dato);
					}while(validarEnteros(dato) == true);
					opc = atoi(dato);
			        switch (opc) {
			            case 1:
			                imprimir_por_edad(datos, &n);
			                system("pause");
			                break;
			            case 2:
			                imprimir_por_nombre(datos, n);
			                system("pause");
			                break;
			            case 3:
			                imprimir_por_esterilizado(datos, n);
			                system("pause");
			                break;
			            case 4:
			                imprimir_por_adoptado(datos, n);
			                system("pause");
			                break;
			            case 5:
			                break;
			            default:
			                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
			    	}
			    	
				} while (opc != 5);
				break;
			case 3:
				system("cls");
				actualiza_Registro(datos, n, d,m,a);
				break;
			case 4:
				if(n==0){
					printf("Aun no existen registros, intentelo de nuevo mas tarde\n");
					system("pause");
				}else{
					adoptar(datos, n);
				}
				break;
			case 5: 
				system("cls");
				salida=true;
				break;
			default:
				printf("Opcion no valida ingrese su selecion nuevamente\n");
		}
		system("cls");
	}while(salida==false);
	printf("Tenga un buen d%ca\n", 161);
	return 0;
}
//Funcion para la portada
void portada(void){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hConsole, 5);
    gotoxy(38,0);
	printf("Materia: ");
	SetConsoleTextAttribute (hConsole, 7);
	gotoxy(47,0);
	printf("Programacion 1\n");
	SetConsoleTextAttribute (hConsole, 5);
	gotoxy(44,1);
	printf("Grupo: ");
	SetConsoleTextAttribute (hConsole, 7);
	gotoxy(51,1);
	printf("T07F\n");
	SetConsoleTextAttribute (hConsole, 5);
	gotoxy(45,2);
	printf("Parcial: ");
	SetConsoleTextAttribute (hConsole, 7);
	gotoxy(54,2);
	printf("2\n");
	SetConsoleTextAttribute (hConsole, 5);
	gotoxy(41,3);
	printf("Fecha: ");
	SetConsoleTextAttribute (hConsole, 7);
	gotoxy(48,3);
	printf("14/04/2023\n");
	SetConsoleTextAttribute (hConsole, 5);
	gotoxy(37,4);
	printf("Alumnos: ");
	SetConsoleTextAttribute (hConsole, 7);
	gotoxy(45,4);
	printf("Rafael L%cpez Lara\n", 162);
	gotoxy(45,5);
	printf("Eric Leonardo Vel%czquez Hern%cndez", 160, 160);
	SetConsoleTextAttribute (hConsole, 5);
	gotoxy(41,6);
	printf("Matricula: ");
	SetConsoleTextAttribute (hConsole, 7);
	gotoxy(52,6);
	printf("182239 y 179798\n");
	SetConsoleTextAttribute (hConsole, 5);
	gotoxy(38,7);
	printf("Actividad: ");
	SetConsoleTextAttribute (hConsole, 7);
	gotoxy(49,7);
	printf("Proyecto final: ADOPTA \n");

}
void bienvenida(void){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(25, 4);
    printf("Bienvenido a \n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(25,6);
    printf("   / \\__\n");
    gotoxy(25,7);
    printf(" (    @\\___\n");
    gotoxy(25,8);
    printf(" /         O\n");
    gotoxy(25,9);
    printf("/   (_____/\n\n");
    gotoxy(25,11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("ADOPTA\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15 );

    
  gotoxy(0, 13);
    printf("Cargando...\n");


    for (int i = 0; i <= 100; i++) {
        gotoxy(50, 15);
        printf("\r[");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // Cambiar el color del texto a rojo
        for (int j = 0; j < i * BAR_SIZE / 100; j++) {
            printf("=");
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Restablecer el color del texto
        for (int j = i * BAR_SIZE / 100; j < BAR_SIZE; j++) {
            printf(" ");
        }
        printf("] %d%%", i);
        fflush(stdout);
        usleep(5000);
    }
    gotoxy(50, 15);
    printf("\r[");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Cambiar el color del texto a verde
    for (int j = 0; j < BAR_SIZE; j++) {
        printf("=");
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Restablecer el color del texto
    printf("] 100%%");
    fflush(stdout);
    printf("\n\n");
    gotoxy(0, 18);
    printf("Carga completa!");
    printf("\n\n");
    gotoxy(0, 21);
    printf("Disrute de su instancia\n");

}
void menu ( ){  //Funcion para mostrar el menu sin pedir datos
	printf("\n");
	printf("----------MENU----------\n");
	printf("1.- Crear registro\n2.- Consultar registro\n3.- Actualizar registro\n");
	printf("4.- Adopcion\n5.- Salir\n");
	printf("------------------------\n");
}
int crear_Registro(struct datos_Registro *datos, int n, int d, int m, int a){
	int val, num, cant=1;
	char dato[50];
	bool ver, retorno;
	val = n;
	do{
		datos[val].dia = d;
	    datos[val].mes = m;
	    datos[val].anio = a;
		datos[val].id = val+1;
        printf("Ingrese el nombre del perrito %d\n", val+1);
        int solo_letras;
	    do {
	        solo_letras = 1;
	        scanf("%s", dato); 
	        for (int j = 0; dato[j] != '\0'; j++) {
	            if (!isalpha(dato[j])) { 
	                solo_letras = 0; 
	                break;
	            }
	        }
	        if (!solo_letras) {
	            printf("El nombre solo debe de contener letras (sin acentos). Intentalo de nuevo.\n");
	        }
	        if(strlen(dato)>10){
				printf("El nombre no debe de contener mas de 10 caracteres\n");
				solo_letras = 0;
			}
	    } while (!solo_letras);
		strcpy(datos[val].nombre, dato);
	    printf("Ingrese la edad del perrito: ");
	    do{
			fflush(stdin);
			scanf("%s", &dato);
			ver = validarEnteros(dato);
			datos[val].edad = atoi(dato);
			if(datos[val].edad<1 || datos[val].edad>25){
				printf("Ingrese una edad valida\n");
				ver =true;
			}
		}while( ver == true);
	    printf("Ingrese la talla del perrito:  \n1.-Grande\n2.-Mediano\n3.-Chico\n");
	    do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			datos[val].talla = atoi(dato);
			if(datos[val].talla != 1 && datos[val].talla !=2 && datos[val].talla !=3){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
		}while(ver==true);
	    printf("Ingrese si el perrito esta esterilizado \n1.-Esta esterilizado\n2.-No esta esterilizado\n");
	    do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			datos[val].esterilizado = atoi(dato);
			if(datos[val].esterilizado != 1 && datos[val].esterilizado !=2){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
		}while(ver==true);
	    printf("Ingrese si el perrito esta adoptado \n1.-Esta adoptado\n2.-No esta adoptado\n");
	    do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			datos[val].adoptado = atoi(dato);
			if(datos[val].adoptado != 1 && datos[val].adoptado !=2){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
		}while(ver==true);
		do{
			ver = false;
	    	printf("1.- Registrar otro perrito\n2.- Regresar al menu\n");
	    	fflush(stdin);
			scanf("%s", &dato);
			ver = validarEnteros(dato);
			num = atoi(dato);
			if(num != 1 && num !=2){
				printf("Ingrese un dato valido\n");
				ver= true;
			}
		}while(ver == true);
		if(num == 1){
			retorno = true;
    		val++;
    		cant++;
		}else{
			retorno = false;
		}
    	system("cls");
	}while(retorno == true);
	return cant;
}
void imprimir_por_edad(struct datos_Registro *datos, int *n) {
    int age, val1;
    bool ver2, ver;
    char dato[50], nombreP[11];
    val1= *n;
    printf("Ingrese la edad del perrito a buscar: ");
    do{
			fflush(stdin);
			scanf("%s", &dato);
			ver = validarEnteros(dato);
			age = atoi(dato);
			if( age<1 || age>25){
				printf("Ingrese una edad valida\n");
				ver =true;
			}
		}while( ver == true);
    ver2=false;
    for (int i = 0; i < val1; i++) {
    	char nombre[10];
        if ( datos[i].edad == age ){
            printf("ID: %d\n", datos[i].id);
            fflush(stdin);
			strcpy(nombreP, datos[i].nombre);
            printf("Nombre: %s\n", nombreP);
            printf("Edad: %d\n", datos[i].edad);
            printf("Talla: ");
            if(datos[i].talla == 1){
            	printf("Grande\n");
			}
			if(datos[i].talla == 2){
            	printf("Mediano\n");
			}
			if(datos[i].talla == 3){
            	printf("Chico\n");
			}
            printf("Fecha de registro: %02d/%02d/%d \n", datos[i].dia, datos[i].mes, datos[i].anio);
            printf("Esterilizado: %s\n", datos[i].esterilizado == 1 ? "Si" : "No");
            printf("Adoptado: %s\n", datos[i].adoptado == 1 ? "Si" : "No");
            printf("\n\n");
            ver2=true;
        }
    }
    if(ver2==false){
    	printf("Perrito no encontrado\n");
	}
}
void imprimir_por_nombre(datos_Registro *datos, int n) {
    char nombre[20], dato[50], nombreP[11], nombreP2[11];
    bool ver2;
    printf("Ingrese el nombre del perrito a buscar: ");
    int solo_letras;
	    do {
	        solo_letras = 1;
	        scanf("%s", dato); 
	        for (int j = 0; dato[j] != '\0'; j++) {
	            if (!isalpha(dato[j])) { 
	                solo_letras = 0; 
	                break;
	            }
	        }
	        if (!solo_letras) {
	            printf("El nombre solo debe de contener letras (sin acentos). Intentalo de nuevo.\n");
	        }
	        if(strlen(dato)>10){
				printf("El nombre no debe de contener mas de 10 caracteres\n");
				solo_letras = 0;
			}
	    } while (!solo_letras);
	    for (int indice = 0; dato[indice] != '\0'; ++indice){
			dato[indice] = tolower(dato[indice]);
		}
		strcpy(nombre, dato);
    for (int i = 0; i < n; i++) {
    	strcpy(nombreP2, datos[i].nombre);
    	for (int indice = 0; nombreP2[indice] != '\0'; ++indice){
			nombreP2[indice] = tolower(nombreP2[indice]);
		}
        if (strcmp(nombre, nombreP2) == 0) {
            printf("ID: %d\n", datos[i].id);
            strcpy(nombreP, datos[i].nombre);
            printf("Nombre: %s \n", nombreP);
            printf("Edad: %d\n", datos[i].edad);
            printf("Talla: ");
            if(datos[i].talla == 1){
            	printf("Grande\n");
			}
			if(datos[i].talla == 2){
            	printf("Mediano\n");
			}
			if(datos[i].talla == 3){
            	printf("Chico\n");
			}
            printf("Fecha de registro: %02d/%02d/%d \n", datos[i].dia, datos[i].mes, datos[i].anio);
            printf("Esterilizado: %s\n", datos[i].esterilizado == 1 ? "Si" : "No");
            printf("Adoptado: %s\n", datos[i].adoptado == 1 ? "Si" : "No");
            ver2=true;
        }
    }
    if(ver2==false){
    	printf("Perrito no encontrado\n");
	}
}
void imprimir_por_esterilizado(datos_Registro *datos, int n) {
    int esterilizado;
    bool ver2, ver;
    char nombreP[11], dato[50];
    printf("Ingrese 1 si quiere ver los perritos esterilizados o 2 si quiere ver los no esterilizados: ");
    do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			esterilizado = atoi(dato);
			if(esterilizado!= 1 && esterilizado !=2){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
	}while(ver==true);
    for (int i = 0; i < n; i++) {
        if (datos[i].esterilizado == esterilizado) {
            printf("ID: %d\n", datos[i].id);
           	strcpy(nombreP, datos[i].nombre);
            printf("Nombre: %s\n", nombreP);
            printf("Edad: %d\n", datos[i].edad);
            printf("Talla: ");
            if(datos[i].talla == 1){
            	printf("Grande\n");
			}
			if(datos[i].talla == 2){
            	printf("Mediano\n");
			}
			if(datos[i].talla == 3){
            	printf("Chico\n");
			}
            printf("Fecha de registro: %02d/%02d/%d \n", datos[i].dia, datos[i].mes, datos[i].anio);
            printf("Esterilizado: %s\n", datos[i].esterilizado == 1 ? "Si" : "No");
            printf("Adoptado: %s\n", datos[i].adoptado == 1 ? "Si" : "No");
            ver2=true;
        }
    }
    if(ver2==false){
    	printf("Perrito no encontrado\n");
	}
}
void imprimir_por_adoptado(datos_Registro *datos, int n) {
    int adoptado;
    bool ver2, ver;
    char dato[50], nombreP[11];
    printf("Ingrese 1 si quiere ver los perritos adoptados o 2 si quiere ver los no adoptados: ");
   do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			adoptado = atoi(dato);
			if(adoptado!= 1 && adoptado !=2){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
	}while(ver==true);
    for (int i = 0; i < n; i++) {
        if (datos[i].adoptado == adoptado) {
            printf("ID: %d\n", datos[i].id);
            strcpy(nombreP, datos[i].nombre);
            printf("Nombre: %s\n", nombreP);
            printf("Edad: %d\n", datos[i].edad);
            printf("Talla: ");
            if(datos[i].talla == 1){
            	printf("Grande\n");
			}
			if(datos[i].talla == 2){
            	printf("Mediano\n");
			}
			if(datos[i].talla == 3){
            	printf("Chico\n");
			}
            printf("Fecha de registro: %02d/%02d/%d \n", datos[i].dia, datos[i].mes, datos[i].anio);
            printf("Esterilizado: %s\n", datos[i].esterilizado == 1 ? "Si" : "No");
            printf("Adoptado: %s\n", datos[i].adoptado == 1 ? "Si" : "No");
            ver2=true;
        }
    }
    if(ver2==false){
    	printf("Perrito no encontrado\n");
	}
}
void imprimir_por_talla(datos_Registro *datos, int n, int opcTalla) {
	bool ver2;
    for (int i = 0; i < n; i++) {
        if (datos[i].talla == opcTalla) {
            printf("ID: %d\n", datos[i].id);
            printf("Nombre: %s\n", &datos[i].nombre);
            printf("Edad: %d\n", datos[i].edad);
            printf("Talla: ");
            if(datos[i].talla == 1){
            	printf("Grande\n");
			}
			if(datos[i].talla == 2){
            	printf("Mediano\n");
			}
			if(datos[i].talla == 3){
            	printf("Chico\n");
			}
            printf("Fecha de registro: %02d/%02d/%d \n", datos[i].dia, datos[i].mes, datos[i].anio);
            printf("Esterilizado: %s\n", datos[i].esterilizado == 1 ? "Si" : "No");
            printf("Adoptado: %s\n", datos[i].adoptado == 1 ? "Si" : "No");
            ver2=true;
        }
    }
    if(ver2==false){
    	printf("Perrito no encontrado\n");
	}
}			
void adoptar(datos_Registro *datos, int n){
	int opcAdopcion, continuar, id_Adopcion;
	bool salida, ver2, salida2;
	char dato[50];
	int opcTalla;
	do{
		system("cls");
		salida=false;
		salida2=false;
		printf("\n");
		printf("----------A D O P C I O N----------\n");
		printf("1.- Talla \n2.- Edad\n3.- Regresar al menu\n");
		printf("------------------------\n");
		do{
			ver2=false;
			scanf("%s", &dato);
			ver2=validarEnteros(dato);
			opcAdopcion = atoi(dato);
			if(opcAdopcion !=1 && opcAdopcion !=2 && opcAdopcion !=3){
				printf("Ingrese solamente una de las opciones anteriores\n");
				ver2=true;
			}
		}while( ver2 == true);
		switch(opcAdopcion){
			case 1:
				printf("\n");
				printf("----------A D O P C I O N----------\n");
				printf("1.- Grande\n2.- Mediano\n3.- Chico\n");
				printf("------------------------\n");
				do{
					ver2 = false;
					scanf("%s", &dato);
					ver2=validarEnteros(dato);
					opcTalla = atoi(dato);
					if(opcTalla<1 && opcTalla>3){
						ver2=true;
					}
				}while( ver2 == true);
				imprimir_por_talla(datos, n, opcTalla);
				printf("----------A D O P C I O N----------\n");
				printf("1.- Continuar con la adopcion \n2.- Volver a consultar\n");
				printf("------------------------\n");
				do{
					scanf("%s", &dato);
				}while(validarEnteros(dato) == true);
				continuar = atoi(dato);
				switch(continuar){
					case 1:
						system("cls");
						break;
					case 2:
						salida=true;
						break;
					default:
						printf("Ingrese solamente una de las opciones anteriores\n");
				}
				break;
			case 2:
				imprimir_por_edad(datos, &n);
				printf("----------A D O P C I O N----------\n");
				printf("1.- Continuar con la adopcion \n2.- Volver a consultar\n");
				printf("------------------------\n");
				do{
					scanf("%s", &dato);
				}while(validarEnteros(dato) == true);
				continuar = atoi(dato);
				switch(continuar){
					case 1:
						system("cls");
						break;
					case 2:
						salida=true;
						break;
					default:
						printf("Ingrese solamente una de las opciones anteriores\n");
				}
				break;
			case 3:
				salida2=true;
				break;
			default:
				printf("Ingrese solamente una de las opciones anteriores\n");
		}
	}while(salida==true && salida2==false);
	
	if(salida2==false){
		bool ver3;
		printf("Ingrese el ID del perrito a adoptar\n");
		do{
			char salir[] = "R";
			ver3=true;
			do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato)==true);
			id_Adopcion = atoi(dato);
			for(int i=0; i<n; i++){
				if(datos[i].id == id_Adopcion){
					ver3=false;
				}
			}
			if(ver3==true){
				printf("ID no encontrado\n");
			}
		}while(ver3==true);
		do{
			ver2=true;
			for (int i = 0; i < n; i++) {
		        if (datos[i].id == id_Adopcion){
		            printf("ID: %d\n", datos[i].id);
		            printf("Nombre: %s\n", &datos[i].nombre);
		            printf("Edad: %d\n", datos[i].edad);
		            printf("Talla: ");
		            if(datos[i].talla == 1){
		            	printf("Grande\n");
					}
					if(datos[i].talla == 2){
		            	printf("Mediano\n");
					}
					if(datos[i].talla == 3){
		            	printf("Chico\n");
					}
		            printf("Fecha de registro: %02d/%02d/%d \n", datos[i].dia, datos[i].mes, datos[i].anio);
		            printf("Esterilizado: %s\n", datos[i].esterilizado == 1 ? "Si" : "No");
		            printf("Adoptado: %s\n", datos[i].adoptado == 1 ? "Si" : "No");
		            ver2=false;
		        }
	    	}
	    	if(ver2==true)
	    		printf("Ingrese un id valido\n");
		}while(ver2==true);
	    system("pause");
	    ficha_Adopcion(datos, id_Adopcion);
	}
}
void actualiza_Registro(datos_Registro *datos, int n, int d, int m, int a){
	int num;
	char dato[50];
	bool ver, verId;
	
    do{
    	verId=false;
	    printf("Ingrese el ID a modificar\n");
	    do{
	    	fflush(stdin);
			scanf("%s", &dato);
		}while(validarEnteros(dato) == true);
		num = atoi(dato);
		for(int i=0; i<n; i++){
			if(datos[i].id==num){
				verId = true;
			}
		}
		if(verId==false){
			printf("ID no encontrada vuelva a intentarlo\n");
		}
	}while(verId==false);
	datos[num-1].dia = d;
	datos[num-1].mes = m;
	datos[num-1].anio = a;
        printf("Ingrese el nombre del perrito %d\n", num);
        int solo_letras;
	    do {
	        solo_letras = 1;
	        scanf("%s", dato); 
	        for (int j = 0; dato[j] != '\0'; j++) {
	            if (!isalpha(dato[j])) { 
	                solo_letras = 0; 
	                break;
	            }
	        }
	        if (!solo_letras) {
	            printf("El nombre debe de contener solo letras(sin acentos). Intentalo de nuevo.\n");
	        }
	        if(strlen(dato)>10){
				printf("El nombre no debe de contener mas de 10 caracteres\n");
				solo_letras = 0;
			}
	    } while (!solo_letras);
		strcpy(datos[num-1].nombre, dato);
	    do{
			fflush(stdin);
			scanf("%s", &dato);
			ver = validarEnteros(dato);
			datos[num-1].edad = atoi(dato);
			if(datos[num-1].edad<1 || datos[num-1].edad>25){
				printf("Ingrese una edad valida\n");
				ver =true;
			}
		}while( ver == true);
	    printf("Ingrese la talla del perrito:  \n1.-Grande\n2.-Mediano\n3.-Chico\n");
	    do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			datos[num-1].talla = atoi(dato);
			if(datos[num-1].talla != 1 && datos[num-1].talla !=2 && datos[num-1].talla !=3){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
		}while(ver==true);
	    printf("Ingrese si el perrito esta esterilizado \n1.-Esta esterilizado\n2.-No esta esterilizado\n");
	    do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			datos[num-1].esterilizado = atoi(dato);
			if(datos[num-1].esterilizado != 1 && datos[num-1].esterilizado !=2){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
		}while(ver==true);
	    printf("Ingrese si el perrito esta adoptado \n1.-Esta adoptado\n2.-No esta adoptado\n");
	    do{
		    ver=false;
	    	do{
				fflush(stdin);
				scanf("%s", &dato);
			}while(validarEnteros(dato) == true);
			datos[num-1].adoptado = atoi(dato);
			if(datos[num-1].adoptado != 1 && datos[num-1].adoptado !=2){
				printf("Ingrese un dato valido\n");
				ver=true;
			}
		}while(ver==true);
}
bool validarEnteros(char c[]){
	bool ver;
	ver=false;
	for(int i=0; i<strlen(c); i++){
		if(isdigit(c[i])==0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("Error: valor no valido\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			ver=true;
			break;
		}
	}
	return ver;
}
bool validarCaracteres(char c[]){
	bool ver;
	ver=false;
	for(int i=0; i<strlen(c); i++){
		if(isalpha(c[i]) == 0 && c[i] != ' '){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("Error: valor no valido\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			ver=true;
			break;
		}
	}
	return ver;
}
void ficha_Adopcion(datos_Registro *datos, int id_Adopcion){
	char nombre_Archivo[40], nombre[10], apellido[40], domicilio[100], dato[50];
	char tipoArchivo[] = ".txt";
	int edad;
	int solo_letras;
	bool ver;
	printf("Solicitud de adopcion aceptada\n");
	printf("Por favor ingrese los siguientes datos:\n");
	printf("Nombre: \n");
	do {
	    solo_letras = 1;
	    scanf("%s", nombre); 
	    for (int j = 0; nombre[j] != '\0'; j++) {
	        if (!isalpha(nombre[j])) { 
	            solo_letras = 0; 
	            break;
	        }
	    }
	    if (!solo_letras) {
	        printf("Ingrese solo letras.\n");
	    }
	} while (!solo_letras);
	printf("Apellido paterno: \n");
	do {
	    solo_letras = 1;
	    scanf("%s", apellido); 
	    for (int j = 0; apellido[j] != '\0'; j++) {
	        if (!isalpha(apellido[j])) { 
	            solo_letras = 0; 
	            break;
	        }
	    }
	    if (!solo_letras) {
	        printf("Ingrese solo letras.\n");
	    }
	} while (!solo_letras);
	printf("Edad: \n");
	do{
		ver=false;
		fflush(stdin);
		scanf("%s", &dato);
		ver = validarEnteros(dato);
		edad = atoi(dato);
		if(edad<18){
			printf("Debes ser mayor de edad para poder adoptar a un perrito\n");
			ver=true;
		}
	}while( ver == true);
	printf("Domicilio: \n");
	scanf("%s", domicilio);
	strcat(strcpy(nombre_Archivo,apellido), tipoArchivo);
	
	FILE *fichero;
	fichero = fopen(nombre_Archivo, "rt");
	if(fichero == NULL){
		fichero = fopen(nombre_Archivo, "w");
	}else{
		fichero = fopen(nombre_Archivo, "r+");
	}
	fprintf(fichero, "\n\n-----FICHA DE ADOPCION-----\n");
	fprintf(fichero, "Nombre del perrito: %s\n", datos[id_Adopcion-1].nombre);
	fprintf(fichero, "Edad: %d\n", datos[id_Adopcion-1].edad);
	fprintf(fichero, "Talla: ");
	if(datos[id_Adopcion-1].talla == 1){
	    fprintf(fichero, "Grande\n");
	}
	if(datos[id_Adopcion-1].talla == 2){
	    fprintf(fichero, "Mediano\n");
	}
	if(datos[id_Adopcion-1].talla == 3){
	    fprintf(fichero, "Chico\n");
	}
	fprintf(fichero, "Esterilizado: %s\n", datos[id_Adopcion-1].esterilizado == 1 ? "Si" : "No");
	fprintf(fichero, "Nombre completo del dueño: %s %s\n", nombre, apellido);
	fprintf(fichero, "Edad: %d\n", edad);
	fprintf(fichero, "Domicilio: %s\n", domicilio);
	fclose(fichero);
	system("cls");
	
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(25,6);
    printf("   / \\__\n");
    gotoxy(25,7);
    printf(" (    @\\___\n");
    gotoxy(35,7);
    printf("WOOF!!");
    gotoxy(25,8);
    printf(" /         O\n");
    gotoxy(25,9);
    printf("/   (_____/\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	printf("Adopcion completada, consulte la ficha generada\n");
	system("pause");
}
