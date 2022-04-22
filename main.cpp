#include <iostream>
#include "tvlist.h"
#include <cstring>
#include <fstream>
#define INIT_STRING "Inserisci nome file da ordinare senza includere l'estensione (.txt): "

using namespace std;
using tvlist = List<TV>;
int parseDisplaySize(string);

void pullDataFromMaster(ofstream &myfile, unsigned short *sizeArray, unsigned short n, tvlist &odata)
{
    bool found;
    for (int i = 0; i < n; i++)
    {
        myfile << sizeArray[i] << " POLLICI" << endl;
        found = false;
        for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
        {
            if (parseDisplaySize(app->getValue().getModel()) == sizeArray[i])
            {
                myfile << "TV di Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
                if (found == false)
                    found = true;
            }
        }
        if (!found)
            myfile << "\t\t**NESSUN MODELLO TROVATO**" << endl;
        myfile << endl;
    }
}

void writeToFile(string file, tvlist &odata)
{
    ofstream myfile;
    myfile.open(file + "Ordinato.txt");

    int i = 0;            // size count
    unsigned short k[15]; // max value;
    cout << "Inserisci dimensione (0 per fermarsi): ";
    while (1)
    {
        cout << "Inserisci dimensione: ";
        cin >> k[i];
        if (k[i] != 0)
            i++;
        else
            break;
    }
    if (i == 0)
        exit(0);
    unsigned short sizeArray[i];
    for (int j = 0; j < i; j++)
    {
        sizeArray[j] = k[j];
    }
    pullDataFromMaster(myfile, sizeArray, i, odata);
    cout << "File di testo ordinato creato." << endl;
    myfile.close();
}

void loadFile(string idata, tvlist &list)
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
    char arr[14];

    strcpy(arr, myWord.c_str());
    if ((int(arr[0]) <= 57 && int(arr[0]) >= 48))
    {
        string ds = myWord.substr(0, 2);
        return stoi(ds);
    }
    else if ((int(arr[2]) <= 57 && int(arr[2]) >= 48))
    {
        string ds = myWord.substr(2, 2);
        return stoi(ds);
    }
    return 0;
}

void init(tvlist &masterTVList, string file)
{
    loadFile(file + ".txt", masterTVList);
    writeToFile(file, masterTVList);
}

int main()
{
    tvlist masterTVList;
    string file;

    cout << INIT_STRING;
    cin >> file;
    init(masterTVList, file);
}
