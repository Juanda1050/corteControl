//Juan Daniel González Alejandre 1901711 
#include <stdio.h>
#include <windows.h>
#include <conio.h> 
#include <string.h> 

void gotoxy(short x, short y) 
{
   COORD pos = {x, y};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

#define CIERTO 1
#define FALSO 0
#define CUENTA_MINIMA 100
#define CUENTA_MAXIMA 999
#define PARTIDA_MINIMA 1
#define PARTIDA_MAXIMA 100
#define LONGITUD_CUENTA 3
#define LONGITUD_SERVICIO 40
#define LONGITUD_DESCRIPCION 80
#define LONGITUD_CANTIDAD 30
#define LONGITUD_PRECIO 15
 
typedef struct{
 		      long int Cuenta_e;
 		      int Partida_e;
 		      char Servicio_e[LONGITUD_SERVICIO+1];
 		      char Descripcion_e[LONGITUD_DESCRIPCION+1];
 		      float Cantidad_e;
		      float Precio_e;
        } regCuenta;

typedef struct{
		      long int Cuenta_s;
		      int Partida_s;
 		      char Servicio_s[LONGITUD_SERVICIO+1];	
 		      char Descripcion_s[LONGITUD_DESCRIPCION+1];
 		      float Cantidad_s;
			  float Subtotal_s;
			  float IVA_s;	 
		      float Total_s;
        } regTotal; 
        
FILE *ptfEntrada, *ptfSalida;

regCuenta vtrEntrada;
regTotal vtrSalida;

void vCICLO_MENU();
void vINICIAR();
void vALTAS( regCuenta vtrEntrada );
long int liCAPTURAR_CUENTA();
int iCAPTURAR_PARTIDA();
char cCAPTURAR_SERVICIO(char ServicioReceptor[], char ServicioLocal[]);
char cCAPTURAR_DESCRIPCION(char DescripcionReceptor[], char DescripcionLocal[]);
float fCAPTURAR_CANTIDAD();
float fCAPTURAR_PRECIO();
void vREPORTE( regCuenta vtrEntrada, regTotal vtrSalida);
void vIMPRIME( regTotal vtrSalida);
int iSELECCIONA_OPCION( int OpcionMenor , int OpcionMayor );
void ORDENAR_REGISTROS( regCuenta vtrEntrada );
void vARCHIVO_HACIA_ARREGLOS();
void vORDENAMIENTO( long int auC_t[], int auP_t[], char auS_t[][LONGITUD_SERVICIO], char auD_t[][LONGITUD_DESCRIPCION], float auCant_t[], float auPrecio_t[], int R );	
void vARREGLO_HACIA_ARCHIVO( long int auC_t[], int auP_t[], char auS_t[][LONGITUD_SERVICIO], char auD_t[][LONGITUD_DESCRIPCION], float auCant_t[], float auPrecio_t[], int R, regCuenta vtrEntrada );

main()
{		
   vCICLO_MENU();
}

void vCICLO_MENU()
{
   int OpcionMenu;
   int OpcionMenor = 1, OpcionMayor = 4;  
   do{
     printf("M E N U   P R I N C I P A L\n");
	 printf("1. INICIAR \n");
     printf("2. ALTAS \n");
     printf("3. REPORTE \n");
	 printf("4. SALIDA \n");
     printf("Cual opcion deseas? : ");
     OpcionMenu = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );   
	 switch( OpcionMenu )
	 {
	    case 1:
		      /* borra el archivo de entrada anterior, si se desea */
		    	system("cls");
		      vINICIAR();
		      break;
	    case 2:
              /* altas de registros */
              system("cls");
		      vALTAS(vtrEntrada);
		      break;
	    case 3:
              /* da el resultado del proceso */
		      vREPORTE(vtrEntrada, vtrSalida);
              break;
        case 4:
              printf("Gracias por su registro.\n");                      		  
              system("pause");
              break;
        default:
              printf("La opci%cn elegida no est%c disponible\n", 162, 160);
              printf("El programa concluir%c su funci%cn\n", 160, 162);             
              system("pause");
              break;              
	 }
   }while( OpcionMenu >= OpcionMenor && OpcionMenu < OpcionMayor );
}

