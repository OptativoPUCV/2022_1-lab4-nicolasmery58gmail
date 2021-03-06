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
  Pair * m = createPair(key, value);
  long posicion = hash(m->key, map->capacity);
  map->current = posicion;
  while(map->buckets[posicion]!=NULL){
    posicion++;
    if (posicion == map->capacity){
      posicion = 0;
    }
  }
  map->buckets[posicion] = m;
  map->size++;

}

void enlarge(HashMap * map) {
  Pair ** old = map->buckets;
  long resize = map->size;
  map->capacity*=2;
  map->buckets= (Pair **)malloc(sizeof(Pair*)*map->capacity);
  map->size=0;
  for(long i = 0; i<map->capacity; i++){
    if(map->size != resize){
      if(old[i] != NULL){
        insertMap(map, old[i]->key, old[i]->value);
        map->size++;
      }
    }
    if(map->size == resize){
      break;
    }
  }
  
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
  Pair *var=searchMap(map, key);
  if(var!=NULL){
    if(is_equal(key, map->buckets[map->current]->key)==1){
      map->buckets[map->current]->key = NULL;
      map->size--;
    }
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  long posicion;
  posicion = hash(key, map->capacity);
  while(map->buckets[posicion]!=NULL){
    if(is_equal(key, map->buckets[posicion]->key)==1){
      map->current = posicion;
      return map->buckets[posicion];
    }
    if(posicion == map->capacity){
      posicion=0;
    }else{
      posicion++;
    }
    
  }
  
  
  return NULL;
}

Pair * firstMap(HashMap * map) {
  for(long i = 0; i<map->capacity; i++){
    if (map->buckets[i] != NULL){
      if(map->buckets[i]->key != NULL){
        map->current=i;
        return map->buckets[i];
      }
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {
  for(long i = map->current+1; i < map->capacity; i++){
    
    if (map->buckets[i] != NULL){
      if(map->buckets[i]->key != NULL){
        map->current=i;
        return map->buckets[i];
      }
    }
  }
  return NULL;
}
