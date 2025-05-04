#ifndef SLABSTOCK_STOCKCOLLECTION_H
#define SLABSTOCK_STOCKCOLLECTION_H

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/projectware.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SlabStock::CPyTa::protobuf {
class StockInfo;
class StockMap;
}  // namespace SlabStock::CPyTa::protobuf

namespace SlabStock::CPyTa {
class StockInfoFacade;

/*! \brief description of StockCollection
 *
 * Longer description of StockCollection.
 */

class StockMapFacade final :
    public DUTIL::ProjectWare,
    public D_NAMED_CLASS(::SlabStock::CPyTa::StockCollection)
{
  public:
  using StockList = std::unique_ptr<SlabStock::CPyTa::protobuf::StockMap>;

  //! Declare static factory member
  D_DECLARE_PROJECTWARE(StockMapFacade)

  //! A serialization of the underlying protobuf StockMap attribute
  D_NAMED_STRING(SerializedMap)

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  static DUTIL::ConstructionData buildConstrutionData(std::string const& serilizedMap = {});

  //! Construct with construction data
  explicit StockMapFacade(DUTIL::ConstructionData const& cd);

  ~StockMapFacade();

  std::string getSerializedMap() const;

  void add(std::string key, std::unique_ptr<SlabStock::CPyTa::protobuf::StockInfo> stock_info);

  std::vector<std::string> getKeyList() const;

  private:
  //! A protobuf definef map containing all protobuf StockInfo instances.
  //! The stock ticker symbol serves as map key to access the StockInfo object.
  StockList map_;
};

}  // namespace SlabStock::CPyTa
#endif  // SLABSTOCK_STOCKCOLLECTION_H
