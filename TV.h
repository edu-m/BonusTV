#include <fstream>
#include <string>

class TV
{
private:
    //EAN,MARCA,MODELLO,SCART,API,API_APERTE,TERRESTRE,DVB-T2,HEVC,SATELLITARE,VIA_CAVO
    std::string ean;
    std::string brand;
    std::string model;
    bool scart;
    bool api;
    bool apio;
    bool terrestrial;
    bool t2;
    bool hevc;
    bool satellite;
    bool cable;

public:
    //constructors
    TV(std::string e, std::string b, std::string m, bool sct, bool ap, bool apo, bool tr, bool t2,
       bool h, bool sat, bool cbl) : ean(e), brand(b), model(m), scart(sct), api(ap), apio(apo),
                                     terrestrial(tr), t2(t2), hevc(h), satellite(sat), cable(cbl) {}
    TV() : TV("undefined", "undefined", "undefined", 0, 0, 0, 0, 0, 0, 0, 0) {}

    std::string getEAN()
    {
        return this->ean;
    }
    std::string getBrand()
    {
        return this->brand;
    }
    std::string getModel()
    {
        return this->model;
    }
    bool isScart()
    {
        return this->scart;
    }
    bool isAPI()
    {
        return this->api;
    }
    bool isAPIO()
    {
        return this->apio;
    }
    bool isTerrestrial()
    {
        return this->terrestrial;
    }
    bool isT2()
    {
        return this->t2;
    }
    bool isHEVC()
    {
        return this->hevc;
    }
    bool isSatellite()
    {
        return this->satellite;
    }
    bool isCable()
    {
        return this->cable;
    }

    void setEAN(std::string e)
    {
        this->ean = e;
    }
    void setBrand(std::string b)
    {
        this->brand = b;
    }
    void setModel(std::string m)
    {
        this->model = m;
    }
    void isScart(bool s)
    {
        this->scart = s;
    }
    void isAPI(bool a)
    {
        this->api = a;
    }
    void isAPIO(bool a)
    {
        this->apio = a;
    }
    void isTerrestrial(bool t)
    {
        this->terrestrial = t;
    }
    void isT2(bool t)
    {
        this->t2 = t;
    }
    void isHEVC(bool h)
    {
        this->hevc = h;
    }
    void isSatellite(bool s)
    {
        this->satellite = s;
    }
    void isCable(bool c)
    {
        this->cable = c;
    }
    friend ostream &operator<<(ostream &out, const TV &app)
    {
        out << "EAN: " << app.ean << ", ";
        out << "MARCA: " << app.brand << ", ";
        out << "MODELLO: " << app.model << ", ";
        out << "SCART: ";
        if (app.scart)
            out << "SI";
        else
            out << "NO";
        out << ", ";

        out << "API: ";
        if (app.api)
            out << "SI";
        else
            out << "NO";
        out << ", ";

        out << "API_APERTE: ";
        if (app.apio)
            out << "SI";
        else
            out << "NO";
        out << ", ";

        out << "TERRESTRE: ";
        if (app.terrestrial)
            out << "SI";
        else
            out << "NO";
        out << ", ";

        out << "DVB-T2: ";
        if (app.t2)
            out << "SI";
        else
            out << "NO";
        out << ", ";

        out << "HEVC: ";
        if (app.hevc)
            out << "SI";
        else
            out << "NO";
        out << ", ";

        out << "SATELLITARE: ";
        if (app.satellite)
            out << "SI";
        else
            out << "NO";
        out << ", ";

        out << "VIA_CAVO: ";
        if (app.cable)
            out << "SI";
        else
            out << "NO";

        return out;
    }
    bool isTrue(std::string k)
    {
        if (k == "n/a" || k == "NO" || k == "n.a.")
            return 0;
        return 1;
    }
    friend istream &operator>>(istream &in, TV &p)
    {
        std::string ean;
        std::string brand;
        std::string model;
        std::string scart; //to bool
        std::string api;
        std::string apio;
        std::string terrestrial;
        std::string t2;
        std::string hevc;
        std::string satellite;
        std::string cable; //to bool

        getline(in, ean, ',');
        getline(in, brand, ',');
        getline(in, model, ',');
        getline(in, scart, ',');
        getline(in, api, ',');
        getline(in, apio, ',');
        getline(in, terrestrial, ',');
        getline(in, t2, ',');
        getline(in, hevc, ',');
        getline(in, satellite, ',');
        getline(in, cable, '\n');

        p.setEAN(ean);
        p.setBrand(brand);
        p.setModel(model);
        p.isScart(p.isTrue(scart));
        p.isAPI(p.isTrue(api));
        p.isAPIO(p.isTrue(apio));
        p.isTerrestrial(p.isTrue(terrestrial));
        p.isT2(p.isTrue(t2));
        p.isHEVC(p.isTrue(hevc));
        p.isSatellite(p.isTrue(satellite));
        p.isCable(p.isTrue(cable));

        return in;
    }
    bool operator==(const TV &s) const
    {
        return this->model == s.model;
    }
};