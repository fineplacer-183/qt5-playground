#include "tests.h"
#include <pakfile.h>
#include <QFile>
#include <QDebug>
#include <memory.h>

using namespace std;

QByteArray uncompressed;


void colorRed () {
  printf("\033[1;31m");
}

void colorYellow() {
  printf("\033[1;33m");
}

void colorCyan()
{
  printf("\033[0;36m");
}

void colorReset () {
  printf("\033[0m");
}


typedef struct {
  unsigned char msgStart[4]; // 7f 02 00 00
  unsigned char msgRemain[156480];
} msg_t;

msg_t msg;

const unsigned char msgStart[] = { 0x7f, 0x02, 0x00, 0x00 }; 
const unsigned char msgPad[][2] = { { 0xe0, 0x00 },
                                    { 0xc0, 0x00 },
                                    { 0xc0, 0x00 },
                                    { 0x00, 0x00 }
                                  };


struct state;
typedef void state_fn(struct state *);

struct state
{
    state_fn * next;
    int idx; // bytes procesed
    int charsPrinted;
};

state_fn sMsgStart, sMsgRemains, sMsgStats;

void sMsgStats(struct state* state) 
{
  colorYellow();
  printf("\n%05d bytes Processed\n", state->idx);
  state->next = 0;
}

void sMsgRemains(struct  state* state)
{

  #define CH( index ) (unsigned int) uncompressed[state->idx+index] == msgStart[index]

  if (state->idx == uncompressed.length() ) {
    state->next = sMsgStats;
  } else if ( CH(0) && CH(1) && CH(2) && CH(3) ) { 
    state->next = sMsgStart;        
  } else {
    if (state->charsPrinted % 64 == 0) {
      printf("\n");
      state->charsPrinted = 0;
    }
  
    printf("%2.2x", (unsigned int) uncompressed[state->idx]);

    state->idx++;
    state->next = sMsgRemains;
  }
}


void sMsgStart(struct state* state)
{
    state->charsPrinted = 0;
    colorRed();
    printf("\n\n");
    for (int i = 0; i < (int) sizeof(msgStart); i++, state->idx++, state->charsPrinted++) {
      printf("%2.2x", (unsigned int) msgStart[i]);
    }
    colorReset();
    memcpy(msg.msgStart, msgStart, sizeof(msgStart));

    state->next = sMsgRemains;
}





void testArj(const QString fName)
{
  uncompressed = pakfile::arjUncompress(fName.toStdString());

  struct state state = { sMsgRemains, 0 };
  while(state.next) state.next(&state);
  
  printf("\n");
  fflush(stdout);

  qInfo() << "len: " << uncompressed.length() << " size: " << uncompressed.size();
}

int main(int argc, char **argv)
{
  const QString arjFilename  = QString::fromStdString(DOCDATA_PATH "comiss/bga/bga272/ap141629.pak");

  testArj (arjFilename);
}