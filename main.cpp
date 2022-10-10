#include <iostream>
#include<stdlib.h>
#include <time.h>  
#include <fstream>
#include <string.h>

using namespace std;

// METODOS 
void menu();
void insertar();
void buscar_codigo();
//void buscar(string);*/
//FORMA CANONICA
void generar_digitos();
void especialidad(char *);
void nombre(char *);
//INDICE
void init();
void insert_index(int, int);
void print();
void sortlista();
int binarysearch(char *);

void llenar_lista();
void showdata(int );
//ATRIBUTOS
//INDICE
typedef struct index{
	int pkey;
	int nrr;
	struct index *next;
} indice;
//PRODUCTO
typedef struct producto{
	char codigo[7]; 
	char nombre[20];
	char descripcion[50];
	char precio[4];
	char especialidad[10];
} pro;
indice *head;
pro p;
//VARIABLES GLOBALES 
int flag, id=0, count=0;

int main(int argc, char** argv) {

	llenar_lista();// LLENA INDICE DE DATOS GUARDADOES EN DISCO
	menu();
	

	return 0;
}

void showdata(int b){
	int l=b*96;
	string word;
	fstream file ("menu.txt", ios::in);
	file.seekg(l,ios_base::beg);
	if(file.is_open())
	{
		for(int i=0; i<5; i++){
			getline(file, word, '|');
			cout<<word;
		}
	
		
	}
	else
	cout<<"Could not open the file\n";
	file.close();
}

void llenar_lista(){
	char c;//VARIABLE PARA LEER CARACTER
	int offset=96;//TAMAÑO DEL REGISTRO
	ifstream f;
	f.open("menu.txt",ios_base::in);
	f.seekg(0,ios_base::beg);// POSICION 0 DEL ARCHIVO DE DATO
	//SUMAR EL VALOR ASCII DEL CARACTER A LA VARIABLE ID
	while(f.get(c)){
		cout<<c;
		id+=c;//LLENAR VALOR ASCII PARA INDICE ORDENADO

		for(int i=0; i<6;i++){
			f.get(c);
			cout<<c;
			id+=c;
		}
		insert_index(id,count);//INSERTAR ID Y NRR AL INDICE
		count++;
		id=0;
		f.seekg(offset,ios_base::beg);//NOS MOVEMOS DE POSICION EN EL ARCHIVO
		offset+=97;// 96 DEL TAMAÑO DEL REGISTRO MÁS EL SALTO DE RENGLON
		cout<<offset<<endl;
		f.get(c);//PARA LEER SALTO DE RENGLON AL FINAL
	}
			
	f.close();
}

//inicializar nodo cabeza del indice
void init(){
	
	head=NULL;
}

//para insertar el indice con la primary key y el nrr
void insert_index(int element, int count){
	indice *nuevo;
	nuevo=(struct index*)malloc(sizeof(struct index));

	nuevo->pkey=element;
	nuevo->nrr=count;
	
	nuevo->next=NULL;//nuevo apunta a nada para evitar basura
	nuevo->next=head;
	head=nuevo;
}
//ordenar lista
void sortlista(){
    struct index *node=NULL, *temp = NULL;
    int tempk, tempn,i=0;//temp variable to store node data
    node = head;
    //temp = node;//temp node to hold node data and next link
    while(node != NULL)
    {
    	
        temp=head; 
        while (temp->next !=NULL)//travel till the second last element 
        {
        	
           if(temp->pkey > temp->next->pkey)// compare the data of the nodes 
            {
              tempk = temp->pkey;
              tempn = temp->nrr;
              
              temp->pkey = temp->next->pkey;// swap the data
              temp->nrr = temp->next->nrr;// swap the data
           
              
              
              temp->next->pkey = tempk;
              temp->next->nrr = tempn;
             
              
            }
            
         temp = temp->next;    // move to the next element 
        }
        node = node->next;    // move to the next node
        
    }
}

struct index* mid_node(index* start, index* last){
   if (start == NULL)
      return NULL;
   struct index* slow = start;
   struct index* fast = start -> next;
   while (fast != last){
      fast = fast -> next;
      if (fast != last){
         slow = slow -> next;
         fast = fast -> next;
      }
   }
   return slow;
}


int binarysearch(char *c){
	int b=0;
	
	for(int i=0;i<7;i++){
		b+=c[i];//suma de codigo para indice
	}
	struct index *first= head, *last= NULL, *mid;
	
	
   	do{
      	index* mid = mid_node(first, last);
      	if (mid == NULL){
      		cout<<"not found";
		  return 0;
	  	}
         
      if (mid->pkey == b){
      	cout<<"found. NRR: ";
		return mid->nrr;
	  }
         
      else if (mid -> pkey < b)
         first = mid -> next;
      else
         last = mid;
   }
   while (last == NULL || last != first);
      cout<<"not found";
		return 0;
}


//imprime indice
void print(){
    if(head==NULL)    //condicion para checar lista vacia
    {
        printf("lista esta vacia\n");
        return;
    }
    struct index *cur=head;            
    int c;//contador del while
    c=0;
    
    fstream f;
	f.open("indice.txt",std::ios_base::out | std::ios_base::trunc);

    while(cur!=NULL)                  //la iteracion recorre hasta que obtiene el nodo NULL
    {
        printf("\n pkey: %d, nrr: %d, ->",cur->pkey,cur->nrr); 
		f<<cur->pkey; 
		f<<" ";
		f<<cur->nrr; 
		f<<"\n";
        c++;                      //cuenta el numero de nodos en la lista
        cur=cur->next;                //mueve el puntero al siguiente nodo y obtine valor
    }
    f.close();
    printf("NULL\n");
    printf("numero de nodos %d\n",c);
}

