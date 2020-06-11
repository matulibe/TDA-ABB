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

abb_t* arbol_crear(abb_comparador* comparador, abb_liberar_elemento* destructor){
  abb_t* arbol = calloc(1, sizeof(abb_t));
  arbol->comparador = (abb_comparador*) comparador;
  arbol->destructor = (abb_liberar_elemento*) destructor;
  return arbol;
}

int insercion(nodo_abb_t* actual, nodo_abb_t* nodo, abb_t* arbol){
  if(arbol->comparador(actual->elemento, nodo->elemento) == MAYOR){
    if(actual->derecha == NULL){
      actual->derecha = nodo;
      return EXITO;
    }else{
      return insercion(actual->derecha, nodo, arbol);
    }
  }else{
    if(actual->izquierda == NULL){
      actual->izquierda = nodo;
      return EXITO;
    }else{
      return insercion(actual->izquierda, nodo, arbol);
    }
  }
}


int arbol_insertar(abb_t* arbol, void* elemento){
  if(!arbol)
    return ERROR;
  nodo_abb_t* nuevo = calloc(1, sizeof(nodo_abb_t));
  nuevo->elemento = elemento;
  if(!arbol->nodo_raiz){
    arbol->nodo_raiz = nuevo;
    return EXITO;
  }
  return insercion(arbol->nodo_raiz, nuevo, arbol);
}

nodo_abb_t* buscar_reemplazo(nodo_abb_t* borrado){
  bool encontrado = false;
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
      if(!aux->derecha){
        if(aux->izquierda){
          borrado->derecha = aux->izquierda;
        }
        retorno = aux;
        encontrado = true;
      }
      aux = aux->derecha;
    }
  }
  return retorno;
}

nodo_abb_t* reordenar(abb_t* arbol, void* elemento, nodo_abb_t* borrado){
  nodo_abb_t* aux = buscar_reemplazo(borrado);
  aux->izquierda = borrado->izquierda;
  aux->derecha = borrado->derecha;
  arbol->destructor(borrado->elemento);
  return aux;
}


int eliminar_y_reordenar(abb_t* arbol, void* elemento, nodo_abb_t* nodo){
  nodo_abb_t* borrado;
  int comparacion = arbol->comparador(nodo->elemento, elemento);
  if(comparacion == MENOR){
    borrado = nodo->izquierda;
    if(nodo->izquierda->elemento == elemento){
      nodo_abb_t* nuevo = reordenar(arbol, elemento, borrado);
      nodo->izquierda = nuevo;
      return EXITO;
    }else{
      return eliminar_y_reordenar(arbol, elemento, borrado);
    }
  }else if(comparacion == MAYOR){
    borrado = nodo->derecha;
    if(nodo->derecha->elemento == elemento){
      nodo_abb_t* nuevo = reordenar(arbol, elemento, borrado);
      nodo->izquierda = nuevo;
      return EXITO;
    }else{
      return eliminar_y_reordenar(arbol, elemento, borrado);
    }
  }
  return ERROR;
}


int arbol_borrar(abb_t* arbol, void* elemento){
  return eliminar_y_reordenar(arbol, elemento, arbol->nodo_raiz);
}

void* busqueda(nodo_abb_t* nodo, void* elemento, abb_t* arbol){
  if(!nodo)
    return NULL;
  int comparador = arbol->comparador(nodo->elemento, elemento);
  if(comparador == MENOR){
    return busqueda(nodo->izquierda, elemento, arbol);
  }else if(comparador == MAYOR){
    return busqueda(nodo->derecha, elemento, arbol);
  }
  return nodo->elemento;
}


void* arbol_buscar(abb_t* arbol, void* elemento){
  return busqueda(arbol->nodo_raiz, elemento, arbol);
}


void* arbol_raiz(abb_t* arbol){
  if(!arbol){
    return NULL;
  }
  return (arbol->nodo_raiz->elemento);
}


bool arbol_vacio(abb_t* arbol){
  if(!arbol->nodo_raiz){
    return true;
  }
  return false;
}


void recorrido_ind(nodo_abb_t* nodo, void** array, int tamanio, int n, int* cantidad){
  if(!nodo){
    return;
  }
  int pos_hijo_der = ((2*n) + 2);
  int pos_hijo_izq = ((2*n) + 1);
  if(pos_hijo_izq >= tamanio){
    return;
  }
  recorrido_ind(nodo->izquierda, array,tamanio, pos_hijo_izq, cantidad);
  array[n] = nodo;
  cantidad++;
  recorrido_ind(nodo->derecha, array, tamanio, pos_hijo_der, cantidad);
}


int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
  if(!array || !tamanio_array){
    return ERROR;
  }
  int posicion = 0, cantidad = 0;
  recorrido_ind(arbol->nodo_raiz, array, tamanio_array, posicion, &cantidad);
  return cantidad;
}


int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array);


int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array);


void destruir_nodos(nodo_abb_t* nodo){
  if(!nodo){
    return;
  }
  destruir_nodos(nodo->izquierda);
  destruir_nodos(nodo->derecha);
  free(nodo);
}


void arbol_destruir(abb_t* arbol){
  if(!arbol)
    return;
  destruir_nodos(arbol->nodo_raiz);
  free(arbol);
}


void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
  if(recorrido == ABB_RECORRER_INORDEN){

  }else if(recorrido == ABB_RECORRER_PREORDEN){

  }else{
    
  }
}
