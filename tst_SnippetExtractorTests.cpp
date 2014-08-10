#include <QString>
#include <QByteArray>

#include <QtTest>

#include "Exception.h"
#include "Helpers.h"
#include "Process.h"

class SnippetExtractorTests : public QObject
{
    Q_OBJECT

public:
    SnippetExtractorTests();
private:
    QByteArray loadResource(const QString& path);

private Q_SLOTS:
    void testIncludeSample();
    void testErrorOnMissingSnippet();
};

SnippetExtractorTests::SnippetExtractorTests()
{
}

QByteArray SnippetExtractorTests::loadResource(const QString &path)
{
    QFile input(path);
    if (!input.open(QIODevice::ReadOnly)) {
        Q_ASSERT_X(false, Q_FUNC_INFO, "resource cannot be opened");
    }
    return input.readAll();
}

void SnippetExtractorTests::testIncludeSample()
{
    const QString result = process(":/data/testresources/include-sample.md.in");
    const QString expected = loadResource(":/data/testresources/include-sample.md");
    QCOMPARE(result, expected);
}

void SnippetExtractorTests::testErrorOnMissingSnippet()
{
    try {
        const QString result = process(":/data/testresources/missing-sample.md.in");
        QFAIL("Missing samples should result in errors!");
    } catch (const Exception&) {
        //all good
    }
}

QTEST_APPLESS_MAIN(SnippetExtractorTests)

#include "tst_SnippetExtractorTests.moc"