int iSELECCIONA_OPCION( int LimiteMenor , int LimiteMayor )
{
   int OpcionSeleccionada;
   char Opcion[2];        
   	   
   do{
      scanf( "%s", Opcion );  
      OpcionSeleccionada = atoi( Opcion );
      if( OpcionSeleccionada == FALSO )
      {
          printf("La opcion seleccionada NO ES CORRECTA !!!\n");
          printf("El rango de opciones es de %d a %d, favor de intentar de nuevo \n", LimiteMenor, LimiteMayor );          
      }    
      else
      {
         if( OpcionSeleccionada < LimiteMenor || OpcionSeleccionada > LimiteMayor )
         {
            printf("La opcion seleccionada NO ES CORRECTA !!!\n");
            printf("El rango de opciones es de %d a %d, favor de intentar de nuevo \n", LimiteMenor, LimiteMayor );
         }
      }  
   }while( OpcionSeleccionada < LimiteMenor || OpcionSeleccionada > LimiteMayor );
   return(OpcionSeleccionada);
}

void vINICIAR()
{
   int OpcionMenor = 1, OpcionMayor = 2;     
   int Opcion;    
     
   printf( "INICIAR\n" );
   printf( "Esta rutina DESTRUYE el archivo de entrada anterior !!!!\n" );
   printf( "Deseas DESTRUIRLO?\nPresione: 1.SI; 2.NO : " );
   Opcion = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );
   if( Opcion == CIERTO )
   {
      ptfEntrada = fopen("c:Ordinario1901711.dat","r");  /* abrir archivo de entrada */
      if( ptfEntrada == NULL )
      {
	      printf( "No puedo DESTRUIR el archivo porque NO existe \n" );
	      system( "pause" );
	      system("cls");
       }
       else
       {
	      fclose( ptfEntrada );
          /* borra archivo */
	      remove("c:Ordinario1901711.dat");
	      system("cls");
       } /* fin  if(ptfentrada == NULL) */
    } /* fin if(Opcion == CIERTO) */
} 

void vALTAS( regCuenta vtrEntrada )
{
   int Continuar, OpcionMenor = 1, OpcionMayor = 2;
   
   ptfEntrada = fopen("c:Ordinario1901711.dat","a+");
   if( ptfEntrada == NULL)
   {
      printf( "El archivo de entrada NO existe ; favor de revisar su proceso \n" );
   } 

   if( ptfEntrada != NULL)
   {
      do{
      	system("cls");
	      printf( "ALTAS \n" );
          vtrEntrada.Cuenta_e = liCAPTURAR_CUENTA();
          vtrEntrada.Partida_e = iCAPTURAR_PARTIDA();
          cCAPTURAR_SERVICIO(vtrEntrada.Servicio_e, vtrEntrada.Servicio_e);		  	      
          cCAPTURAR_DESCRIPCION(vtrEntrada.Descripcion_e, vtrEntrada.Descripcion_e);
          vtrEntrada.Cantidad_e = fCAPTURAR_CANTIDAD();
          vtrEntrada.Precio_e = fCAPTURAR_PRECIO();
	      fwrite(&vtrEntrada, sizeof(regCuenta), 1, ptfEntrada);
	      printf( "¿Deseas continuar?\nPresione: 1.SI; 2.NO : " );
          Continuar = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );	      
      }while( Continuar == 1 );
   } 
   fclose(ptfEntrada);
   system("cls");
}

long int liCAPTURAR_CUENTA()
{	
   long int CuentaLocal;
   char CuentaCadena[LONGITUD_CUENTA];	   
      
   do{
		printf("Captura el n%cmero de comanda: ", 163);     
        scanf(" %[^\n]",CuentaCadena);
		CuentaLocal = atol(CuentaCadena);
        if( CuentaLocal == 0 || CuentaLocal < CUENTA_MINIMA || CuentaLocal > CUENTA_MAXIMA )
        {
        	printf( "El dato capturado para el n%cmero de comanda no cumple con los requisitos \n", 163);
        	printf( "Capture un dato con %d d%cgitos, entre %d y %d \n",LONGITUD_CUENTA, 161, CUENTA_MINIMA, CUENTA_MAXIMA); 			       	
        	strset( CuentaCadena, ' ' );   
		}
   }while( CuentaLocal == 0 || CuentaLocal < CUENTA_MINIMA || CuentaLocal > CUENTA_MAXIMA );
return( CuentaLocal );
} 

