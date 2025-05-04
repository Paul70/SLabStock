#include "libd/libdutil/constructiondata.h"
#include "libslabstock/application/stockcrawler.h"
#include "libslabstock/database/sqlclient.h"
#include "tests/testbase.h"

using namespace DUTIL;
using namespace SLABSTOCK::App;
using namespace SLABSTOCK::Database;

namespace {
class StockCrawlerTests : public TestBase
{};
}  // namespace

TEST_F(StockCrawlerTests, testWhatAmI)
{
  // StockCrawler sc(ConstructionData().addSubobject<StockCrawler::DBServiceAccess>(
  //     ConstructionData()
  //         .setParameter<SqlClient::SqlDatabaseName>("jdbc:mariadb://localhost:3306/slabstock_test")
  //         .setParameter<SqlClient::SqlDatabaseUser>("test_user")));

  auto cd = ConstructionData();
  StockCrawler sc(cd);

  EXPECT_EQ(sc.whatAmI(), StockCrawler::getClassName());
}

TEST_F(StockCrawlerTests, Test_sendMail)
{
  auto databaseUrl = std::string("jdbc:mariadb://localhost:3306/slabstock_test");
  auto databaseUser = std::string("test_user");

  StockCrawler sc(
      StockCrawler::buildCostructionData(std::move(databaseUrl), std::move(databaseUser)));

  sc.crateDatabase();
  sc.buildStockCollection();
  EXPECT_EQ(sc.whatAmI(), StockCrawler::getClassName());
}
