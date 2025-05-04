#ifndef SLABSTOCK_STOCK_H
#define SLABSTOCK_STOCK_H

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/projectware.h"

#include <string>

namespace DUTIL {
struct ConstructionData;
}

namespace SlabStock::CPyTa::protobuf {
class StockInfo;
}

namespace SlabStock::CPyTa {

/*! \brief description of Stock
 *
 * Longer description of Stock.
 */

class StockInfoFacade final :
    public DUTIL::ProjectWare,
    public D_NAMED_CLASS(::SLABSTOCK::CPyTa::StockInfoFacade)
{
  public:
  using SharedStockInfo = std::shared_ptr<CPyTa::protobuf::StockInfo>;
  using UniqueStockInfo = std::unique_ptr<CPyTa::protobuf::StockInfo>;

  //! Declare static factory member
  D_DECLARE_PROJECTWARE(StockInfoFacade)

  //! Named parameter containing the stock symbol/identifier
  D_NAMED_STRING(Symbol)

  //! Named parameter containing the company name
  D_NAMED_STRING(Company)

  //! Named parameter containing the company's unique ISIN identifier.
  D_NAMED_STRING(ISIN)

  //! Named boolean parameter indicating the possess state of the stock.
  D_NAMED_BOOL(Possess)

  //! Named integer parameter holding the number of heldt stocks of this type.
  D_NAMED_LABEL(Number)

  //! A string containing a serialized protobuf StockInfo instance used to construct
  //! the underlying StockInfo member of this class. If this optional string is given,
  //! other construction paramenters are ignored.
  D_NAMED_STRING(Serilization);

  //! Return construction requirements.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  //! Get ConstructionData to build a class instance .
  static UniqueStockInfo createStockInfoInstance(std::string const& symbol,
                                                 std::string const& company = {},
                                                 std::string const& isin = {}, bool possess = false,
                                                 int number = 0);

  //! Construct with construction data
  explicit StockInfoFacade(DUTIL::ConstructionData const& cd);

  explicit StockInfoFacade(SharedStockInfo stockInfo);

  ~StockInfoFacade() override;

  std::string getSymbol() const;
  std::string getCompanyName() const;
  std::string getISIN() const;
  bool getPossessState() const;

  private:
  SharedStockInfo info_;
};

}  // namespace SlabStock::CPyTa
#endif  // SLABSTOCK_STOCK_H
