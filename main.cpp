#include <iostream>
#include "tvlist.h"
#include <cstring>
#include <fstream>
#include <algorithm>
#include "banned.h"
#include <sys/stat.h>
#define EXT ".txt"

using tvlist = List<TV>;
using namespace std;
int parseDisplaySize(string);

void insertEntry(Node<TV> *app, ofstream &myfile, bool *found)
{
    string uppercaseBrandString = app->getValue().getBrand();
    transform(uppercaseBrandString.begin(), uppercaseBrandString.end(), uppercaseBrandString.begin(), ::toupper);
    myfile << "Marca: " << uppercaseBrandString << ", EAN: " << app->getValue().getEAN() << ", Modello: " << app->getValue().getModel() << endl;
    if (!*found)
        *found = true;
}

void pullDataFromMaster(ofstream &myfile, List<int> *tvSizes, unsigned short n, tvlist &odata)
{
    bool found;
    for (Node<int> *i = tvSizes->getHead(); i != NULL; i = i->getNext())
    {
        myfile << "\t\t\t\t\t" << i->getValue() << " POLLICI\n";
        found = false;
        for (Node<TV> *app = odata.getHead(); app != NULL; app = app->getNext())
            if (parseDisplaySize(app->getValue().getModel()) == i->getValue())
                insertEntry(app, myfile, &found);
        if (!found)
            myfile << "\t\t\t**NESSUN MODELLO TROVATO**\n\n";
        else
            myfile << "\n";
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
    myfile.open(file.substr(0, file.length() - 4) + "_ordinato.txt");
    unsigned short i;
    List<int> tvSizes;

    cout << "Inserisci dimensione (0 per fermarsi): " << endl;
    while (i != 0)
    {
        cout << "Inserisci dimensione: ";
        cin >> i;
        if (!tvSizes.isNodePresent(i) && i != 0)
            tvSizes.insert(i);
    }
    if (tvSizes.getLength() == 0)
        exitErrNoData();
    pullDataFromMaster(myfile, &tvSizes, i, odata);
    cout << "File di testo ordinato creato." << endl;
    myfile.close();
    exit(EXIT_SUCCESS);
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
    if (uint8_t(str[0]) <= 57 && uint8_t(str[0]) >= 48)
        return stoi(str.substr(0, 2));
    if (uint8_t(str[2]) <= 57 && uint8_t(str[2]) >= 48)
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
    if (str.find(EXT) != string::npos)
        return str;
    return str + EXT;
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