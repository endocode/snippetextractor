#include <QString>
#include <QByteArray>

#include <QtTest>

#include "Exception.h"
#include "Helpers.h"
#include "Process.h"

class MarkdownFilterTests : public QObject
{
    Q_OBJECT

public:
    MarkdownFilterTests();
private:
    QByteArray loadResource(const QString& path);

private Q_SLOTS:
    void testIncludeSample();
    void testErrorOnMissingSnippet();
};

MarkdownFilterTests::MarkdownFilterTests()
{
}

QByteArray MarkdownFilterTests::loadResource(const QString &path)
{
    QFile input(path);
    if (!input.open(QIODevice::ReadOnly)) {
        Q_ASSERT_X(false, Q_FUNC_INFO, "resource cannot be opened");
    }
    return input.readAll();
}

void MarkdownFilterTests::testIncludeSample()
{
    const QString result = process(":/data/testresources/include-sample.md.in");
    const QString expected = loadResource(":/data/testresources/include-sample.md");
    QCOMPARE(result, expected);
}

void MarkdownFilterTests::testErrorOnMissingSnippet()
{
    try {
        const QString result = process(":/data/testresources/missing-sample.md.in");
        QFAIL("Missing samples should result in errors!");
    } catch (const Exception&) {
        //all good
    }
}

QTEST_APPLESS_MAIN(MarkdownFilterTests)

#include "tst_MarkdownFilterTests.moc"