int iCAPTURAR_PARTIDA(){
	int PartidaLocal;
	char PartidaCadena[LONGITUD_CUENTA];
	
	do{
		printf("Captura el n%cmero de partida: ", 163);
		scanf(" %[^\n]",PartidaCadena);
		PartidaLocal = atoi(PartidaCadena);
		if(PartidaLocal == 0 || PartidaLocal < PARTIDA_MINIMA || PartidaLocal > PARTIDA_MAXIMA){
			printf("El dato capturado para el n%cmero de partida no cumple con los requisitos \n", 163);
			printf("Capture un dato %d d%cgitos, entre %d y %d \n", LONGITUD_CUENTA, 161, PARTIDA_MINIMA, PARTIDA_MAXIMA);
			strset(PartidaCadena, ' ');
		}
	}while(PartidaLocal == 0 || PartidaLocal < PARTIDA_MINIMA || PartidaLocal > PARTIDA_MAXIMA);
	return (PartidaLocal);
}

char cCAPTURAR_SERVICIO(char ServicioReceptor[], char ServicioLocal[])
{
   int Longitud, NoCumple, i;
   	   
   do{
   	  NoCumple = FALSO; 
      printf("Captura el nombre del servicio: ");     
      scanf(" %[^\n]",ServicioLocal);
      Longitud = strlen( ServicioLocal );
      if( Longitud < 1 || Longitud > LONGITUD_SERVICIO || NoCumple == CIERTO )
      {
         printf( "El dato capturado para el nombre del servicio no cumple con los requisitos \n");
         printf( "Capture un dato con hasta %d letras y espacios en blanco \n", LONGITUD_SERVICIO );
         strset( ServicioLocal, ' ' );
      }
   } while( Longitud < 1 || Longitud > LONGITUD_SERVICIO || NoCumple == CIERTO );
   return(ServicioLocal[LONGITUD_SERVICIO]);	   
} 

char cCAPTURAR_DESCRIPCION(char DescripcionReceptor[], char DescripcionLocal[]){
	int Longitud, NoCumple, i;
	
	do{
		NoCumple = FALSO;
		printf("Captura la descripci%cn del servicio: ", 162);
		scanf(" %[^\n]", DescripcionLocal);
		Longitud = strlen(DescripcionLocal);
		for( i = 0; i < Longitud; i++ ){
         	if( ! ( isalpha(DescripcionLocal[i]) || isspace(DescripcionLocal[i]) ) ){
	       NoCumple = CIERTO;
         }
      }
		if ( Longitud < 1 || Longitud > LONGITUD_DESCRIPCION || NoCumple == CIERTO ){
			printf("El dato capturado para la descripci%cn no cumple con los requisitos \n", 162);
			printf("Capture un dato con hasta %d letras y espacios en blanco \n", LONGITUD_DESCRIPCION);
			strset( DescripcionLocal, ' ' );
		}
	}while( Longitud < 1 || Longitud > LONGITUD_DESCRIPCION || NoCumple == CIERTO );
		return(DescripcionLocal[LONGITUD_DESCRIPCION]);
}

float fCAPTURAR_CANTIDAD(){
	float CantidadLocal;
	char CantidadCadena[LONGITUD_CANTIDAD];
	
	do{
		printf("Capture la cantidad de producto que desea: ");
		scanf(" %[^\n]",CantidadCadena);
		CantidadLocal = atof(CantidadCadena);
		if( CantidadLocal == 0 ){
			printf("El dato capturado para la cantidad de producto no cumple los requisitos \n");
			printf("Capture otro dato \n");
			strset(CantidadCadena, ' ');
		}
	}while(CantidadLocal == 0);
	return(CantidadLocal);
}

float fCAPTURAR_PRECIO()
{	
   float PrecioLocal;
   char PrecioCadena[LONGITUD_PRECIO];	   
     
   do{
		printf("Captura el precio unitario: ");     
        scanf(" %[^\n]",PrecioCadena);
		PrecioLocal = atof(PrecioCadena);	
        if( PrecioLocal == 0 )
        {
        	printf( "El dato capturado para el precio unitario no cumple con los requisitos \n", 162);
        	printf( "Capture otro dato \n"); 			       	
        	strset( PrecioCadena, ' ' ); 
		}
   }while( PrecioLocal == 0 );
return( PrecioLocal );
}

