//REGISTRO DE ALMACEN

#include <iostream.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <11-4.h>

//Constantes

#define ST1 "Contado"
#define ST2 "Credito"
#define DISCOUNTRAGE 0.05

//Estructura de fecha

typedef struct fech
{
	int day;
   int month;
   int year;
}	fech;

//Estructura Principal

typedef struct warehouse
{
   fech saledate;   //sd
	float salemount; //sm
   float discount;  //dc
   float paytotal;  //pt
   int salenumber;  //sn
   int sallercode;  //sc
   int saletype;    //st
   int salearea;    //sa
   char clientname[30];  //cn
   struct warehouse *before, *after; // Puntero para cada nodo
}	warehouse;

//Listas

warehouse *generallist = NULL;        //Lista general
warehouse *cashpaymentslist = NULL;   //Lista de facturas de contado
warehouse *creditpaymentslist = NULL; //Lista de facturas de credito

//------------------------------------------------------------------------------

//FUNCIONES

//Función que valida el número de venta

int searchsalenumber(warehouse *sale, int sn)
{
	sale = generallist;

   while(sale != NULL)
   {
   	if(sale -> salenumber == sn)
      	return 1;

      sale = sale -> after;
   }
   return 0;
}

//Función que averigua el descuento

float salediscount(int st, float sm)
{
	float dc;

	if(st == 1)   //Condicional si el pago es de contado
   	dc = sm * DISCOUNTRAGE;
   else //Condicional si el pago es credito
   	dc = 0.00;

   return dc;
}

//Función que averigua el total a pagar

float salepaytotal(float sm, float dc)
{
	float pt;

   pt = sm - dc;

   return pt;
}

//Función que averigua el st

char *findoutst(warehouse *sale)
{
   if(sale -> saletype == 1)
   {
   	return ST1;
   }
	else
   {
   	return ST2;
   }
}

//------------------------------------------------------------------------------

//PROCEDIMIENTOS

void reportsheader()
{
	gotoxy(3,6);	printf("Numero");
   gotoxy(13,6);	printf("N. Cliente");
   gotoxy(27,6);	printf("Monto ($)");
   gotoxy(41,6);	printf("Fecha");
   gotoxy(53,6);	printf("Tipo");
   gotoxy(62,6);	printf("Total ($)");
   horizontal(1,72,7);
}

void reportsheader2()
{
	gotoxy(3,6);	printf("Numero");
   gotoxy(13,6);	printf("N. Cliente");
   gotoxy(27,6);	printf("Monto ($)");
   gotoxy(41,6);	printf("Fecha");
   gotoxy(53,6);	printf("Zona");
   gotoxy(62,6);	printf("Total ($)");
   horizontal(1,72,7);
}

void reportsheader3()
{
	gotoxy(3,6);	printf("Numero");
   gotoxy(13,6);	printf("N. Cliente");
   gotoxy(27,6);	printf("Monto ($)");
   gotoxy(41,6);	printf("Fecha");
   gotoxy(52,6);	printf("Codigo");
   gotoxy(62,6);	printf("Total ($)");
   horizontal(1,72,7);
}

//Procedimiento que permite insertar un dato tipo cola en un nodo de la lista

void insertqueuetypebills(int sdd, int sdm, int sdy, float dc, float pt, float sm, int sn, int sc, int st, int sa, char cn[])
{
	warehouse *sale = NULL; //Define el puntero

   //Crea o construye un nuevo nodo con el tamaño de la estructura
   sale = (warehouse *) malloc(sizeof(struct warehouse));

   //Asgina a c/u de los campos del que acaba de crear los datos correspondientes
   sale -> before = NULL;
   sale -> saledate.day = sdd;
   sale -> saledate.month = sdm;
   sale -> saledate.year = sdy;
   sale -> discount = dc;
   sale -> paytotal = pt;
   sale -> salemount = sm;
   sale -> salenumber = sn;
   sale -> sallercode = sc;
   sale -> saletype = st;
   sale -> salearea = sa;
   strcpy(sale -> clientname,cn);
   sale -> after = NULL;

	if (generallist == NULL)
   	generallist = sale; //Lista hace lo mismo que esta haciendo sale
   else
   	{
      	warehouse *saleaux = generallist; //Define el puntero saleaux y hace lo mismo que lista
         while (saleaux -> after != NULL) //Ciclo que recorre la lista
         {
         	saleaux = saleaux -> after; //Mueve el puntero al siguiente nodo
         }
      	saleaux -> after = sale;  //Encadenar o unir el nuevo nodo con los
      	sale -> before = saleaux; //nodos existentes
      }
}

//Procedimiento que permite insertar un dato tipo pila en un nodo de la lista

void insertpiletypebills(int sdd, int sdm, int sdy,float dc, float pt, float sm, int sn, int sc, int st, int sa, char cn[])
{
	warehouse *sale = NULL; //Define el puntero

   //Crea o construye un nuevo nodo con el tamaño de la estructura
   sale = (warehouse *) malloc(sizeof(struct warehouse));

   //Asgina a c/u de los campos del que acaba de crear los datos correspondientes
   sale -> before = NULL;
   sale -> saledate.day = sdd;
   sale -> saledate.month = sdm;
   sale -> saledate.year = sdy;
   sale -> discount = dc;
   sale -> paytotal = pt;
   sale -> salemount = sm;
   sale -> salenumber = sn;
   sale -> sallercode = sc;
   sale -> saletype = st;
   sale -> salearea = sa;
   strcpy(sale -> clientname,cn);
   sale -> after = NULL;

	if (generallist == NULL)
   	generallist = sale; //Lista hace lo mismo que esta haciendo sale
   else
   	{
      	sale -> after = generallist;
         generallist = sale;
      }
}

//Procedimiento que lee un dato y lo guarda en la lista insertandolo como cola

