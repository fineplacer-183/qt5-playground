#ifndef _PAKFILE_H
#define _PAKFILE_H

#include <QByteArray>
#include <string>

class pakfile
{
private:
  /* data */
  QByteArray dataCompressed;
  QByteArray dataUncompressed;
  
private:
  union {
    typedef struct {
      char header[2];
      char dummy[256000-2];
    } structBytes;
    char bytes[256000];
  } u;

public: /* compression stuff */
  static QByteArray arjUncompress(std::string filename, std::string password="screen");
  static QByteArray arjCompress(const QByteArray &data, std::string password="screen");
  static QByteArray zlibUncompress(const QByteArray &data);
  static QByteArray zlibCompress(const QByteArray &data);
  static void zErr(int ret);

public:
  pakfile(/* args */);
  ~pakfile();
};

#endif // _PAKFILE_H