void vREPORTE( regCuenta vtrEntrada, regTotal vtrSalida )
{
    long int Cuenta_t;
    int Partida_t;
    char Descripcion_t[LONGITUD_DESCRIPCION];
    float Cantidad_t;
    float Precio_t = 0;
    float Subtotal_t = 0;
    float IVA_t = 0;
    float Total_t = 0;
    char Servicio_t[LONGITUD_SERVICIO];
       
    ORDENAR_REGISTROS( vtrEntrada );    
    ptfEntrada = fopen("c:Ordinario1901711.dat","r");  /* abrir archivo de entrada */
    ptfSalida = fopen("c:Ordinario1901711.sal","w");  /* abrir archivo de salida */
    if( ptfEntrada == NULL )
    {
	   printf("El archivo de entrada NO existe; favor de revisar su proceso \n");
    } 
    
    if( ptfEntrada != NULL )
    {
       /* leer archivo de entrada */
       fread(&vtrEntrada, sizeof(regCuenta), 1, ptfEntrada);
       Cuenta_t = vtrEntrada.Cuenta_e;
       Partida_t = vtrEntrada.Partida_e;
       strcpy(Servicio_t, vtrEntrada.Servicio_e);
       strcpy(Descripcion_t, vtrEntrada.Descripcion_e);
       Cantidad_t = vtrEntrada.Cantidad_e;
       do{
	        if( Cuenta_t == vtrEntrada.Cuenta_e )
	        {
	        	Precio_t = vtrEntrada.Precio_e*vtrEntrada.Cantidad_e;
	        	Subtotal_t = Subtotal_t + Precio_t ;
	        	IVA_t = Subtotal_t*0.16;
	           	Total_t = IVA_t + Subtotal_t;
	           /* leer archivo de entrada */
	           fread(&vtrEntrada, sizeof(regCuenta), 1, ptfEntrada);
	        }
	        else
	        {
	           /* se realiza el corte de control */
	           /* pasar los valores de la variables de trabajo a las variables de salida */
	           vtrSalida.Cuenta_s = Cuenta_t;
			   vtrSalida.Subtotal_s = Subtotal_t;
			   vtrSalida.IVA_s = IVA_t;	       
	           vtrSalida.Total_s = Total_t;

	           /* escribir en el archivo de salida */
	           fwrite(&vtrSalida, sizeof(regTotal), 1, ptfSalida);

	           /* re-inicializar las variables de trabajo */
	           Cuenta_t = vtrEntrada.Cuenta_e;
	           Partida_t = vtrEntrada.Partida_e;
               strcpy(Servicio_t,vtrEntrada.Servicio_e);	       
               strcpy(Descripcion_t, vtrEntrada.Descripcion_e);
               Cantidad_t = vtrEntrada.Cantidad_e;
               Subtotal_t = 0;
               IVA_t = 0;
	           Total_t = 0;
            } /* fin if */
       }while(!feof(ptfEntrada));
       /* se realiza el ultimo corte de control */
       /* pasar los valores de la variables de trabajo a las variable de salida */
       	vtrSalida.Cuenta_s = Cuenta_t;
		vtrSalida.Subtotal_s = Subtotal_t;
		vtrSalida.IVA_s = IVA_t;	       
	    vtrSalida.Total_s = Total_t;
       /* escribir en el archivo de salida */
       fwrite(&vtrSalida, sizeof(regTotal), 1, ptfSalida);
       /* cerrar archivos */
       fclose(ptfEntrada);
       fclose(ptfSalida);
       vIMPRIME(vtrSalida);
    } /* fin del if */
    printf("\n");
	printf("\n");
       system("pause");
       system("cls");
} /* fin funcion vREPORTE */

void vIMPRIME(regTotal vtrSalida)
{
   int Linea;
   	   
   /* abrir archivo de salida */
   ptfSalida = fopen("c:Ordinario1901711.sal","r");
   system("cls");
   if( ptfSalida == NULL )
   {
      printf("Imposible abrir el archivo; favor de revisar su proceso \n");
   } /* fin if(ptfsalida==NULL) */
 
   /* poner encabezados */ 
   printf("Folio Venta          Sub total              IVA               Total\n");
   Linea=2;
   /* leer archivo de salida */
   fread(&vtrSalida, sizeof(regTotal), 1, ptfSalida);
   do{
       gotoxy( 1, Linea ); 
       printf( "%ld", vtrSalida.Cuenta_s );
       gotoxy( 20, Linea ); ; 
       printf( "%8.2f", vtrSalida.Subtotal_s );
       gotoxy( 40, Linea );
       printf( "%8.2f", vtrSalida.IVA_s );
       gotoxy( 60, Linea );
       printf( "%8.2f", vtrSalida.Total_s );
       Linea++;
       /* leer archivo de salida */
       fread(&vtrSalida, sizeof(regTotal), 1, ptfSalida);
   }while(!feof(ptfSalida));
   fclose(ptfSalida);
} 

void ORDENAR_REGISTROS( regCuenta vtrEntrada )
{  
   vARCHIVO_HACIA_ARREGLOS();   
} 