void insertbills1()
{
	char next = 'S';
   char cn[30];
   int sn = 0, sc, st, sa, sdd, sdm, sdy;
   int d, m, y;
   float sm, dc, pt;
   while((next == 'S') || (next == 's'))
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,3);	printf("A G R E G A N D O  F A C T U R A S  T I P O  C O L A");

      do
      {
      	sn += 1; //ingrementa en 1 el nuemro de venta cada vez que se ingresa un dato
      	gotoxy(10,6);	printf("Numero de Venta                          : No.%d",sn);

      	if(searchsalenumber(generallist,sn) == 1)
         {
         	gotoxy(10,8);	printf("ERROR: Numero de Venta YA Existe");
            delline();	gotoxy(37,6);	clreol();
            system("Color F0");
         }
      }while(searchsalenumber(generallist,sn) != 0);

      gotoxy(10,8);	printf("Nombre del Cliente                       : ");	scanf("%s",cn);
      gotoxy(10,10);	printf("Monto de Venta                           : $");  sm = validarenteros(1,1000000,10,47);
      gotoxy(10,12);	printf("Fecha de Venta                           : ");
      sdd = validarenteros(1,31,12,47);
      gotoxy(55,12);	printf("/");
      sdm = validarenteros(1,12,12,51);
      gotoxy(58,12);	printf("/");
      sdy = validarenteros(1,1000000000,12,54);

      gotoxy(10,14);	printf("Tipo de Venta [1 = Contado | 2 = Credito]: ");   st = validarenteros(1,2,14,47);
      gotoxy(10,16);	printf("Zona de Venta [1 | 2 | 3]                : ");   sa = validarenteros(1,3,16,47);
      gotoxy(10,18);	printf("Codigo de Vendedor [1 | 2 | 3]           : ");   sc = validarenteros(1,3,18,47);

      dc = salediscount(st,sm); // Se le asigna a dc lo que devuelve "salediscount"
      pt = salepaytotal(sm,dc); // Se le asigna a Pt lo que devuelve "salepaytotal"

      gotoxy(10,20);	printf("Descuento                                : $%.2f", dc);
      gotoxy(10,22);	printf("Total a Pagar                            : $%.2f", pt);

      insertqueuetypebills(sdd, sdm, sdy, dc, pt, sm, sn, sc, st, sa, cn);

      gotoxy(10,25);	printf("Continuar Agregando Facturas [S | N]...?");
      next = getch();
   }
}

//Procedimiento que lee un dato y lo guarda en la lista insertandolo como cola

void insertbills2()
{
	char next = 'S';
   char cn[30];
   int sn = 0, sc, st, sa, sdd, sdm, sdy;
   int d, m, y;
   float sm, dc, pt;
   while((next == 'S') || (next == 's'))
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,3);	printf("A G R E G A N D O  F A C T U R A S  T I P O  P I L A");

      do
      {
      	sn += 1; //ingrementa en 1 el nuemro de venta cada vez que se ingresa un dato
      	gotoxy(10,6);	printf("Numero de Venta                          : No.%d",sn);

      	if(searchsalenumber(generallist,sn) == 1)
         {
         	gotoxy(10,8);	printf("ERROR: Numero de Venta YA Existe");
            delline();	gotoxy(37,6);	clreol();
            system("Color F0");
         }
      }while(searchsalenumber(generallist,sn) != 0);

      gotoxy(10,8);	printf("Nombre del Cliente                       : ");	scanf("%s",cn);
      gotoxy(10,10);	printf("Monto de Venta                           : $");  sm = validarenteros(1,1000000,10,47);
      gotoxy(10,12);	printf("Fecha de Venta                           : ");
      sdd = validarenteros(1,31,12,57);
      gotoxy(55,12);	printf("/");
      sdm = validarenteros(1,12,12,51);
      gotoxy(58,12);	printf("/");
      sdy = validarenteros(1,1000000000,12,54);

      gotoxy(10,14);	printf("Tipo de Venta [1 = Contado | 2 = Credito]: ");   st = validarenteros(1,2,14,47);
      gotoxy(10,16);	printf("Zona de Venta [1 | 2 | 3]                : ");   sa = validarenteros(1,3,16,47);
      gotoxy(10,18);	printf("Codigo de Vendedor [1 | 2 | 3]           : ");   sc = validarenteros(1,3,18,47);

      dc = salediscount(st,sm); // Se le asigna a dc lo que devuelve "salediscount"
      pt = salepaytotal(sm,dc); // Se le asigna a Pt lo que devuelve "salepaytotal"

      gotoxy(10,20);	printf("Descuento                                : $%.2f", dc);
      gotoxy(10,22);	printf("Total a Pagar                            : $%.2f", pt);

      insertpiletypebills(sdd, sdm, sdy,dc, pt, sm, sn, sc, st, sa, cn);

      gotoxy(10,25);	printf("Continuar Agregando Facturas [S | N]...?");
      next = getch();
   }
}

//Submenu de crear facturas

void submenu1()
{
	SetConsoleTitle("Facturas Almacen"); // Cambia el nombre de la consola
   _setcursortype(_NOCURSOR);
	int option = 0;
   while(option < 3)
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,2);	printf("S U B M E N U :  A G R E G A R  F A C T U R A S");
      gotoxy(10,5);	printf("1. Agregar Tipo Cola");
      gotoxy(10,7);	printf("2. Agregar Tipo Pila");
      gotoxy(10,9);	printf("3. Regresar");
      gotoxy(10,12);	printf("Digite su Opcion: ");
      option = validarenteros(1,9,28,12);

      switch(option)
      {
         case 1:   insertbills1();    break;
         case 2:   insertbills2();    break;
      }
   }
}

//Procedimiento de consultar facturas

