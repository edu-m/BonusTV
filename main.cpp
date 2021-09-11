#include <iostream>
#include "tvlist.h"
#include <cstring>
#include <fstream>

using namespace std;
int parseDisplaySize(string);

void pullDataFromMaster(ofstream &myfile, unsigned short size, List<TV> &odata)
{
    myfile << size << " POLLICI" << endl;
    for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
    {
        if (parseDisplaySize(app->getValue().getModel()) == size)
            myfile << "TV di Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
    }
    myfile << endl;
}

void writeToFile(List<TV> &odata)
{
    ofstream myfile;
    myfile.open("samsungOrdinato.txt");
    pullDataFromMaster(myfile, 32, odata);
    pullDataFromMaster(myfile, 49, odata);
    pullDataFromMaster(myfile, 55, odata);
    pullDataFromMaster(myfile, 60, odata);
    pullDataFromMaster(myfile, 65, odata);
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
