#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;

class Lista;
class Nod{
protected:
    Nod* next;
    int info;
    static int n; //var statica pt a nr obiectele
public:
    Nod(); //constructor initializare
    Nod(Nod*,int); //constructor parametrizat
    virtual ~Nod(); //destructor nod
    Nod(Nod&); //constructor de copiere

    void setInfo(int info){this->info=info;} //setter pt info
    void setNext(Nod* next){this->next=next;} //setter pt next
    Nod* getNext(){return next;} //getter pt next
    int getInfo(){return info;} //getter pt info

    Nod& operator=(Nod &); //supraincarcarea operatorului de atribuire =

    virtual void citire(istream& in); //functia de citire
    friend istream& operator>>(istream& in, Nod& n); //supraincarcarea op de citire >>

    virtual void afisare(ostream& out); //functia de afisare
    friend ostream& operator<<(ostream& out, Nod& n); //supraincarcarea op de afisare <<

    static void nrObiecte(){ // metoda statica de afisare a numarului de obiecte
        cout<<n;
    }

    friend class Lista;
    friend class Lista_circulara;
};
int Nod::n; //declaram variabila

Nod::Nod(){
    this->info=0; //initializam campul de info cu 0
    this->next=NULL; //initializam adresa urmatorului elem
    n++; //numaram obiectele de tip Nod
}
Nod::Nod(Nod* next,int info){
    this->info=info; //actualizam campul de info
    this->next=next;
}
Nod::~Nod(){
    delete[] next;
}
Nod::Nod(Nod &n){
    this->info = n.info; //copiam info in alt nod
    this->next = n.next;
}
Nod& Nod::operator=(Nod &n){
    this->info=n.info;
    this->next=n.next;
}
void Nod::citire(istream& in){
    cout<<"Introduceti info: ";
    in>>info;
}
istream& operator>>(istream& in,Nod& n){
    n.citire(in);
    return in;
}
void Nod::afisare(ostream& out){
    out<<"Info introdusa este: "<<info<<endl;
}
ostream& operator<<(ostream& out, Nod& n){
    n.afisare(out);
    return out;
}

class Nod_dublu:public Nod{
private:
    Nod* prev;
public:
    Nod_dublu(); //constructor de initilaizare
    Nod_dublu(Nod*, int, Nod*); //constructor parametrizat
    Nod_dublu(Nod_dublu&); //constructor de copiere
    ~Nod_dublu(); //destructor

    Nod_dublu& operator=(Nod_dublu &); //supraincarcarea operatorului de atribuire =

    void setPrev(Nod* prev){this->prev=prev;} //setter pt next
    Nod* getPrev(){return prev;} //getter pt prev

    friend class Lista;
};
Nod_dublu::Nod_dublu():Nod()
{
    this->prev=NULL; //initializam adresa catre elementul anterior din LDI
}
Nod_dublu::Nod_dublu(Nod* next,int info, Nod* prev):Nod(next, info){

    this->prev=prev; //facem leg pt lista dublu inlantuita
}
Nod_dublu::~Nod_dublu(){
    delete prev;
}
Nod_dublu::Nod_dublu(Nod_dublu &n){
    this->prev=n.prev;
}
Nod_dublu& Nod_dublu::operator=(Nod_dublu &n){
    Nod::operator=(n);
    this->prev=n.prev;
}
class Lista{
protected:
    Nod_dublu* prim;
    Nod_dublu* ultim;
    static int l; //nr cate ob de tip lista
public:
    Lista(); //constructor de initializare
    Lista(Nod_dublu*,Nod_dublu*); //constructor parametrixat
    Lista(Lista&); //constructor de copiere
    virtual ~Lista(); //destructor lista

    void setPrim(Nod_dublu* prim){this->prim=prim;} //setter prim
    Nod_dublu* getPrim(){return prim;} //getter prim

    void setUltim(Nod_dublu* ultim){this->ultim=ultim;} //setter ultim
    Nod_dublu* getUltim(){return ultim;} //getter ultim

    void adaugare(int info,int poz); //metoda publica de adaugare a unui nod pe o anumita pozitie

    void stergere(int);  //metoda publica stergere a unui nod pe o anumita pozitie

    virtual void citire(istream& in); //metoda publica de citire a unei liste
    friend istream& operator>>(istream& in, Lista& l); //supraincarcarea operatorului de citire >>

    virtual void afisare(ostream& out);  //metoda publica de afisare a unei liste
    friend ostream& operator<<(ostream& out, Lista& l);  //supraincarcarea operatorului de afisare <<

    Lista& operator=(Lista &); //supraincarcarea operatorului de atribuire =

     static void numarObiecte(){ // metoda statica de afisare a numarului de obiecte de tip lista
        cout<<l;
    }
};
int Lista::l; //declaram variabila