void consultbills(warehouse *sale)
{
	char next = 'S';
   int sn,enco = 0;
   sale = generallist;
   while((next == 'S') || (next == 's'))
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,3);	printf("C O N S U L T A N D O  F A C T U R A S");
      		gotoxy(10,6);	printf("Numero de Venta    : No.");
      sn = validarenteros(1,10000000000,34,6);
      if(searchsalenumber(generallist,sn) != 0)
      {
      	while(sale != NULL) //Ciclo que recorre la lista
      	{
         	if(sale -> salenumber == sn)
      		{
         		enco = 1;
         		gotoxy(10,8);  printf("Nombre del Cliente : %s",sale -> clientname);
         		gotoxy(10,10); printf("Monto de Venta     : $%.2f",sale -> salemount);
            	gotoxy(10,12);	printf("Fecha de Pago      : %d/%d/%d", sale -> saledate.day, sale -> saledate.month, sale -> saledate.year);
            	gotoxy(10,14);	printf("Tipo de Venta      : %s",findoutst(generallist));
            	gotoxy(10,16);	printf("Zona de Venta      : No.%d", sale -> salearea);
            	gotoxy(10,18);	printf("Codigo de Vendedor : No.%d", sale -> sallercode);
            	gotoxy(10,20);	printf("Descuento          : $%.2f", sale -> discount);
            	gotoxy(10,22);	printf("Total Pagado       : $%.2f", sale -> paytotal);
      		}
         	if(enco != 1)
      		{
      			gotoxy(10,8);	printf("Numero de Venta NO Existente");
      		}
         	sale = sale -> after;
   		}
      }
      gotoxy(10,25);	printf("Continuar Consultando Facturas [S | N] ?");
      next = getch();
   }
}

//------------------------------------------------------------------------------

//Modificar datos de factura

//Procedimiento que modifica el nombre del cliente "clientname"

void modifyclientname(warehouse *sale)
{
	sale = generallist; //Se define e inicializa el puntero "sale"

	char next = 'S';
   int sn;
   char newcn[30];

   clrscr();
   system("Color F0");
   gotoxy(10,3);	printf("M O D I F I C A N D O  N O M B R E  D E L  C L I E N T E");
			gotoxy(10,6);	printf("Numero de Venta          :");
   sn = validarenteros(1,10000000000,37,6);
   while(sale != NULL) //Ciclo que recorre la lisat
   {
   	if(sale -> salenumber != sn)
      {
      	gotoxy(10,8);	printf("ERROR: NO Encontrado");
      }
   	if(sale -> salenumber == sn) //Condicional que verifica el numero de venta
      {
      	gotoxy(10,8);	printf("Nombre del Cliente Actual: %s",sale -> clientname);
         gotoxy(10,10);	printf("Nuevo Nombre del Cliente : ");

         scanf("%s",&newcn);
         strcpy(sale -> clientname,newcn); //Copia el nuevo nombre en "sale -> clientname"

         gotoxy(10,13);	printf("Nombre del Cliente Modificado Exitosamente...");
         break;
      }
      sale = sale -> after;
   }
   gotoxy(10,16);	printf("Pulse TECLA para Continuar...");
   getch();
}

//Procedimiento que modifica el monto de venta "salemount"

void modifysalemount(warehouse *sale)
{
	sale = generallist; //Se define e inicializa el puntero "sale"

	char next = 'S';
   int sn;
   float newsm;

   clrscr();
   system("Color F0");
   gotoxy(10,3);	printf("M O D I F I C A N D O  M O N T O  D E  V E N T A");
			gotoxy(10,6);	printf("Numero de Venta      :");
   sn = validarenteros(1,10000000000,33,6);
   while(sale != NULL) //Ciclo que recorre la lisat
   {
   	if(sale -> salenumber == sn) //Condicional que verifica el numero de venta
      {
      	gotoxy(10,8);	printf("Monto de Venta Actual: $%.2f",sale -> salemount);
         gotoxy(10,10);	printf("Nuevo Monto de Venta : $");

         newsm = validarenteros(1,10000000000,34,10);
         sale -> salemount = newsm;	//Actualiza "salemount" al nuevo monto introducido por el usuario
         sale -> discount = salediscount(sale -> saletype,newsm); //Actualiza el descuento tomando en cuenta el nuevo monto de venta
      	sale -> paytotal = salepaytotal(newsm,sale -> discount); //Actualiza el total de venta tomando en cuenta el nuevo monto de venta

         gotoxy(10,13);	printf("Monto de Venta Modificado Exitosamente...");
         break;
      }
      if(sale -> salenumber != sn)
      {
      	gotoxy(10,8);	printf("ERROR: NO Encontrado");
      }
      sale = sale -> after;
   }
   gotoxy(10,16);	printf("Pulse TECLA para Continuar...");
   getch();
}

//Procedimiento que modifica la fecha

void modifysaledate(warehouse *sale)
{
	sale = generallist; //Se define e inicializa el puntero "sale"

	char next = 'S';
   int sn,newsdd,newsdm,newsdy;

   clrscr();
   system("Color F0");
   gotoxy(10,3);	printf("M O D I F I C A N D O  F E C H A  D E  V E N T A");
   		gotoxy(10,6);	printf("Numero de Venta: ");
   sn = validarenteros(1,10000000000,27,6);
   while(sale != NULL) //Ciclo que recorre la lisat
   {
   	if(sale -> salenumber == sn) //Condicional que verifica el numero de venta
      {
      	gotoxy(10,8);	printf("Fecha Actual   : %d/%d/%d",sale -> saledate.day,sale -> saledate.month,sale -> saledate.year);
         gotoxy(10,10);	printf("Nueva Fecha    : ");
         newsdd = validarenteros(1,31,27,10);
      	gotoxy(29,10);	printf("/");
      	newsdm = validarenteros(1,12,30,10);
      	gotoxy(32,10);	printf("/");
      	newsdy = validarenteros(1,1000000000,33,10);

         sale -> saledate.day = newsdd;
         sale -> saledate.month = newsdm;
         sale -> saledate.year = newsdy;

         gotoxy(10,13);	printf("Fecha Modificada Exitosamente...");
         break;
      }
      if(sale -> salenumber != sn)
      {
      	gotoxy(10,8);	printf("ERROR: NO Encontrado");
      }
      sale = sale -> after;
   }
   gotoxy(10,16);	printf("Pulse TECLA para Continuar...");
   getch();
}

//Procedimiento que modifica el tipo de venta "saletype"