void vARCHIVO_HACIA_ARREGLOS()
{
   long int auCuenta_t[1000];
   int auPartida_t[1000];
   char auServicio_t[1000][LONGITUD_SERVICIO];
   char auDescripcion_t[1000][LONGITUD_DESCRIPCION];
   float auCantidad_t[1000];
   float auPrecio_t[1000];
   int i = 0, Registros;
      
   ptfEntrada = fopen("c:Ordinario1901711.dat","r");

   fread(&vtrEntrada, sizeof(regCuenta), 1, ptfEntrada);
   do{
        /* pasar de datos de archivo hacia arreglos */
        auCuenta_t[i] = vtrEntrada.Cuenta_e;
        auPartida_t[i] = vtrEntrada.Partida_e;
	    strcpy( auServicio_t[i], vtrEntrada.Servicio_e );
	    strcpy( auDescripcion_t[i], vtrEntrada.Descripcion_e );
	    auCantidad_t[i] = vtrEntrada.Cantidad_e;
	    auPrecio_t[i] = vtrEntrada.Precio_e;
	     
        i = i + 1;
        fread(&vtrEntrada, sizeof(regCuenta), 1, ptfEntrada);
	}while( !feof( ptfEntrada ) );
	Registros = i;
	/* cerrar el archivo */	
	fclose( ptfEntrada );
    vORDENAMIENTO( auCuenta_t, auPartida_t, auServicio_t, auDescripcion_t, auCantidad_t, auPrecio_t, Registros );	
} 

void vORDENAMIENTO( long int auC_t[], int auP_t[], char auS_t[][LONGITUD_SERVICIO], char auD_t[][LONGITUD_DESCRIPCION], float auCant_t[], float auPrecio_t[], int R )
{
   int i, j, AuxiliarCuenta;
   int AuxiliarPartida;
   char AuxiliarServicio[LONGITUD_SERVICIO], AuxiliarDescripcion[LONGITUD_DESCRIPCION];
   float AuxiliarPrecio, AuxiliarCantidad;
	   
   for ( i = 1; i < R; i++)
   {
      for ( j = 0; j < R-i; j++)
      {
         if (auC_t[j] >= auC_t[j+1] )
         {
            AuxiliarCuenta = auC_t[j];
            auC_t[j] = auC_t[j+1];
            auC_t[j+1] = AuxiliarCuenta;
            
            AuxiliarPartida = auP_t[j];
            auP_t[j] = auP_t[j+1];
            auP_t[j+1] = AuxiliarPartida;
            
            strcpy(AuxiliarServicio, auS_t[j]);
            strcpy(auS_t[j], auS_t[j+1]);
            strcpy(auS_t[j+1], AuxiliarServicio);
            
            strcpy(AuxiliarDescripcion, auD_t[j]);
            strcpy(auD_t[j], auD_t[j+1]);
            strcpy(auD_t[j+1], AuxiliarDescripcion);
            
            AuxiliarCantidad = auCant_t[j];
            auCant_t[j] = auCant_t[j+1];
            auCant_t[j+1] = AuxiliarCantidad;

            AuxiliarPrecio = auPrecio_t[j];
            auPrecio_t[j] = auPrecio_t[j+1];
            auPrecio_t[j+1] = AuxiliarPrecio;
            
         } /* fin if */ 
      } /* fin for j */
   } /* fin for i */
   vARREGLO_HACIA_ARCHIVO( auC_t, auP_t, auS_t, auD_t, auCant_t, auPrecio_t, R, vtrEntrada );
} 

void vARREGLO_HACIA_ARCHIVO( long int auC_t[], int auP_t[], char auS_t[][LONGITUD_SERVICIO], char auD_t[][LONGITUD_DESCRIPCION], float auCant_t[], float auPrecio_t[], int R, regCuenta vtrEntrada )
{
   FILE *ptfNuevoArchivo;
   int i;

   /* abrir archivo en modo escritura */
   ptfEntrada = fopen("c:Ordinario1901711.dat","w");   
   
   for( i = 0; i < R; i++ )
   {
       /* pasar datos de arreglos al archivo */
       vtrEntrada.Cuenta_e = auC_t[i];
       vtrEntrada.Partida_e = auP_t[i];
       strcpy( vtrEntrada.Servicio_e, auS_t[i] );       
       strcpy( vtrEntrada.Descripcion_e, auD_t[i]);
       vtrEntrada.Cantidad_e = auCant_t[i];
       vtrEntrada.Precio_e = auPrecio_t[i];
   
       fwrite(&vtrEntrada, sizeof(regCuenta), 1, ptfEntrada);
    } /* fin del for */
   	fclose( ptfEntrada );
   	return;
} 
