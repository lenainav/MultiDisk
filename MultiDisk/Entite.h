#ifndef ENTITE_H_INCLUDED
#define ENTITE_H_INCLUDED

///////////
///     Transfer to new file "Entity.h"
///////////

#define ISFILE  0   //to replace with the code
#define ISDIR   1

typedef struct Entity Entity;
struct Entity                   ///Entity descriptor
{
    uint8_t     type;           //file or directory?
    size_t      id;             //id of the element
    char*       name;           //entity name

                                ///if DIR
    Entity**    elements;       //elements in the dir
    size_t      nelem;          //number of elements

                                ///if FILE
    size_t      addr;           //address of the file (in the full disk)
    size_t      size;           //size of the file;

};


Entity*     ent_init();         ///create in memory

void        ent_free(           ///free in memory
                Entity* ent;    //entity
                     );

size_t      ent_entaddr(        ///Return the address of the end of the file, -1 if fail
                Entity* ent;    //Entity
                        );





#endif // ENTITE_H_INCLUDED