void modifysaletype(warehouse *sale)
{
	sale = generallist; //Se define e inicializa el puntero "sale"

	char next = 'S';
   int sn,newst;

   clrscr();
   system("Color F0");
   gotoxy(10,3);	printf("M O D I F I C A N D O  T I P O  D E  V E N T A");
			gotoxy(10,6);	printf("Numero de Venta     : ");
   sn = validarenteros(1,10000000000,33,6);
   while(sale != NULL) //Ciclo que recorre la lisat
   {
   	if(sale -> salenumber == sn) //Condicional que verifica el numero de venta
      {
      	gotoxy(10,8);	printf("Tipo de Venta Actual: No.%d (%s)",sale -> saletype,findoutst(generallist));
         gotoxy(10,10);	printf("Nuevo Tipo de Venta : No.");

         newst = validarenteros(1,10000000000,35,10);
         sale -> saletype = newst;	//Actualiza "saletype" al nuevo typo de venta introducido por el usuario
         sale -> discount = salediscount(newst,sale -> salemount); //Actualiza el descuento tomando en cuenta el nuevo tipo de venta
      	sale -> paytotal = salepaytotal(sale -> salemount,sale -> discount); //Actualiza el total de venta tomando en cuenta el nuevo tipo de venta

         gotoxy(37,10);	printf("(%s)",findoutst(generallist));
         gotoxy(10,13);	printf("Tipo de Venta Modificado Exitosamente...");
         break;
      }
      if(sale -> salenumber != sn)
      {
      	gotoxy(10,8);	printf("ERROR: NO Encontrado");
      }
      sale = sale -> after;
   }
   gotoxy(10,16);	printf("Pulse TECLA para Continuar...");
   getch();
}

//Procedimiento que modifica la zona de venta "salearea"

void modifysalearea(warehouse *sale)
{
	sale = generallist; //Se define e inicializa el puntero "sale"

	char next = 'S';
   int sn,newsa;

   clrscr();
   system("Color F0");
   gotoxy(10,3);	printf("M O D I F I C A N D O  A R E A  D E  V E N T A");
			gotoxy(10,6);	printf("Numero de Venta     : ");
   sn = validarenteros(1,10000000000,33,6);
   while(sale != NULL) //Ciclo que recorre la lisat
   {
   	if(sale -> salenumber == sn) //Condicional que verifica el numero de venta
      {
      	gotoxy(10,8);	printf("Zona de Venta Actual: No.%d",sale -> saletype);
         gotoxy(10,10);	printf("Nueva Zona de Venta : No.");

         newsa = validarenteros(1,10000000000,35,10);
         sale -> salearea = newsa;	//Actualiza "salearea" a la nueva area introducida por el usuario

         gotoxy(10,13);	printf("Area de Venta Modificada Exitosamente...");
         break;
      }
      if(sale -> salenumber != sn)
      {
      	gotoxy(10,8);	printf("ERROR: NO Encontrado");
      }
      sale = sale -> after;
   }
   gotoxy(10,16);	printf("Pulse TECLA para Continuar...");
   getch();
}

//Procedimiento que modifica el codigo del vendedor "sallercode"

void modifysallercode(warehouse *sale)
{
	sale = generallist; //Se define e inicializa el puntero "sale"

	char next = 'S';
   int sn,newsc;

   clrscr();
   system("Color F0");
   gotoxy(10,3);	printf("M O D I F I C A N D O  C O D I G O  D E  V E N D E D O R");
   	gotoxy(10,6);	printf("Numero de Venta          : ");
   sn = validarenteros(1,10000000000,37,6);
   while(sale != NULL) //Ciclo que recorre la lisat
   {
   	if(sale -> salenumber == sn) //Condicional que verifica el numero de venta
      {
      	gotoxy(10,8);	printf("Codigo de Vendedor Actual: No.%d",sale -> sallercode);
         gotoxy(10,10);	printf("Nueva Zona de Venta      : No.");

         newsc = validarenteros(1,10000000000,40,10);
         sale -> sallercode = newsc;	//Actualiza "sallercode" al nuevo codigo de vendedor introducido por el usuario

         gotoxy(10,13);	printf("Codigo de Vendedor Modificado Exitosamente...");
         break;
      }
      if(sale -> salenumber != sn)
      {
      	gotoxy(10,8);	printf("ERROR: NO Encontrado");
      }
      sale = sale -> after;
   }
   gotoxy(10,16);	printf("Pulse TECLA para Continuar...");
   getch();
}

//Submenu de modificar facturas

void submenu2()
{
	SetConsoleTitle("Facturas Almacen"); // Cambia el nombre de la consola
   _setcursortype(_NOCURSOR);
	int option = 0;
   while(option < 6)
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,2);	printf("S U B M E N U :  M O D I F I C A R  F A C T U R A S");
      gotoxy(10,5);	printf("1. Modificar Nombre del Cliente");
      gotoxy(10,7);	printf("2. Modificar Monto de Venta");
      gotoxy(10,9);	printf("3. Modificar Fecha de Venta");
      gotoxy(10,11);	printf("4. Modificar Tipo de Venta");
      gotoxy(10,13);	printf("5. Modificar Zona de Venta");
      gotoxy(10,15);	printf("6. Modificar Codigo del Vendedor");
      gotoxy(10,17);	printf("7. Regresar");
      gotoxy(10,20);	printf("Digite su Opcion: ");
      option = validarenteros(1,7,28,20);

      switch(option)
      {
         case 1:  modifyclientname(generallist); break;
         case 2:  modifysalemount(generallist);  break;
         case 3:  modifysaledate(generallist);   break;
         case 4:  modifysaletype(generallist);   break;
         case 5:  modifysalearea(generallist);   break;
         case 6:  modifysallercode(generallist); break;
      }
   }
}

//Procedimiento general de modificar facturas

void modifybill(warehouse *sale)
{
	sale = generallist; //Se define e inicializa el puntero "sale"

	char next = 'S';
   int sn = 0;
   while((next == 'S') || (next == 's'))
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,3);	printf("M O D I F I C A N D O  F A C T U R A S");
      gotoxy(10,6);	printf("Numero de Venta: ");
      sn = validarenteros(1,10000000000,27,6);

      if(searchsalenumber(sale,sn) != 0) //Aqui invoca la función para buscar el numero de venta correspondiente
      {
      	submenu2();
         clrscr();
         system("Color F0");
      	gotoxy(10,10);	printf("Continuar Modificando Empleados [S | N]?");
      }
      if(searchsalenumber(sale,sn) == 0)
      {
      	gotoxy(10,8);	printf("Factura NO Encontrada");
         gotoxy(10,10);	printf("Continuar Modificando Empleados [S | N]?");
      }
      next = getch();
   }
}

