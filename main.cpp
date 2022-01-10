#include <iostream>
#include "tvlist.h"
#include <cstring>
#include <fstream>

using namespace std;
int parseDisplaySize(string);

void pullDataFromMaster(ofstream &myfile, List<int> *tvSizes, unsigned short n, List<TV> &odata)
{
    bool found;
    for (Node<int> *i = tvSizes->getHead(); i != NULL; i = i->getNext())
    {
        myfile << i->getValue() << " POLLICI" << endl;
        found = false;
        for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
        {
            if (parseDisplaySize(app->getValue().getModel()) == i->getValue())
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

void writeToFile(string file, List<TV> &odata)
{
    ofstream myfile;
    myfile.open(file.erase(file.length() - 4, 4) + "Ordinato.txt");

    unsigned short i;
    List<int> tvSizes;

    cout << "Inserisci dimensione (0 per fermarsi): " << endl;
    while (1)
    {
        cout << "Inserisci dimensione: ";
        cin >> i;
        if (i == 0)
            break;
        if (!tvSizes.isNodePresent(i))
            tvSizes.insert(i);
    }
    if (tvSizes.getLength() == 0)
        exit(0);

    pullDataFromMaster(myfile, &tvSizes, i, odata);
    cout << "File di testo ordinato creato." << endl;
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
    writeToFile(idata, list);
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

int main()
{
    List<TV> masterTVList;
    string file;

    cout << "Inserisci nome file da ordinare senza includere l'estensione (.txt): ";
    cin >> file;

    loadFile(file + ".txt", masterTVList);
}
