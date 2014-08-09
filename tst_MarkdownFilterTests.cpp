#include <QString>
#include <QtTest>

class MarkdownFilterTests : public QObject
{
    Q_OBJECT

public:
    MarkdownFilterTests();

private Q_SLOTS:
    void testCase1();
};

MarkdownFilterTests::MarkdownFilterTests()
{
}

void MarkdownFilterTests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(MarkdownFilterTests);

#include "tst_MarkdownFilterTests.moc"
