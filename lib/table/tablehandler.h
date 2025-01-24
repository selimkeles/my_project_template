// tablehandler.h
#ifndef TABLEHANDLER
#define TABLEHANDLER
#include "functionprototypes.h"
/*  LET US CREATE ENUMERATION BASED ON OUR TABLE
    This block creates enum with month names
*/
#define ITEM(a, b, c) a,
enum {
#include "table.h"
};
#undef ITEM

/*  LET US CREATE struct BASED ON OUR TABLE
    This block creates struct with uint8_t members named after months respectively
    We could use c parameters and defined them like strings ie.
    #define ITEM(a, b, c) uint8_t *a[c];
*/
#define ITEM(a, b, c) char a;
typedef struct __attribute__((packed)) {
#include "table.h"
} configItems_t;
#undef ITEM

/*  Lastly we can create constant struct
    to be able to used as lookuptable
*/

typedef long(*func_name)(int);
typedef struct
{
    char name[LAST][10];
    func_name func[LAST];
    int value[LAST];
}lookupTable_t;
#define ITEM(a, b, c) #a,
#define ITEM_FUNC(a, b, c) b,
#define ITEM_VALUE(a, b, c) c,
extern const lookupTable_t lookupTable = {
    .name = {
        #include "table.h"
    },
    .func = {
        #include "table.h"
    },
    .value = {
        #include "table.h"
    }
};
#undef ITEM
#undef ITEM_FUNC
#undef ITEM_VALUE


#endif // TABLEHANDLER
