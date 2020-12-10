


#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <tr1/memory>

using namespace std;


class Investment {
 private:
        string nume;
        double inv;
        string incr;

        void update() {
            double r= (0.1 * rand() / RAND_MAX - 0.02);
            if (r > 0)
                incr = " --> ";
            else
                incr = " <--";
            inv *= r+1;
        }

public:
    Investment(string nume, double inv) : nume(nume), inv(inv), incr(" == ") {};

    double get_val() {
        //update();
        return inv;
    }


    void print_val()
    {
        update();
        cout << incr << inv << endl;
    }
};

Investment* createInvestment(string nume, double inv)
{
    Investment *a =new Investment(nume, inv);
    return a;
}

void f()
{
    cout << "Item13: alocare cu auto_ptr\n";

    double f_initial = 1000;

    std::auto_ptr<Investment> pInv(createInvestment("Fondul de investiti", f_initial));

    for (int i = 0; i < 10; i++)
    {
        pInv->print_val();
    }

    std::auto_ptr<Investment> pInv2(pInv);

    cout << "Fondul 2 este " << pInv2->get_val() << endl;
    if (!(pInv.get() == nullptr))
        cout << "Fondul 1 este " << pInv->get_val() << endl;
    else
        cout << "Fondul (obiectul) de la pInv a fost mutat la pInv2 - pInv este null\n";

}

void g() {
    cout << "\nItem13: alocare cu shared_ptr\n";

    double f_initial = 1000;

    std::tr1::shared_ptr<Investment>pInv(createInvestment("Fondul de investiti C", f_initial));
    for (int i = 0; i < 10; i++)
    {
        pInv->print_val();
    }

    cout << "\nevolutie pINv2 \n";
    std::tr1::shared_ptr<Investment>pInv2(pInv);;
	cout<< "Val pInv2 dupa copiere: " <<pInv2->get_val()<<"\n";
    for (int i = 0; i < 10; i++)
    {
        pInv2->print_val();
    }
    cout << "\ndin nou pInv "<< pInv->get_val()<<"\n";


}

// Item 14

std::mutex m;
int i = 0;


class Lock {
private:
    std::mutex* mutexPtr;

public:
    explicit Lock(std::mutex* pm) : mutexPtr(pm)
    {
        mutexPtr->lock();
    }

    ~Lock() { mutexPtr->unlock(); }

private:
    Lock& operator=(const Lock& a) = delete;
    Lock (Lock & Lock) = delete;
};

void thcount(string nume)
{
    //m.lock();
    std::this_thread::sleep_for(std::chrono::microseconds(rand()%1000));
    Lock ml(&m);
   // Lock ml2(&m);

   // ml2 = ml;      //eroare - operatorul de copiere implicit dezactivat
   // Lock ml3(ml);  //eroare -copierea prin constructor dezactivata

    std::cout << i << " Hello " << nume<<std::endl;
    i++;
    //m.unlock();
}

void item14()
{
    cout << "\nItem14: mutex utilizand clasa Lock \n";
    std::thread t1(thcount,"t1");

    std::thread t2(thcount,"t2");

    std::thread t3(thcount,"t3");

    t1.join();
    t2.join();
    t3.join();
}

int main()
{
    f();
    g();
    item14();
    return 0;
}
