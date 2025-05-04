#include "stockcrawler.h"
#include "database/sqldatabaseaccess.h"

#include "cpyTa/stockinfofacade.h"
#include "cpyTa/stockmapfacade.h"

#include "libd/libdpython/pythoninterface.h"

#include "cpyTa/protobuf/cpp/stock_info.pb.h"

#include "libcpymail/mail.h"
#include "libcpymail/mailagent.h"

using namespace DUTIL;
using namespace SLABSTOCK::App;
using namespace SlabStock::CPyTa;
using namespace SLABSTOCK::Database;

D_DEFINE_PROCESS(StockCrawler)

ConstructionValidator const& StockCrawler::getConstructionValidator()
{
  using WR = WarelistRule;
  static ConstructionValidator cv(
      {/*no setting rules*/},
      {WR::forSubobject<StockCrawler::DatabaseAccess>(
           "Set a database service object to connect and access the database"),
       {WR::forSubobject<StockCrawler::StockBla>(
           "Set a map containing stock information treated by this class")}});
  return cv;
}

ConstructionData StockCrawler::buildCostructionData(std::string database_url,
                                                    std::string database_user)
{
  using CD = ConstructionData;
  auto sqlDatabaseAccessCD = SqlDatabaseAccess::buildConstructionData(database_url, database_user);

  // clang-format off
  auto stockCrawlerCD = CD().addSubobject<StockCrawler::DatabaseAccess>(std::move(sqlDatabaseAccessCD))
                            .addSubobject<StockCrawler::StockBla>(ConstructionData());
  // clang-format on
  return stockCrawlerCD;
}

StockCrawler::StockCrawler(ConstructionData const& cd) :
    Process(cd),
    database_(getConstructionValidator().buildSubobject<StockCrawler::DatabaseAccess>(cd)),
    stocks_(getConstructionValidator().buildSubobject<StockCrawler::StockBla>(cd))
{}

StockCrawler::~StockCrawler() {}

void StockCrawler::getMail() const
{

  using namespace Slabstock::MailServices;
  auto agent = MailAgent::create();

  // baue mir ein mail object
  DUTIL::ConstructionData cd;
  cd.setParameter<Mail::Subject>("Star Wars")
      .setParameter<Mail::Message>("Obi Wan: Hello there!")
      .addSubobject<Mail::AddressList>(
          DUTIL::ConstructionData().setParameter<Address::MailAddress>("mail@paulheidenreich.com"));
  Slabstock::MailServices::Mail mail(cd);
  agent->send(mail);
}

void StockCrawler::crateDatabase()
{
  database_->queryTable();
  database_->exportValueCallback<std::string>(
      [](std::string input) { std::cout << input << std::endl; });
}

void StockCrawler::buildStockCollection()
{
  database_->queryTable();

  database_->exportValueCallback<std::string>([&](std::string input) {
    std::cout << input << std::endl;
    auto info = StockInfoFacade::createStockInfoInstance(input);
    stocks_->add(input, std::move(info));
  });

  // - perform price analyis buaen
  // - das pyhton module bauen
  // - für mail auch bauen
}

void StockCrawler::requestPriceAnalysis() const
{
  // jetht kann ich hier den analyzer gleich mit dem string füttern
}

std::string StockCrawler::whatAmIImpl() const
{
  return getClassName();
}

bool StockCrawler::updateImpl(SimulationBase& /*sim*/, Event::Id& /*newTargetEvent*/)
{
  return false;
}

bool StockCrawler::finalizeImpl(SimulationBase&)
{
  return true;
}