//------------------------------------------------------------------------------

//Procedimiento para eliminar una factura

void removebill(warehouse *sale)
{
	sale = generallist;
	int sn;
	int found = 0;
	char answer = ' ';
	clrscr();
   system("Color F0");
	gotoxy(10,2); printf("E L I M I N A N D O  F A C T U R A S");
	gotoxy(10,5); printf("Numero de Venta a Eliminar: ");
   sn = validarenteros(1,100,38,5);

	while (sale != NULL) //Ciclo para recorrer la lista
	{
		if (sn == sale -> salenumber)
		{
			gotoxy(10,8);  printf("Factura Encontrada...");
			gotoxy(10,10); printf("Factura No.%d",sn);
			found = 1;
			break;
		}
		sale = sale -> after; //Mueve el puntero al siguiente nodo en la lista
	}
	if (found == 0)
	{
		gotoxy(10,8); printf("Factura NO Encontrada...");
	}
	if (found	==	1)
	{
		gotoxy(10,15); printf("Esta Seguro que Desea Eliminar los Datos de Esta Factura [S | N]?: ");
		answer = getch();
		if (toupper(answer) == 'N')
		{
			gotoxy(10,17); printf("Los Datos NO han Sido Eliminados...");
		}
		if (toupper(answer) != 'N')
		{
			if ((sale -> before == NULL) && (sale -> after == NULL))
			{
				generallist = NULL;
			}
			else
				if(sale -> before == NULL) //Verifica si es el primer nodo
				{
					warehouse *saleaux1 = sale;
					sale = sale -> after;
					sale -> before = NULL;
   				saleaux1 = NULL;
					free(saleaux1);
					generallist = sale;
				}
				else
					if(sale -> after == NULL) //Verifica si es el último nodo
					{
                  warehouse *saleaux1 = sale;
						sale = sale -> before;
               	sale -> after = NULL;
						saleaux1 = NULL;
						free(saleaux1);
					}
					else //Verifica si está en el medio
					{
						warehouse *saleaux1 = sale -> before;
               	warehouse *saleaux2 = sale -> after;
						saleaux1 -> after = saleaux2;
						saleaux2 -> before = saleaux1;
						sale = NULL;
						free(sale);
					}
					gotoxy(10,17); printf("Los Datos han Sido Eliminados Correctamente...");

		} //Cierra If answer != ‘N’
	} //Cierra If found = 1
	gotoxy(10,20); printf("Pulse TECLA para Continuar...");
	getch();
}

//------------------------------------------------------------------------------

//PROCEDIMIENTOS PARA GENERAR LISTAS

//Procedimiento que inserta la lista "cashpaymentslist"

void insertcashpayments(int sdd, int sdm, int sdy, float dc, float pt, float sm, int sn, int sc, int st, int sa, char cn[])
{
	warehouse *sale = NULL; //Se define e inicializa el puntero "sale"

   sale = (warehouse *) malloc(sizeof(struct warehouse)); //Crea un nuevo espacio en la variable sale

   sale -> before = NULL;
   sale -> saledate.day = sdd;
   sale -> saledate.month = sdm;
   sale -> saledate.year = sdy;
   sale -> discount = dc;
   sale -> paytotal = pt;
   sale -> salemount = sm;
   sale -> salenumber = sn;
   sale -> sallercode = sc;
   sale -> saletype = st;
   sale -> salearea = sa;
   strcpy(sale -> clientname,cn);
   sale -> after = NULL;

   if(cashpaymentslist == NULL) //Condicional si "cashpaymentslist" está vacía
   {
   	cashpaymentslist = sale; //Lista apunta al mismo lugar que donde está sale
   }
   else //Condicional si "cashpaymentslist" no está vacía
   {
   	warehouse *sale2 = cashpaymentslist; //Se define sale2 y apunta al mismo lugar que "cashpaymentslist"
      while(sale2 -> after != NULL) //Recorre la lista hasta que after sea NULL
      	sale2 = sale2 -> after; //Mueve el puntero
      sale2 -> after = sale;
   }
}

//Procedimiento que inserta la lista "creditpaymentslist"

void insertcreditpayments(int sdd, int sdm, int sdy, float dc, float pt, float sm, int sn, int sc, int st, int sa, char cn[])
{
	warehouse *sale = NULL; //Se define e inicializa el puntero "sale"

   sale = (warehouse *) malloc(sizeof(struct warehouse)); //Crea un nuevo espacio en la variable sale

   sale -> before = NULL;
   sale -> saledate.day = sdd;
   sale -> saledate.month = sdm;
   sale -> saledate.year = sdy;
   sale -> discount = dc;
   sale -> paytotal = pt;
   sale -> salemount = sm;
   sale -> salenumber = sn;
   sale -> sallercode = sc;
   sale -> saletype = st;
   sale -> salearea = sa;
   strcpy(sale -> clientname,cn);
   sale -> after = NULL;

   if(creditpaymentslist == NULL) //Condicional si "creditpaymentslist" está vacía
   {
   	creditpaymentslist = sale; //Lista apunta al mismo lugar que donde está sale
   }
   else //Condicional si "creditpaymentslist" no está vacía
   {
   	warehouse *sale3 = creditpaymentslist; //Se define sale3 y apunta al mismo lugar que "creditpaymentslist"
      while(sale3 -> after != NULL) //Recorre la lista hasta que after sea NULL
      	sale3 = sale3 -> after; //Mueve el puntero
      sale3 -> after = sale;
   }
}

//Procedimiento que copia los datos de las facturas guardadas en "cashpaymentslist"

void copycashpaymentslist(warehouse *sale)
{
	cashpaymentslist = NULL;
   sale = generallist;  //"sale" hace lo mismo que esta haciendo lista, es decir apunta al primer nodo de la lista
   while(sale != NULL)  //Ciclo que recorre la lista
   {
      if(sale -> saletype == 1) //Chequea si la factura es de pago en contado
   	{
   		insertcashpayments(sale -> saledate.day,sale -> saledate.month,sale -> saledate.year ,sale -> discount,sale -> paytotal,
         sale -> salemount,sale -> salenumber,sale -> sallercode,sale -> saletype,sale -> salearea,sale -> clientname); //Invocación "insertcashpayments"

   	}
   	sale = sale -> after;        //Mueve el puntero al siguiente nodo
   }
   clrscr();
   system("Color F0");
   gotoxy(10,3);printf("GENERANDO LISTA DE PAGOS EN CONTADO");
   gotoxy(10,6);printf("Lista de PAGOS EN CONTADO Generada Correctamente...");
   gotoxy(10,9);printf("Pulse TECLA para Continuar...");
   getch();
}

