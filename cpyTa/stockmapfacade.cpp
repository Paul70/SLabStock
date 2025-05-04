#include "stockmapfacade.h"
#include "stockinfofacade.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

#include "protobuf/cpp/stock_map.pb.h"

using namespace DUTIL;
using namespace SlabStock::CPyTa;

D_DEFINE_PROJECTWARE(StockMapFacade)

ConstructionValidator const& StockMapFacade::getConstructionValidator()
{
  using SR = SettingRule;
  static const DUTIL::ConstructionValidator cv(
      {SR::forNamedParameter<StockMapFacade::SerializedMap>(
          SR::Usage::OPTIONAL, "Seialized string cotaining a state of protobuf StockMap object.")});
  return cv;
}

ConstructionData StockMapFacade::buildConstrutionData(std::string const& serilizedMap)
{
  return ConstructionData().setParameter<StockMapFacade::SerializedMap>(serilizedMap);
}

StockMapFacade::StockMapFacade(ConstructionData const& cd) :
    map_(std::make_unique<protobuf::StockMap>())
{
  auto serializedMap = getConstructionValidator()
                           .validateNamedParameter<StockMapFacade::SerializedMap>(cd)
                           .value();
  if (!serializedMap.empty())
  {
    map_->ParseFromString(serializedMap);
  }
}

StockMapFacade::~StockMapFacade()
{
  // needed due to forward declaration of unique_ptr type
}

std::string StockMapFacade::getSerializedMap() const
{
  return map_->SerializeAsString();
}

void StockMapFacade::add(std::string key, std::unique_ptr<protobuf::StockInfo> stock_info)
{
  map_->mutable_map()->insert({key, *std::move(stock_info)});
}

std::vector<std::string> StockMapFacade::getKeyList() const
{
  std::vector<std::string> keyList{};
  keyList.reserve(map_->map_size());
  for (const auto& ele : map_->map())
  {
    keyList.push_back(ele.first);
  }
  return keyList;
}

// std::vector<std::string> StockMapFacade::getStockSymbolList() const
// {
//   std::vector<std::string> symbols{};
//   symbols.reserve(map_.size());
//   for (const auto& [key, value] : map_)
//   {
//     symbols.push_back(key);
//   }
//   return symbols;
// }
