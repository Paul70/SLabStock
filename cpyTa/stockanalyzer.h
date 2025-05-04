#ifndef SLABSTOCK_CPYTA_STOCKANALYZER_H
#define SLABSTOCK_CPYTA_STOCKANALYZER_H

#include <string>
#include <vector>

namespace DUTIL {
struct ConstructionData;
}

namespace SlabStock::CPyTa {
class StockMapFacade;

/*! \brief description of StockCollection
 *
 * Longer description of StockCollection.
 */

class StockAnalyzer
{
  public:
  //! Construct with construction data
  explicit StockAnalyzer(StockMapFacade const& stockMap);

  ~StockAnalyzer();

  void performPriceAnalysis(std::vector<std::string> const& symbols = {}) const;

  private:
  void sendNotification(std::string const& message) const;

  StockMapFacade const& stockMap_;
};

// class PyStockAnalyzer : public StockAnalyzer
// {};

}  // namespace SlabStock::CPyTa
#endif  // SLABSTOCK_CPYTA_STOCKANALYZER_H
