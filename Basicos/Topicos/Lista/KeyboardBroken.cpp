#include <iostream>
#include <string>
using namespace std;

#include <iostream>

using namespace std;

template<class T> struct LinkedList{
	/*Definimos el Nodo*/
	struct Node{
		Node* next; /*Apunta al siguiente nodo*/
		T data;

		Node(T val){	/*Constructor Node*/
			next = NULL;
			data = val;
		}
	}; //Cierra definicion del nodo
	
	/*Cabeza,Cola y tamaño de la lista*/
	Node* head;
	Node* tail;
	int size = 0;

	LinkedList(){ /*Constructor de la LinkedList*/
		head = tail = NULL;
		size = 0;
	}

	/*Función push_back: Agrega elementos y enlaza*/
	void push_back(T val){
		Node* node = new Node(val);
		if (size==0){
			head = tail = node;
		}else{
			tail->next = node;	/*Se enlaza el nodo siguiente*/
			tail = node;		/*Y se establece la cola de la lista*/
		}
		size++;					/*La lista aumenta de tamaño*/
	}//cierra función push_back

	/*Función pop_back: Saca elementos y enlaza*/
	void pop_back(){
		if (size==0){
			throw runtime_error("Cannont erase from the empty list");
		}
		if (size==1){
			head = tail = NULL;
		}else{
			Node* prev = head;
			Node* last = head->next;

			while(last && last->next){ //Mientras no lleguen al ultimo elemento
				prev = prev->next;
				last = last->next;
			}
			prev->next = NULL;  /*Se convertira en la cola (tail), y next=null*/
			tail = prev;		
		}
		size--;
	}//cierra funcion pop_back

	/*Funcion exists: válida si un elemento está en la lista*/
	bool exists(T value){
		if (size==0){
			return false;
		}

		Node* current = head;
		while(current){  /*Vamos a recorrer la lista*/
			if (current->data == value){ /*Hace match con algun elemento*/
				return true;
			}
			current = current->next; /*Avanzará a través de los nodos*/
		}
		return false;
	}//cierra funcion exists.

	int length(){
		return size;
	}
}; 

int main(){
	LinkedList<char>* left  = new LinkedList<char>();
	LinkedList<char>* rigth = new LinkedList<char>();
	string sentece="";
	while(getline(cin,sentece)){
		bool is = false;

		for (int i = 0; i < sentece.size(); i++){
			if (sentece[i]=='[' || sentece[i]==']'){ /* encontro: [ */
				if (sentece[i]=='[')
					is = true;
				else
					is = false;

				if (rigth->head){
					if (left->head){
						rigth->tail->next = left->head;
						rigth->tail = left->tail;
					}
					left = rigth;
					rigth = new LinkedList<char>();
				}
				continue;
			}else{
				if (is)
					rigth->push_back(sentece[i]);
				else
					left->push_back(sentece[i]);
			}				
		}

		if(rigth->head){
			rigth->tail->next = left->head;
			rigth->tail = left->tail;
			left = rigth;
		}
		while(left->head){
			cout<<left->head->data;
			left->head = left->head->next;
		}
		cout << "\n";
		left = new LinkedList<char>();
		rigth = new LinkedList<char>();
	}//cierra while de getline
}//cierra main