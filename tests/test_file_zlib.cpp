#include "tests.h"
#include <pakfile.h>
#include <QFile>

using namespace std;

void testZlib(const QString fName)
{
  QFile file(fName);

  if (!file.open(QIODevice::ReadOnly))
    ASSERT_THROW("Filenotfound" == nullptr);

  QByteArray compressed = file.readAll();

  QByteArray uncompressed = pakfile::zlibUncompress(compressed);
  QByteArray filedata =  "Hallo\nWelt";

  ASSERT_THROW(0 != uncompressed.compare(compressed));
  ASSERT_THROW(0 == uncompressed.compare(filedata));

  file.close();
}

int main(int argc, char **argv)
{
  const QString zlibFileName = QString::fromStdString(TESTS_PATH "data/file_zlib.pak");

  testZlib(zlibFileName);
}