//Procedimiento que copia los datos de las facturas guardadas en "creditpaymentslist"

void copycreditpaymentslist(warehouse *sale)
{
	creditpaymentslist = NULL;
   sale = generallist;  //"sale" hace lo mismo que esta haciendo lista, es decir apunta al primer nodo de la lista
   while(sale != NULL)  //Ciclo que recorre la lista
   {
      if(sale -> saletype == 2) //Chequea si la factura es de pago en credito
   	{
   		insertcreditpayments(sale -> saledate.day,sale -> saledate.month,sale -> saledate.year ,sale -> discount,sale -> paytotal,
         sale -> salemount,sale -> salenumber,sale -> sallercode,sale -> saletype,sale -> salearea,sale -> clientname); //Invocación de  "insertcreditpayments"

   	}
   	sale = sale -> after;        //Mueve el puntero al siguiente nodo
   }
   clrscr();
   system("Color F0");
   gotoxy(10,3);printf("GENERANDO LISTA DE PAGOS EN CREDITO");
   gotoxy(10,6);printf("Lista de PAGOS EN CREDITO Generada Correctamente...");
   gotoxy(10,9);printf("Pulse TECLA para Continuar...");
   getch();
}

//Procedimiento que despliega la lista "cashpaymentslist"

void reportcashpaymentslist(warehouse *sale,warehouse *sale2)
{
   sale2 = cashpaymentslist;  //Asigna a "sale2" lo guardado en "cahspaymentslist"

   int line = 6;
   if(sale2 == NULL) //Por si "cashpaymentslist" está vacía
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  D E  C O N T A D O");
      gotoxy(9,5);	printf("NO hay Facturas Pagadas de Contado...");
   }
   else
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  D E  C O N T A D O");
      reportsheader();

      while(sale2 != NULL)  //Este ciclo nos imprime la lista de contados
      {
         gotoxy(4,line + 3);	printf("No.%d",sale2 -> salenumber);
         gotoxy(13,line + 3);	printf("%s",sale2 -> clientname);
      	gotoxy(26,line + 3);	printf("$%.2f",sale2 -> salemount);
      	gotoxy(39,line + 3);	printf("%d/%d/%d", sale -> saledate.day, sale -> saledate.month, sale -> saledate.year);
      	gotoxy(52,line + 3);	printf("Contado");
      	gotoxy(62,line + 3);	printf("$%.2f",sale2 -> paytotal);

         sale2 = sale2 -> after; //Mueve el puntero al siguiente nodo de la lista original

         line++;

         vertical(6,line + 3,11);
      	vertical(6,line + 3,24);
      	vertical(6,line + 3,37);
      	vertical(6,line + 3,50);
      	vertical(6,line + 3,60);
         vertical(6,line + 3,72);

      }

      gotoxy(10,line + 15);printf("Pulse TECLA para continuar...");
   }
   getch();
}

//Procedimiento que despliega la lista "creditpaymentslist"

void reportcreditpaymentslist(warehouse *sale,warehouse *sale3)
{
   sale3 = creditpaymentslist;  //Asigna a "sale3" lo guardado en "creditpaymentslist"

   int line = 6;
   if(sale3 == NULL) //Por si "creditpaymentslist" está vacía
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  D E  C R E D I T O");
      gotoxy(9,5);	printf("NO hay Facturas Pagadas de Credito...");
   }
   else
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  D E  C R E D I T O");
      reportsheader();

      while(sale3 != NULL)  //Este ciclo nos imprime la lista de contados
      {
         gotoxy(4,line + 3);	printf("No.%d",sale3 -> salenumber);
         gotoxy(13,line + 3);	printf("%s",sale3 -> clientname);
      	gotoxy(26,line + 3);	printf("$%.2f",sale3 -> salemount);
      	gotoxy(39,line + 3);	printf("%d/%d/%d", sale -> saledate.day, sale -> saledate.month, sale -> saledate.year);
      	gotoxy(52,line + 3);	printf("Credito");
      	gotoxy(62,line + 3);	printf("$%.2f",sale3 -> paytotal);
         sale3 = sale3 -> after; //Mueve el puntero al siguiente nodo de la lista original

         line++;

         vertical(6,line + 3,11);
      	vertical(6,line + 3,24);
      	vertical(6,line + 3,37);
      	vertical(6,line + 3,50);
      	vertical(6,line + 3,60);
         vertical(6,line + 3,72);

      }

      gotoxy(10,line + 15);printf("Pulse TECLA para continuar...");
   }
   getch();
}

//Submenu de generar listas

void submenu3()
{
	SetConsoleTitle("Facturas Almacen"); // Cambia el nombre de la consola
   _setcursortype(_NOCURSOR);
	int option = 0;
   while(option < 2)
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,2);	printf("S U B M E N U :  G E N E R A R  L I S T A S");
      gotoxy(10,5);	printf("1. Desplegar Lista de Pagos en Contado");
      gotoxy(10,7);	printf("2. Desplegar Lista de Pagos en Credito");
      gotoxy(10,9);	printf("3. Regresar");
      gotoxy(10,12);	printf("Digite su Opcion: ");
      option = validarenteros(1,3,28,12);

      switch(option)
      {
         case 1:  reportcashpaymentslist(generallist,cashpaymentslist);     break;
         case 2:  reportcreditpaymentslist(generallist,creditpaymentslist); break;
      }
   }
}

//------------------------------------------------------------------------------

//PROCEDIMIENTOS DE REPORTES

//Procedimiento que despliega la lista "generallist"

