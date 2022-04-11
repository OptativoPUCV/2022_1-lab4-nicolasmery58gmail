#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  
  

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *mapa = (HashMap*)malloc(sizeof(HashMap));
  mapa->buckets = (Pair**)malloc(sizeof(Pair*)*capacity);
  for(int i; i<capacity; i++){
    mapa->buckets[i] = NULL;
  }
  mapa->capacity = capacity;
  mapa->size = 0;
  mapa->current = -1;
    return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
  

}

Pair * searchMap(HashMap * map,  char * key) {   
  
  
    return NULL;
}

Pair * firstMap(HashMap * map) {
  long aux = 0;
  
  while(map->buckets[aux] == NULL || map->buckets[aux]->key == NULL){
    
    aux = (aux+1)%map->capacity;
  }
  map->current = aux;
  return map->buckets[aux];
}

Pair * nextMap(HashMap * map) {

  map->buckets[map->current] = map->buckets[map->current+1];
  return map->buckets[map->current];
  
}