Lista::Lista(){
    this->prim=NULL;
    this->ultim=NULL;
    l++;
}
Lista::Lista(Nod_dublu* prim, Nod_dublu* ultim){
    this->prim=prim;
    this->ultim=ultim;
}
Lista::~Lista(){
    Nod_dublu* curr=prim;
    Nod_dublu* aux;
    while(curr!=NULL){
        aux=(Nod_dublu*)curr->next;
        free(curr);
        curr=aux;
    }
}
Lista::Lista(Lista& l){
    this->prim=l.prim;
    this->ultim=l.ultim;
}
void Lista::adaugare(int info,int poz){
     int i;
     Nod_dublu* nodnou=new Nod_dublu; //nodul pe care il vom adauga
     Nod_dublu* curr=new Nod_dublu; //curr este nodul curent cu care parcurgem lista
         if(prim==NULL) //daca lista e goala noul nodul nou adaugat va fi si primul si ultim nod al listei
        {
            nodnou->info=info;
            prim=ultim=nodnou;
            prim->prev=NULL;
            ultim->next=NULL;
        }
     else
    {
         curr=prim; //actualizam nodul curent cu primul nod pentru a parcurge lista
         i=1;
         while(i<poz-1 and curr!=NULL)
         {
             curr=(Nod_dublu*) curr->next; //parcurgem lista pana ajungem la pozitia pe care vrem sa adaugam noul nod
             i++;
         }
        if(poz==1)
         {
             nodnou->info=info;
             nodnou->next=prim;
             nodnou->prev=NULL;
             prim->prev=nodnou;
             prim=nodnou;
         }
         else if(curr==ultim) //daca vrem sa adaugam la finalul listei
         {
             nodnou->info=info;
             nodnou->next=NULL;
             nodnou->prev=ultim;
             ultim->next=nodnou;
             ultim=nodnou;
         }

     }
}
void Lista::stergere(int poz){
    if (prim==NULL)return;
    Nod_dublu* curr = prim;
    if (poz==0)
    {
        prim=(Nod_dublu*)curr->next;
        free(curr);
        return;
    }
    for (int i=0;curr!=NULL && i<poz-1; i++)
         curr = (Nod_dublu*)curr->next;
    if (curr == NULL || curr->next == NULL)
         return;
    Nod_dublu* next = (Nod_dublu*)curr->next->next;
    free(curr->next);
    curr->next = next;
}
Lista& Lista::operator=(Lista &l){
    this->ultim=l.ultim;
    this->prim=l.prim;
}
void Lista::citire(istream& in){
    int n,info;
    cout<<"Introduceti nr de elem al listei: ";
    in>>n;
    cout<<"Enumarati elem listei: ";
    for(int i=1;i<=n;i++)
    {
        Nod_dublu* nodnou=new Nod_dublu;
        in>>info;
        adaugare(info,i);
    }
}
istream& operator>>(istream& in, Lista& l){
    l.citire(in);
    return in;
}
void Lista::afisare(ostream& out){
    Nod_dublu* curr=prim;
    out<<"Lista este: ";
    while(curr!=NULL and curr->next!=prim)
    {
        out<<curr->info<<" ";
        curr=(Nod_dublu*)curr->next;
    }
    out<<endl;
}
ostream& operator<<(ostream& out, Lista& l){
    l.afisare(out);
    return out;
}
class Lista_circulara:public Lista{
public:
    Lista_circulara();
    Lista_circulara(Nod_dublu*, Nod_dublu*);
    ~Lista_circulara();

    void adaugare_circulara(int info);

    void citire(istream& in); //metoda publica de citire a unei liste
    friend istream& operator>>(istream& in, Lista_circulara& ); //supraincarcarea operatorului de citire >>

    void afisare(ostream& out);  //metoda publica de afisare a unei liste
    friend ostream& operator<<(ostream& out, Lista_circulara& );  //supraincarcarea operatorului de afisare <<

    Lista_circulara& operator=(Lista_circulara &); //supraincarcarea operatorului de atribuire =

