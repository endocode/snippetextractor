#include <QString>
#include <QtTest>

#include "Helpers.h"
#include "Process.h"

class MarkdownFilterTests : public QObject
{
    Q_OBJECT

public:
    MarkdownFilterTests();

private Q_SLOTS:
    void testIncludeSample();
};

MarkdownFilterTests::MarkdownFilterTests()
{
}

void MarkdownFilterTests::testIncludeSample()
{
    const QString result = process(":/data/testresources/include-sample.md.in");
    QVERIFY(!result.isEmpty());
    QCOMPARE(result.trimmed(), u("//test"));
}

QTEST_APPLESS_MAIN(MarkdownFilterTests)

#include "tst_MarkdownFilterTests.moc"
