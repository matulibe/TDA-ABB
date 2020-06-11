#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "abb.h"

#define MENOR -1
#define MAYOR 1
#define IGUAL 0
#define EXITO 0
#define ERROR -1




int comparador(void* actual, void* comparado){
  int primero = *(int*)(actual);
  int segundo = *(int*)(comparado);
  if(primero < segundo){
    return MAYOR;
  }else if(primero > segundo){
    return MENOR;
  }else{
    return IGUAL;
  }
}

void borrar_elemento(void* borrado){

}


nodo_abb_t* buscar_reemplazo(nodo_abb_t* borrado){
  bool encotrado = false;
  nodo_abb_t* retorno;
  if(!borrado->izquierda){
    if(!borrado->derecha)
      return NULL;
    retorno = borrado->derecha;
  }else{
    nodo_abb_t* aux = borrado->izquierda;
    if(aux->derecha == NULL)
      encontrado = true;
    while(encontrado == false){
      if(aux->derecha == NULL)
        encontrado = true;
      aux = aux->derecha;
    }
  }
  return retorno;
}