    int Josephus(int, int);

};
Lista_circulara::Lista_circulara():Lista(){}
Lista_circulara::Lista_circulara(Nod_dublu* prim, Nod_dublu* ultim):Lista(prim,ultim){

    ultim->next=prim;
    ultim=(Nod_dublu*)prim->getPrev();
    prim=ultim;
}
Lista_circulara::~Lista_circulara(){

}
void Lista_circulara::adaugare_circulara(int info){
    Nod_dublu* nodnou=new Nod_dublu;
        nodnou->info =info;
    if(prim == NULL){
        prim = nodnou;
        ultim = nodnou;
        nodnou->next = prim;
    }
    else {
        ultim->next = nodnou;
        nodnou->setPrev(ultim);
        ultim = nodnou;
        ultim->next = prim;
        prim->setPrev(ultim);
    }
}
void Lista_circulara::citire(istream &in){
    /*
    int n,info;
    cout<<"Introduceti nr de elem al listei dublu inlantuite ciculare: ";
    in>>n;
    cout<<"Enumarati elem listei dublu inlantuite circulare: ";
    for(int i=1;i<=n;i++)
    {
        Nod_dublu* nodnou=new Nod_dublu;
        in>>info;
        adaugare_circulara(info);
    }
    */
    cout<<"***Se foloseste functia de citire din derivata pentru ca am folosit virtual in baza***"<<endl;
    Lista::citire(in);
}
void Lista_circulara::afisare(ostream &out){
    out<<"***Se apeleaza afisarea din derivata pentru ca am folosit virtual in baza***"<<endl;
    Lista::afisare(out);
}
istream& operator>>(istream& in,Lista_circulara& L){
    L.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Lista_circulara& L){
    L.afisare(out);
    return out;
}
Lista_circulara& Lista_circulara::operator=(Lista_circulara &l){
    Lista::operator=(l);
}
int Lista_circulara::Josephus(int n, int m){ //n este nr de elem al listei, iar m nr din cate in cate elem merge

/*
    while((Nod_dublu*)prim->next!=NULL) //sterg elem din lista circulara pana cand ajung sa am un singur elem
    {
        int k=0;
        while(k!=m) //parcurg lista pana cand k ajunge sa fie egal cu pozitia de pe care trebuie sa sterg
        {
            prim=(Nod_dublu*)prim->next; //iterez prin lista
            k++; //incrementez pana ajung la poz
        }
        if(k==m)
            stergere(k); //sterg elem
    }
    */
    if (n == 1 or m==0)
        return 1;
    else
        return (Josephus(n - 1, m) + m-1) % n + 1;

}
///Mentionez ca meniul a fost luat din cadrul laboratorului de POO.
void menu_output(){
    cout<<"\n Lapadus Raluca 254 - Proiect 2 - Nume proiect: Liste de numere întregi 2  \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citim n obiecte: "; cout<<"\n";
    cout<<"2. Afisam cele n obiecte: "; cout<<"\n";
    cout<<"3. Stergem un nod al listei: "; cout<<"\n";
    cout<<"4. Metoda Josephus:"; cout<<"\n";
    cout<<"5. Numarare obiecte static: "; cout<<"\n";
    cout<<"6. UPCASTING: "; cout<<"\n";
    cout<<"7. DOWNCASTING: "; cout<<"\n";
    cout<<"0. Iesire."; cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;
    int n=0,x,k,info,poz,p;
    Lista_circulara *L;

    do
    {
        menu_output();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if (option==1)
        {
            cout<<"Introduceti nr de liste: ";
            cin>>n;
            L = new Lista_circulara[n];
            for (int i=0; i<n; i++)
                cin>>L[i];
        }
        if (option==2)
        {
             for (int i=0;i<n;i++)
            {
                cout<<L[i]<<endl;
            }
        }
        if (option==3)
        {
            cout<<"Introduceti pozitia de pe care vreti sa fie sters nodul: ";
            cin>>x;
            cout<<"Alegeti lista din care vreti sa stergeti: ";
            cin>>k;
            L[k].stergere(x);
                cout<<L[k]<<endl;
        }
        if (option==4)
        {

           Lista_circulara L;
           int n,m;
           cout<<"Introduceti nr de elem ale listei in care doriti sa se aplice metoda Josephus: ";
           cin>>n;
           cout<<"Introduceti din cate in cate elem sa fie sters elem conform metodei Josephus: ";
           cin>>m;
           cin>>L;
           cout<<"Elementul ramas dupa metoda lui Josephus este: "<<L.Josephus(n,m)<<endl;

        }
        if (option==5)
        {
            Lista_circulara L1,L2;
            cout<<"Avem ";
            Lista::numarObiecte();
            cout<<" obiecte de tip lista"<<endl;
            Nod N1,N2,N3;
            cout<<"Avem ";
            Nod::nrObiecte();
            cout<<" obiecte de tip nod"<<endl;
        }
        if  (option==6)
        {
            cout<<" Nod *n=new Nod_dublu; \n cin>>*n; \n cout<<*n;";
        }
        if (option==7)
        {
            cout<<" Nod_dublu *nd=(Nod_dublu*)new Nod; \n cin>>*nd; \n cout<<*nd;";
        }
        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }
        if (option<0||option>8)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause");
        system("cls");
    }
    while(option!=0);
}
int main()
{
    menu();

    ///UPCASTING - am transformat un nod intr-un nod_dublu
    //Nod *n=new Nod_dublu;
    //cin>>*n;
    //cout<<*n;

    ///DOWNCASTING - am transformat un nod_dublu intr-un nod
   // Nod_dublu *nd=(Nod_dublu*)new Nod;
    //cin>>*nd;
    //cout<<*nd;
   return 0;
}
