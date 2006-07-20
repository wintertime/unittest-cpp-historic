#ifndef UNITTEST_XMLTESTREPORTER_H
#define UNITTEST_XMLTESTREPORTER_H

#include "DeferredTestReporter.h"

#include <iosfwd>

namespace UnitTest
{

class XmlTestReporter : public DeferredTestReporter
{
public:
    XmlTestReporter(std::ostream& ostream);

    virtual void ReportSummary(int totalTestCount, int failureCount, float secondsElapsed);

private:
    XmlTestReporter(XmlTestReporter const&);
    XmlTestReporter& operator=(XmlTestReporter const&);

    void AddXmlElement(std::ostream& os, char const* encoding);
    void BeginResults(std::ostream& os, int const testCount, int const failureCount, float const secondsElapsed);
    void EndResults(std::ostream& os);
    void BeginTest(std::ostream& os, DeferredTestResult const& result);
    void AddFailure(std::ostream& os, DeferredTestResult const& result);
    void EndTest(std::ostream& os, DeferredTestResult const& result);

    std::ostream& m_ostream;
};

}

#endif
