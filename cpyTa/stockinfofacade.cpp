#include "stockinfofacade.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

#include "protobuf/cpp/stock_info.pb.h"

using namespace DUTIL;
using namespace SlabStock::CPyTa;

D_DEFINE_PROJECTWARE(StockInfoFacade)

ConstructionValidator const& StockInfoFacade::getConstructionValidator()
{
  using SR = SettingRule;
  static const DUTIL::ConstructionValidator cv(
      {SR::forNamedParameter<StockInfoFacade::Symbol>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                      "Company short name or symbol/stock-ticker"),
       SR::forNamedParameter<StockInfoFacade::Company>(SR::Usage::OPTIONAL, "Company long name"),
       SR::forNamedParameter<StockInfoFacade::ISIN>(SR::Usage::OPTIONAL, "Company ISIN identifier"),
       []() {
         auto sr = SR::forNamedParameter<StockInfoFacade::Possess>(
             SR::Usage::MANDATORY_WITH_DEFAULT, "Inidicator showing stock possess state");
         sr.defaultValue = false;
         return sr;
       }(),
       []() {
         auto sr = SR::forNamedParameter<StockInfoFacade::Number>(
             SR::Usage::MANDATORY_WITH_DEFAULT,
             "Number of currently held stocks from of this company.");
         sr.defaultValue = 0;
         return sr;
       }()});
  return cv;
}

StockInfoFacade::UniqueStockInfo StockInfoFacade::createStockInfoInstance(
    std::string const& symbol, std::string const& company, std::string const& /*isin*/,
    bool /*possess*/, int /*number*/)
{
  auto info = std::make_unique<CPyTa::protobuf::StockInfo>();
  info->set_symbol(symbol);
  info->set_name(company);
  return info;
}

StockInfoFacade::StockInfoFacade(ConstructionData const& cd) :
    info_(std::make_unique<CPyTa::protobuf::StockInfo>())
{
  auto cv = getConstructionValidator();
  info_->set_symbol(cv.validateNamedParameter<StockInfoFacade::Symbol>(cd));
}

StockInfoFacade::StockInfoFacade(StockInfoFacade::SharedStockInfo stockInfo) :
    info_(stockInfo)
{}

StockInfoFacade::~StockInfoFacade() {}

std::string StockInfoFacade::getSymbol() const
{
  return info_->symbol();
}

std::string StockInfoFacade::getCompanyName() const
{
  return info_->name();
}

std::string StockInfoFacade::getISIN() const
{
  return "";
}

bool StockInfoFacade::getPossessState() const
{
  return "";
}

// void Stock::setPossessState(bool inPossess)
// {
//   possess_ = inPossess;
// }
