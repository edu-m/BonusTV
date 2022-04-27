#include <iostream>
#include "tvlist.h"
#include <cstring>
#include <fstream>
#include <sys/stat.h>
#define EXT ".txt"

using tvlist = List<TV>;
using namespace std;
int parseDisplaySize(string);

void pullDataFromMaster(ofstream &myfile, List<int> *tvSizes, unsigned short n, tvlist &odata)
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
                myfile << "Marca: " << app->getValue().getBrand() << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
                if (!found)
                    found = !found;
            }
        }
        if (!found)
            myfile << "\t\t**NESSUN MODELLO TROVATO**" << endl;
        myfile << endl;
    }
}

void exitErrNoData()
{
    cerr << "Nessun dato e' stato inserito, chiusura del programma.\n";
    exit(EXIT_FAILURE);
}

void writeToFile(string file, tvlist &odata)
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
        exitErrNoData();

    pullDataFromMaster(myfile, &tvSizes, i, odata);
    cout << "File di testo ordinato creato." << endl;
    myfile.close();
}

void loadFile(string idata, tvlist &list)
{
    ifstream ifs(idata, ifstream::in);
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

int parseDisplaySize(string str)
{
    char arr[14]; // max length of SN is 14

    strcpy(arr, str.c_str());
    if ((uint_fast16_t(arr[0]) <= 57 && uint_fast16_t(arr[0]) >= 48))
        return stoi(str.substr(0, 2));
    if ((uint_fast16_t(arr[2]) <= 57 && uint_fast16_t(arr[2]) >= 48))
        return stoi(str.substr(2, 2));
    return -1; // errsize
}

inline bool fileExists(const string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

string sanitizeFileName(string str) // filename must contain ".txt"
{
    if (str.find(".txt") != string::npos)
        return str;
    return str + ".txt";
}

int main()
{
    tvlist masterTVList;
    string file;
    do
    {
        cout << "Inserisci nome file da ordinare: ";
        cin >> file;
        if (!fileExists(sanitizeFileName(file)))
        cerr << "File non trovato: \'" << sanitizeFileName(file) << "\'\n";
    } while (!fileExists(sanitizeFileName(file)));
    loadFile(sanitizeFileName(file), masterTVList);
}
