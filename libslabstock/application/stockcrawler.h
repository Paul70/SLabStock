#ifndef SLABSTOCK_APP_STOCKCRAWLER_H
#define SLABSTOCK_APP_STOCKCRAWLER_H

#include "simulation/process.h"

namespace DUTIL {
struct ConstructionData;
}

namespace SLABSTOCK::App {

/*! \brief description of StockCrawler
 *
 * Longer description of StockCrawler.
 */

class StockCrawler : public Process
{
  public:
  //! Construct with construction data
  explicit StockCrawler(DUTIL::ConstructionData const& cd);

  private:
  // database access
};

}  // namespace SLABSTOCK::App
#endif  // SLABSTOCK_APP_STOCKCRAWLER_H
