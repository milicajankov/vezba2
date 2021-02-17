#include <iostream>
#include <vector>

using namespace std;

class Datum{
    int mesec;
    int godina;
public:
    Datum(int m, int g): mesec(m), godina(g){ }
    friend bool operator == (const Datum &d1, const Datum &d2){
        return (d1.mesec == d2.mesec) == (d1.godina == d2.godina);
    }
    friend bool operator != (const Datum &d1, const Datum &d2){
        return !(d1==d2);
    }
    friend ostream& operator << (ostream& out, const Datum &d){
        out << d.ispis();
        return out;
    }
    string ispis()const{
        return string("(") + to_string(mesec) + "/" + to_string(godina) + ")";

    }

};
class Karta{
    int id;
public:
    Karta(int i): id(i){ }
    virtual string stampa()const{
        return to_string(id);
    }
    virtual bool valjanost(int cena, Datum d)=0;
    virtual void setIznos(double x)=0;

    friend ostream& operator << (ostream& out, const Karta &k){
        out << k.stampa();
        return out;
    }
};
class Mesecna : public Karta{
    string ime;
    Datum d;
public:
    Mesecna(int id, string i, Datum dd): ime(i), d(dd), Karta( id) { }
    bool valjanost(int x, Datum dd){
        return (dd==d);
    }
    string stampa()const{
        return ime + " " + Karta::stampa() + d.ispis();
    }
    void setIznos(double x){
    }
 //   void produzi(int x){}
};
class Pojedinacna : public Karta{
    double iznos=50.;
public:
    Pojedinacna(int id, double iz): Karta(id), iznos(iz) { }

    bool valjanost(int x, Datum dd){
        if (iznos>=x){
            iznos-=x;
            return true;
        }
        return false;
    }
    double getIznos()const{
        return iznos;
    }
    void setIznos(double x){
          iznos+=x;
    }
    string stampa()const{
        return Karta::stampa() + " " + to_string(iznos);
    }
};
class AparatZaProveru{
    vector<Karta*> skup;
public:
    AparatZaProveru()=default;
    void dodaj(Karta* k){
        skup.push_back(k);
    }
    void provera(int x, Datum d){
        for(auto i=0;i<skup.size();++i){
            bool ok= skup[i]->valjanost(x, d);
            cout << skup[i]->stampa();
            if(ok)
                cout << "Karta je valjana." << endl;
                else
                cout << "Karta nije valjana." << endl;
        }
    }
    void doplata(double x){
        for(auto i=0;i<skup.size();++i){
                skup[i]->setIznos(x);                                   //poziv setIznos(x);
        }
    }

    friend ostream& operator << (ostream &out, const AparatZaProveru &a){//kad ovo ne radi, razlog je sto u baznoj klasi nije
    out << "Sadrzaj:" <<  endl;                                         //preklopljen operator <<
        for(auto p: a.skup)
           out << ( *p ) << endl;
        return out;

    }

};
int main()
{
    AparatZaProveru a;
    a.dodaj(new Pojedinacna(1, 30));
    a.dodaj(new Pojedinacna(2, 40));
    a.dodaj(new Mesecna(1, "milica jankov", Datum(2,2005)));
    a.dodaj(new Mesecna(2, "x x x x x x x ", Datum(4,2020)));

    a.provera(33, Datum(6,2021));
    cout << a << endl;

    a.doplata(12);
    cout << a << endl;
    return 0;
}
