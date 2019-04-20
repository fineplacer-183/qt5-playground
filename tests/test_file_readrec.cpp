#include "tests.h"
#include <pakfile.h>
#include <QFile>

using namespace std;

void testBasic(const QString fName)
{
  QFile file(fName);

  if (!file.open(QIODevice::ReadOnly))
    ASSERT_THROW("Filenotfound" == nullptr);

  QByteArray compressed = file.readAll();

  QByteArray uncompressed = pakfile::zUncompress(compressed);
  QByteArray filedata =  "Hallo\nWelt";

  ASSERT_THROW(uncompressed.compare(compressed) != 0);
  ASSERT_THROW(uncompressed.compare(filedata)  == 0);

}


int main(int argc, char **argv)
{
  const QString fileName = QString::fromStdString(TESTS_PATH "data/file_readrec.pak");

  testBasic(fileName);
}