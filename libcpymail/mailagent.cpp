#include "mailagent.h"
#include "mail.h"

#include "libd/libdpython/pythoninterface.h"
#include "libd/libdpython/venv.h"
#include "libd/libdutil/constructiondata.h"

#include "protobuf/mailsettings.pb.h"

using namespace DPYTHON;
using namespace DUTIL;
using namespace Slabstock::MailServices;

std::unique_ptr<MailAgent> MailAgent::create()
{
  return std::make_unique<MailAgent>();
}

void MailAgent::sendImpl(Mail const& mail) const
{
  Venv venv(ConstructionData().setParameter<Venv::PythonExe>("./.venv/bin/python3"));
  venv.activate();

  cpymail::protobuf::MailSettings settings;
  settings.add_to_addresses(mail.getAddresses());
  settings.set_subject(mail.getSubject());
  settings.set_message(mail.getMessage());

  auto resultString = DPYTHON::runPythonCode(std::filesystem::path("cpymail.py"), "cpy_send_mail",
                                             settings.SerializeAsString());

  cpymail::protobuf::RequestResult result;
  result.ParseFromString(resultString);
  if (result.status_code() != 200)
  {
    return;
  }
}
