#ifndef angola_h
#define angola_h

typedef struct angola *Angola;

#define START_TAGGING tag()
#define STOP_TAGGING trace()

Angola mkAngola();
void unmkAngola();

void addId(Angola a, char* str);
void addAuthor(Angola a, char* str);
void addTag(Angola a, char* str);
void addTitle(Angola a, char* str);
void addCategory(Angola a, char* str);
void addText(Angola a, char* str);

void tag();
void trace();

#endif