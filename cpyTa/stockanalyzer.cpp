#include "stockanalyzer.h"
#include "stockinfofacade.h"
#include "stockmapfacade.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

#include "protobuf/cpp/stock_info.pb.h"

using namespace DUTIL;
using namespace SlabStock::CPyTa;

StockAnalyzer::StockAnalyzer(StockMapFacade const& stockMap) :
    stockMap_(stockMap)
{}

StockAnalyzer::~StockAnalyzer()
{
  // needed due to forward declaration of unique_ptr type
}

void StockAnalyzer::performPriceAnalysis(std::vector<std::string> const& symbols) const
{
  if (symbols.empty())
  {
    std::cout << stockMap_.getSerializedMap() << std::endl;
  }
  else
  {
    std::cout << "muss ich noch machen" << std::endl;
  }

  // here execute pyhton code

  // if we get a message back, send a mail

  //next steps:
  //  - python script schreiben, wie das bei mail passiert ist
  //  - python code call from cpp like cpymail
  //  - stockcrawler machen
}

void StockAnalyzer::sendNotification(std::string const& /*message*/) const {}
