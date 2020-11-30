#ifndef KarateExtractor_h
#define KarateExtractor_h

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "TTree.h"
#include "TFile.h"


class MonitorElement;
class PixelDigi;
class Phase2TrackerDigi;
class TrackerGeometry;

class KarateExtractor : public DQMEDAnalyzer {
public:
  explicit KarateExtractor(const edm::ParameterSet&);
  ~KarateExtractor() override;
  void bookHistograms(DQMStore::IBooker& ibooker, edm::Run const& iRun, edm::EventSetup const& iSetup) override;
  void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) override;

  struct DigiMEs {
    MonitorElement* NumberOfDigisPerDet;
    MonitorElement* DigiOccupancyP;
    MonitorElement* DigiOccupancyS;
    MonitorElement* ChargeXYMap;
    MonitorElement* PositionOfDigisP;
    MonitorElement* PositionOfDigisS;
    MonitorElement* ChargeOfDigis;
    MonitorElement* ChargeOfDigisVsWidth;
    MonitorElement* TotalNumberOfDigisPerLayer;
    MonitorElement* NumberOfHitDetectorsPerLayer;
    MonitorElement* NumberOfClustersPerDet;
    MonitorElement* ClusterWidth;
    MonitorElement* ClusterPositionP;
    MonitorElement* ClusterPositionS;
    MonitorElement* FractionOfOvTBits;
    MonitorElement* FractionOfOvTBitsVsEta;
    MonitorElement* EtaOccupancyProfP;
    MonitorElement* EtaOccupancyProfS;
    unsigned int nDigiPerLayer;
    unsigned int nHitDetsPerLayer;
  };

  MonitorElement* XYPositionMap;
  MonitorElement* RZPositionMap;
  MonitorElement* XYOccupancyMap;
  MonitorElement* RZOccupancyMap;

private:
  void bookLayerHistos(DQMStore::IBooker& ibooker, unsigned int det_id, const TrackerTopology* tTopo);
  void fillITPixelDigiHistos(const edm::Handle<edm::DetSetVector<PixelDigi>> handle,
                             const edm::ESHandle<TrackerGeometry> gHandle);
  void fillOTDigiHistos(const edm::Handle<edm::DetSetVector<PixelDigi>> handle,
                        const edm::ESHandle<TrackerGeometry> gHandle);

  edm::ParameterSet config_;
  std::map<unsigned int, DigiMEs> layerMEs;
  //  std::map<unsigned int, std::map<unsigned int ,DigiMEs>> ringMEs;
  bool pixelFlag_;
  uint eventCounter_;
  uint adc_;
  uint row_;
  uint col_;
  uint rawid_;
  TTree* hitTree_;
  //TTree* hitTree_;
  std::string geomType_;
  edm::InputTag otDigiSrc_;
  edm::InputTag itPixelDigiSrc_;
  const edm::EDGetTokenT<edm::DetSetVector<PixelDigi>> otDigiToken_;
  const edm::EDGetTokenT<edm::DetSetVector<PixelDigi>> itPixelDigiToken_;
  edm::ESHandle<TrackerTopology> tTopoHandle_;
};
#endif