void reportbills(warehouse *sale)
{
   sale = generallist;  //Asigna a "sale" lo guardado en "generallist"

   int line = 6;
   if(sale == NULL) //Por si "generallist" está vacía
   {
   	clrscr();
      system("Color F0");
      gotoxy(20,5);	printf("NO hay Facturas Agregadas...");
   }
   else
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  T O D A S  L A S  F A C T U R A S");
      reportsheader();

      while(sale != NULL)  //Este ciclo nos imprime la lista de contados
      {
         gotoxy(4,line + 3);	printf("No.%d",sale -> salenumber);
         gotoxy(13,line + 3);	printf("%s",sale -> clientname);
      	gotoxy(26,line + 3);	printf("$%.2f",sale -> salemount);
      	gotoxy(39,line + 3);	printf("%d/%d/%d", sale -> saledate.day, sale -> saledate.month, sale -> saledate.year);

         if(sale -> saletype == 1) {
      		gotoxy(52,line + 3);	printf("Contado");}
         else {
            gotoxy(52,line + 3);	printf("Credito"); }

      	gotoxy(62,line + 3);	printf("$%.2f",sale -> paytotal);
         sale = sale -> after; //Mueve el puntero al siguiente nodo de la lista original

         line++;

         vertical(6,line + 3,11);
      	vertical(6,line + 3,24);
      	vertical(6,line + 3,37);
      	vertical(6,line + 3,50);
      	vertical(6,line + 3,60);
         vertical(6,line + 3,72);
      }

      gotoxy(10,line + 15);	printf("Pulse TECLA para continuar...");
   }
   getch();
}

//Procedimiento que despliega la lista "generallist" por area de compras

void reportbillsbyarea(warehouse *sale)
{
   sale = generallist;  //Asigna a "sale" lo guardado en "generallist"

   int sarea = 0;
   int line = 6;

   if(sale == NULL) //Por si "generallist" está vacía
   {
   	clrscr();
      system("Color F0");
      gotoxy(20,5);	printf("NO hay Facturas Agregadas...");
   }
   else
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  Z O N A");
      gotoxy(9,6);	printf("Zona de Compra: No.");	sarea = validarenteros(1,3,28,6);
      clrscr();
      system("Color F0");

      while(sale != NULL)  //Este ciclo nos imprime la lista de contados
      {
         if(sale -> salearea == sarea)
         {
            gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  Z O N A");
         	reportsheader2();
         	gotoxy(4,line + 3);	printf("No.%d",sale -> salenumber);
         	gotoxy(13,line + 3);	printf("%s",sale -> clientname);
      		gotoxy(26,line + 3);	printf("$%.2f",sale -> salemount);
            gotoxy(39,line + 3);	printf("%d/%d/%d", sale -> saledate.day, sale -> saledate.month, sale -> saledate.year);
            gotoxy(53,line + 3);	printf("No.%d",sale -> salearea);
      		gotoxy(62,line + 3);	printf("$%.2f",sale -> paytotal);
            line++;
         	vertical(6,line + 3,11);
         	vertical(6,line + 3,24);
      		vertical(6,line + 3,37);
         	vertical(6,line + 3,50);
         	vertical(6,line + 3,60);
         	vertical(6,line + 3,72);
         }
         if(sale -> salearea != sarea)
      	{
      		gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  Z O N A");
      		gotoxy(9,6);	printf("NO hay Facturas Agregadas en Esta Zona de Venta...");
      	}

         sale = sale -> after; //Mueve el puntero al siguiente nodo de la lista original
      }
   }
   gotoxy(10,line + 15);	printf("Pulse TECLA para continuar...");
   getch();
}

//Procedimiento que despliega la lista "generallist" por area de compras

void reportbillsbycode(warehouse *sale)
{
   sale = generallist;  //Asigna a "sale" lo guardado en "generallist"

   int scode = 0;
   int line = 6;

   if(sale == NULL) //Por si "generallist" está vacía
   {
   	clrscr();
      system("Color F0");
      gotoxy(20,5);	printf("NO hay Facturas Agregadas...");
   }
   else
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  C O D I G O");
      gotoxy(9,6);	printf("Codigo de Vendedor: No.");	scode = validarenteros(1,3,32,6);
      clrscr();
      system("Color F0");

      while(sale != NULL)  //Este ciclo nos imprime la lista de contados
      {
         if(sale -> sallercode == scode)
         {
            gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  C O D I G O");
         	reportsheader3();
         	gotoxy(4,line + 3);	printf("No.%d",sale -> salenumber);
         	gotoxy(13,line + 3);	printf("%s",sale -> clientname);
      		gotoxy(26,line + 3);	printf("$%.2f",sale -> salemount);
            gotoxy(39,line + 3);	printf("%d/%d/%d", sale -> saledate.day, sale -> saledate.month, sale -> saledate.year);
            gotoxy(53,line + 3);	printf("No.%d",sale -> sallercode);
      		gotoxy(62,line + 3);	printf("$%.2f",sale -> paytotal);
            line++;
         	vertical(6,line + 3,11);
         	vertical(6,line + 3,24);
      		vertical(6,line + 3,37);
         	vertical(6,line + 3,50);
         	vertical(6,line + 3,60);
         	vertical(6,line + 3,72);
         }

         if(sale -> sallercode != scode)
      	{
      		gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  C O D I G O");
      		gotoxy(9,6);	printf("NO hay Facturas Agregadas con este Codigo de Vendedor...");
      	}

         sale = sale -> after; //Mueve el puntero al siguiente nodo de la lista original
      }
   }
   gotoxy(10,line + 15);	printf("Pulse TECLA para continuar...");
   getch();
}

//Procedimiento que reporta facturas por rango de fechas