//metodos de ingreso de datos
void menu(){
	int op;
	do{
	sortlista();
	cout<<"\n1. Insertar registro \n2. Mostrar un registro por Codigo \n3. Ver indice \n4. Salir:\t";
	cin>>op;
	
	
		switch(op){
			case 1:
				insertar();//insertar registro
				break;
			case 2:
				buscar_codigo(); //busca codigo sin indice
				break;
			case 3:
				print();
				break;
			case 4:
				exit;//salir
				break;
			default:
				cout<<"not a valid option\n";
		}
	}while (op!=4);

}

void insertar(){
	int n;

	fflush(stdin);//limpiar buffer
	//entrada de datos por el usuario por medio del teclado
	cout<<"ingrese los siguientes datos del producto\n";
	cout<<"nombre: ";
	cin.getline(p.nombre, 20);
	cout<<"descripcion: ";
	cin.getline(p.descripcion,50);
	cout<<"precio: ";
	cin>>p.precio;
	fflush(stdin);
	cout<<"especialidad: ";
	cin.getline(p.especialidad,10);
	
	//generar codigo de forma canonica
	generar_digitos();//genera dos numeros aleatorios
	especialidad(p.especialidad);//generar letra de especialidad
	nombre(p.nombre);//generar 3 letras del nombre
	
	// metodo para insertar datos en el archivo
	fstream file;//instancia de archivo
	file.open("menu.txt", std::ios::app);
	if (file.is_open()){
		
		//iteracion para insertar nuevos registro en el indice
		for(int i=0;i<7;i++){
			cout<<p.codigo[i];//imprimir en pantalla
			id+=p.codigo[i];//suma de codigo para indice
			file<<p.codigo[i];//guardo codigo en disco
		
		}
		
		insert_index(id,count);
		count++;
		id=0;
		file<<"|";//poner delimitados
		cout<<"|";
		//iteracion para guardar nombre en disco
		for(int i=0;i<20;i++){
			cout<<p.nombre[i];
			file<<p.nombre[i];//escribir nombre en disco
			p.nombre[i]=0;//re inicializar arreglo
		}
		file<<"|";
		cout<<"|";
		
		for(int i=0;i<50;i++){
			cout<<p.descripcion[i];
			file<<p.descripcion[i];//escribir nombre en disco
			p.descripcion[i]=0;
		}
		file<<"|";
		cout<<"|";
		
		
		for(int i=0;i<4;i++){
			cout<<p.precio[i];
			file<<p.precio[i];//escribir nombre en disco
			p.precio[i]=0;
		}
		file<<"|";
		cout<<"|";
		for(int i=0;i<10;i++){
			cout<<p.especialidad[i];
			file<<p.especialidad[i];//escribir nombre en disco
			p.descripcion[i]=0;
		}
		cout<<"|\n";
		file<<"\n";
		
		file.close();
	}
	else cout << "Unable to open file";
	
	fflush(stdin);

}

void buscar_codigo(){
	char c[7];
	int b;
	cout<<"introduzca codigo: ";
	cin>>c;
	b=binarysearch(c);
	if(b)
		showdata(b);
}

/*void buscar(string c){
	string line;
	fstream file;
	file.open("menu.txt");
	for(unsigned int curLine = 0; getline(file, line); curLine++) {
	    if (line.find(c) != string::npos) {
	        cout << "found: " << c << " line: " << curLine << endl;
	    }
	}
	file.close();
}
*/

//metodos para la forma canonica
void generar_digitos(){
	
	int r;
	//se usan numeros ascii para generar caracteres
	//48 es 0 y 57 es 9
	srand(time(0));
	r = (rand() % (57 - 48 + 1)) + 48;
	p.codigo[0]=r;//guardar primer numero en posicion cero
	r = (rand() % (57 - 48 + 1)) + 48;
	p.codigo[1]=r;//guardar primer numero en posicion uno
	
	cout<<"\n";

}

void especialidad(char *e){
	flag=0;
	
	if (e[2]=='z'||e[2]=='Z')//posicion 3 numeros naturales
		p.codigo[2]=80;//80 es el numero ascii para pe mayuscula
	else if(e[2]=='c'||e[2]=='C'){
		p.codigo[2]=80;//80 es el numero ascii para pe mayuscula
		p.codigo[3]=73;//73 es el numero ascii para i mayuscula
		flag=1;//bandera para posicionar el nombre
	}
	else if(e[0]=='h'||e[0]=='H')
		p.codigo[2]=72;//72 es el numero ascii para ache mayuscula
	else if(e[0]=='b'||e[0]=='B')
		p.codigo[2]=66;//66 es el numero ascii para be mayuscula
	else
		p.codigo[2]='0';//poner cero si no es especialidad valida


}

void nombre(char *n){
	//condicion para rellenar la forma canonica con las letras del nombre si la especialidad es picar
	if (flag){
		p.codigo[4]=p.nombre[0];
		p.codigo[5]=p.nombre[1];
		p.codigo[6]=p.nombre[2];
	}
	else{
		p.codigo[3]=p.nombre[0];
		p.codigo[4]=p.nombre[1];
		p.codigo[5]=p.nombre[2];
	}
	
}

