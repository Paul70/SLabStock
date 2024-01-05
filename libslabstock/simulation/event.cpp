#include "event.h"
#include "callback.h"

#include "libd/libdutil/constructiondata.h"
#include "libd/libdutil/constructionvalidator.h"

using namespace DUTIL;
using namespace SLABSTOCK;

ConstructionValidator const& Event::getConstructionValidator()
{
  using SR = SettingRule;
  using WR = WarelistRule;
  static ConstructionValidator cv(
      {[]() {
         SR sr = SR::forNamedParameter<Event::IdParam>(SR::Usage::MANDATORY_WITH_DEFAULT,
                                                       "Set the unique event Id.");
         sr.minimalValue = -1;
         sr.defaultValue = -1;
         return sr;
       }(),
       SR::forNamedParameter<Event::Description>(SR::Usage::MANDATORY_NO_DEFAULT,
                                                 "Event description."),
       []() {
         SR sr = SR::forNamedEnum<Event::State>(SR::Usage::MANDATORY_WITH_DEFAULT,
                                                "Set the event state.");
         sr.defaultValue = toString(Event::State::NOT_SCHEDULED);
         return sr;
       }()},
      {WR::forSubobjectList<Event::CallbackList>(
          "Define list of event callbacks registered during construction of this event.")});
  return cv;
}

Event::Event(DUTIL::ConstructionData const& cd, LoggingSinkPointer sink) :
    LoggingSource(sink),
    value_(std::make_unique<ConstructionData>(cd)),
    callbacks_(getConstructionValidator().buildSubobjectList<Event::CallbackList>(cd))
{
  // log message
}

Event::~Event() {}

Event::Id Event::getId() const
{
  auto cv = getConstructionValidator();
  return cv.validateNamedParameter<Event::IdParam>(*value_);
}

Event::State Event::getState() const
{
  auto cv = getConstructionValidator();
  return cv.validateNamedEnum<Event::State>(*value_);
}
