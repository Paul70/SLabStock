#ifndef SLABSTOCK_APP_STOCKCRAWLER_H
#define SLABSTOCK_APP_STOCKCRAWLER_H

#include "libslabstock/simulation/process.h"

#include "libd/libdutil/concretefactory.h"
#include "libd/libdutil/namedclass.h"
#include "libd/libdutil/namedreference.h"

namespace SLABSTOCK::Database {
class SqlDatabaseAccess;
}

namespace SlabStock::CPyTa {
class StockMapFacade;
}

namespace SLABSTOCK::App {

/*! \brief description of StockCrawler
 *
 * Longer description of StockCrawler.
 * - crawled die database
 * - erstellt list für TA job, also eine stock collection
 * - was muss ich wissen, nach welchen Kriterien gecrawled wird
 *
 */
class StockCrawler : public Process, public D_NAMED_CLASS(::SLABSSTOCK::App::StockCrawler)
{
  public:
  using Database = std::unique_ptr<SLABSTOCK::Database::SqlDatabaseAccess>;
  using Stocks = std::unique_ptr<SlabStock::CPyTa::StockMapFacade>;

  //! Static factory memeber.
  D_DECLARE_PROCESS(StockCrawler)

  //! Sql Database Access
  D_NAMED_REFERENCE(DatabaseAccess, SLABSTOCK::Database::SqlDatabaseAccess)

  //! Map containing stock information
  D_NAMED_REFERENCE(StockBla, SlabStock::CPyTa::StockMapFacade)

  //! Define set of rules to validate construction data.
  static DUTIL::ConstructionValidator const& getConstructionValidator();

  static DUTIL::ConstructionData buildCostructionData(std::string database_url,
                                                      std::string database_user);

  //! Construct with construction data
  explicit StockCrawler(DUTIL::ConstructionData const& cd);

  ~StockCrawler() override;

  void requestPriceAnalysis() const;

  void getMail() const;

  void crateDatabase();

  void buildStockCollection();

  private:
  virtual std::string whatAmIImpl() const override;
  virtual bool updateImpl(SimulationBase& sim, Event::Id& newTargetEvent) override;
  virtual bool finalizeImpl(SimulationBase&) override;

  Database database_;
  Stocks stocks_;
};

}  // namespace SLABSTOCK::App
#endif  // SLABSTOCK_APP_STOCKCRAWLER_H
