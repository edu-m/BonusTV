#include <iostream>
#include "tvlist.h"
#include <cstring>
#include <fstream>

using namespace std;
int parseDisplaySize(string);

void writeToFile(List<TV> &odata)
{
    ofstream myfile;
    myfile.open("samsungOrdinato.txt");
    myfile << "32 POLLICI"<<endl;
    for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
    {
        if (parseDisplaySize(app->getValue().getModel()) == 32)
            myfile << "TV di Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
    }
    myfile << endl;
    myfile << "49 POLLICI"<<endl;
    for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
    {
        if (parseDisplaySize(app->getValue().getModel()) == 49)
            myfile << "TV di Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
    }
    myfile << endl;
    myfile << "55 POLLICI"<<endl;
    for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
    {
        if (parseDisplaySize(app->getValue().getModel()) == 55)
            myfile << "TV di Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
    }
    myfile << endl;
    myfile << "60 POLLICI"<<endl;
    for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
    {
        if (parseDisplaySize(app->getValue().getModel()) == 60)
            myfile << "TV di Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
    }
    myfile << endl;
    myfile << "65 POLLICI"<<endl;
    for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
    {
        if (parseDisplaySize(app->getValue().getModel()) == 65)
            myfile << "TV di Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
    }
    myfile.close();
}

void loadFile(string idata, List<TV> &list)
{
    ifstream ifs(idata, ifstream::in);
    Node<TV> *app;
    while (ifs.good())
    {
        TV s;
        ifs >> s;
        Node<TV> *temp = new Node<TV>(s);
        list.insert(temp);
    }
    ifs.close();
}

int parseDisplaySize(string myWord)
{
    char myArray[14];
    strcpy(myArray, myWord.c_str());
    if ((int(myArray[0]) <= 57 && int(myArray[0]) >= 48))
    {
        string ds = myWord.substr(0, 2);
        return stoi(ds);
    }
    else if ((int(myArray[2]) <= 57 && int(myArray[2]) >= 48))
    {
        string ds = myWord.substr(2, 2);
        return stoi(ds);
    }
    return 0;
}

int main()
{
    List<TV> masterTVList; 
    loadFile("samsung.txt", masterTVList);

    writeToFile(masterTVList);
}
