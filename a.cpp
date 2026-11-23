#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class PowerPlantAsset {
protected:
    string generatorID;
    bool isGenerating;

public:
    static int activeGenerators;

    PowerPlantAsset(string id) : generatorID(id), isGenerating(true) {
        activeGenerators++;
    }

    virtual ~PowerPlantAsset() {
        activeGenerators--;
    }

    virtual void transmitGridReport() = 0;
};

int PowerPlantAsset::activeGenerators = 0;

class FrancisTurbineModule : virtual public PowerPlantAsset {
protected:
    double waterFlowCubicMetersPerSec;

public:
    FrancisTurbineModule(string id, double flowRate) : PowerPlantAsset(id), waterFlowCubicMetersPerSec(flowRate) {}

    void checkTurbine() {
        cout << "Turbine intake [" << generatorID << "] flow rate: " << waterFlowCubicMetersPerSec << " m3/s." << endl;
    }
};

class SpillwayGateModule : virtual public PowerPlantAsset {
protected:
    double gateOpeningPct;

public:
    SpillwayGateModule(string id, double opening) : PowerPlantAsset(id), gateOpeningPct(opening) {}

    void checkSpillway() {
        cout << "Spillway gate [" << generatorID << "] opening level: " << gateOpeningPct << "%." << endl;
    }
};

class HydroelectricGeneratorUnit : public FrancisTurbineModule, public SpillwayGateModule {
private:
    double powerOutputMW;

public:
    HydroelectricGeneratorUnit(string id, double flowRate, double opening, double output)
        : PowerPlantAsset(id),
          FrancisTurbineModule(id, flowRate),
          SpillwayGateModule(id, opening),
          powerOutputMW(output) {}

    ~HydroelectricGeneratorUnit() {
        cout << "Generator " << generatorID << " decoupled from grid and intake gates closed." << endl;
    }

    void transmitGridReport() override {
        cout << "\n--- Hydroelectric Generator Report: " << generatorID << " ---" << endl;
        checkTurbine();
        checkSpillway();
        cout << "Grid Power Output: " << fixed << setprecision(1) << powerOutputMW << " MW" << endl;
        cout << "Dam Status: Synchronized & Stable" << endl;
    }
};

int main() {
    PowerPlantAsset* unit = new HydroelectricGeneratorUnit("HYDRO-GEN-04", 420.5, 35.0, 680.0);

    unit->transmitGridReport();

    cout << "\nActive Grid Generators: " << PowerPlantAsset::activeGenerators << endl;

    delete unit;

    cout << "Active Generators After Shutdown: " << PowerPlantAsset::activeGenerators << endl;

    return 0;
}