void reportbillsbydaterange(warehouse *sale)
{
	sale = generallist;  //Asigna a "sale" lo guardado en "generallist"

   int sdd1,sdm1,sdy1;
   int sdd2,sdm2,sdy2;
   int line = 6;


   if(sale == NULL) //Por si "generallist" está vacía
   {
   	clrscr();
      system("Color F0");
      gotoxy(20,5);	printf("NO hay Facturas Agregadas...");
   }
   else
   {
   	clrscr();
      system("Color F0");
      gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  F E C H A");
      gotoxy(12,6);	printf("Fecha Inicial");
      gotoxy(30,6);	printf("Fecha Final");
      horizontal(10,42,7);
      vertical(6,13,27);
      gotoxy(12,9);	printf("Dia: ");	sdd1 = validarenteros(1,31,17,9);
      gotoxy(12,11);	printf("Mes: ");	sdm1 = validarenteros(1,12,17,11);
      gotoxy(12,13);	printf("A%co: ",164);	sdy1 = validarenteros(1,1000000,17,13);
      gotoxy(30,9);	printf("Dia: ");	sdd2 = validarenteros(1,31,35,9);
      gotoxy(30,11);	printf("Mes: ");	sdm2 = validarenteros(1,12,35,11);
      gotoxy(30,13);	printf("A%co: ",164);	sdy2 = validarenteros(1,1000000,35,13);
      clrscr();
      system("Color F0");

      while(sale != NULL)  //Este ciclo nos imprime la lista de contados
      {
         if((sale -> saledate.day >= sdd1) && (sale -> saledate.month >= sdm1) &&
         	(sale -> saledate.year >= sdy1) && (sale -> saledate.day <= sdm2)&&
            (sale -> saledate.month <= sdm2) && (sale -> saledate.year <= sdy2))
         {
            gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  F E C H A");
         	reportsheader3();
         	gotoxy(4,line + 3);	printf("No.%d",sale -> salenumber);
         	gotoxy(13,line + 3);	printf("%s",sale -> clientname);
      		gotoxy(26,line + 3);	printf("$%.2f",sale -> salemount);
            gotoxy(39,line + 3);	printf("%d/%d/%d", sale -> saledate.day, sale -> saledate.month, sale -> saledate.year);
            gotoxy(53,line + 3);	printf("No.%d",sale -> sallercode);
      		gotoxy(62,line + 3);	printf("$%.2f",sale -> paytotal);
            line++;
         	vertical(6,line + 3,11);
         	vertical(6,line + 3,24);
      		vertical(6,line + 3,37);
         	vertical(6,line + 3,50);
         	vertical(6,line + 3,60);
         	vertical(6,line + 3,72);
         }

         if((sale -> saledate.day < sdd1) || (sale -> saledate.month < sdm1) ||
         	(sale -> saledate.year < sdy1) || (sale -> saledate.day > sdd2) ||
            (sale -> saledate.month > sdm2) || (sale -> saledate.year > sdy2))
      	{
      		gotoxy(9,3);	printf("R E P O R T A N D O  F A C T U R A S  P O R  F E C H A");
      		gotoxy(9,6);	printf("NO hay Facturas Registradas en este Rango de Fechas...");
      	}

         sale = sale -> after; //Mueve el puntero al siguiente nodo de la lista original
      }
   }
   gotoxy(10,line + 15);	printf("Pulse TECLA para continuar...");
   getch();
}

//Submenu de reportes

void submenu4()
{
	SetConsoleTitle("Facturas Almacen"); // Cambia el nombre de la consola
   _setcursortype(_NOCURSOR); //Elimina la barrita del cursor
	int option = 0;
   while(option < 6)
   {
   	clrscr();
      system("Color F0");
      gotoxy(10,2);	printf("S U B M E N U :  R E P O R T E S  D E  F A C T U R A S");
      gotoxy(10,5);	printf("1. Reportar Todas las Ventas");
      gotoxy(10,7);	printf("2. Reportar Ventas por Zona");
      gotoxy(10,9);	printf("3. Reportar Ventas por Codigo de Vendedor");
      gotoxy(10,11);	printf("4. Reportar Ventas por Rango de Fechas");
      gotoxy(10,13);	printf("5. Reportar Ventas de Contado");
      gotoxy(10,15);	printf("6. Reportar Ventas de Credito");
      gotoxy(10,17);	printf("7. Regresar");
      gotoxy(10,20);	printf("Digite su Opcion: ");
      option = validarenteros(1,7,28,20);

      switch(option)
      {
      	case 1:	reportbills(generallist);	break;
         case 2:	reportbillsbyarea(generallist);	break;
         case 3:	reportbillsbycode(generallist);	break;
      	case 4:	reportbillsbydaterange(generallist); break;
         case 5:  reportcashpaymentslist(generallist,cashpaymentslist);     break;
         case 6:  reportcreditpaymentslist(generallist,creditpaymentslist); break;
      }
   }
}

//Procedimiento que crea cuadro del menu principal

void principalframework()
{
	horizontal(25,54,2);
   horizontal(25,54,24);
   vertical(3,23,24);
   vertical(3,23,55);
   esquina(55, 2,187);
   esquina(55,24,188);
   esquina(24,24,200);
   esquina(24, 2,201);
}

//------------------------------------------------------------------------------

//Menú Principal

void principal()
{
	SetConsoleTitle("Facturas Almacen"); // Cambia el nombre de la consola
   _setcursortype(_NOCURSOR);
	int option = 0;
   while(option < 7)
   {
   	clrscr();
      system("Color F0");
      principalframework();
      gotoxy(27,4);	printf("M E N U  P R I N C I P A L");
      gotoxy(27,7);	printf("1. Agregar Facturas");
      gotoxy(27,9);	printf("2. Consultar Facturas");
      gotoxy(27,11);	printf("3. Modificar Facturas");
      gotoxy(27,13);	printf("4. Eliminar Facturas");
      gotoxy(27,15);	printf("5. Generar Facturas");
      gotoxy(27,17);	printf("6. Reportes de Facturas");
      gotoxy(27,19);	printf("7. Salir");
      gotoxy(27,22);	printf("Digite su Opcion: ");
      option = validarenteros(1,9,45,22);

      switch(option)
      {
         case 1:   submenu1();    break;
         case 2:   consultbills(generallist);  break;
         case 3:   modifybill(generallist);    break;
         case 4:   removebill(generallist);    break;
         case 5:
         		{
               	 copycashpaymentslist(generallist);
               	 copycreditpaymentslist(generallist);
                   submenu3();
         		}       break;
      	case 6:   submenu4();     break;
         case 7:   exit(1);
         default:
         {
         	gotoxy(25,20);		printf("Error: Opcion No Valida");
            getch();
         }  break;
      }
   }
}

//------------------------------------------------------------------------------

//MAIN

main()
{
   principal();
	return 0;
}